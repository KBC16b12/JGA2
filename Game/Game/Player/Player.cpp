#include "stdafx.h"
#include "Player.h"
#include "HUD/Bar.h"
#include "../Camera/GameCamera.h"
#include "../HUD/KillCountSprite.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Trap.h"
#include "../Network/Network.h"
#include "HUD/CountUpSprite.h"
#include "RandomPosManager.h"

Player::Player()
{
	//HP�ݒ�
	m_maxhp = m_hp = 6;
	m_killCount = 0;
	m_HPbar = NewGO<Bar>(PRIORITY1);
	m_HPbar->SetBarPos({ -592.95f, 320.0f });
	m_HPbar->SetBarMaxSize({ 230.5f, 14.2f });
	m_HPbar->SetGaugePos({ -600.0f, 320.0f });
	m_HPbar->SetGaugeMaxSize({ 245.0f, 31.5f });
	m_HPbar->SetBarPath("Assets/sprite/Green.png");
	m_HPbar->SetGaugePath("Assets/sprite/Black.png");
	m_HPbar->SetBarBackPath("Assets/sprite/Black.png");
	m_HPbar->SetData(m_hp, m_maxhp);
	m_HPbar->SetBerQuarter(Bar::enBarQuarter::enQuaLeft);
	m_killCountSprite = NewGO<KillCountSprite>(PRIORITY1);
	m_isInvincible = false;
	m_isInvincibleTec = true;
	m_invincibleCount = 0.0f;
	m_invincibleTecCount = 0.0f;
}

Player::~Player()
{
	DeleteGO(m_HPbar);
	DeleteGO(m_killCountSprite);
}

bool Player::Start()
{
	//m_light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	//m_light.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	//m_light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	//m_light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });
	m_light.SetDiffuseLightDirection(0, { 0.0f, 1.0f, 0.0f });
	m_light.SetDiffuseLightDirection(1, { 0.0f, -1.0f, 0.0f });
	m_light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	m_light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

	float l_lightColor1 = 0.15f;
	float l_lightColor2 = 0.4f;
	float l_lightColor3 = 0.2f;

	float l_lightColor4 = 0.3f;
	m_light.SetDiffuseLightColor(0, { l_lightColor1, l_lightColor1, l_lightColor1, 1.0f });
	m_light.SetDiffuseLightColor(1, { l_lightColor2, l_lightColor2, l_lightColor2, 1.0f });
	m_light.SetDiffuseLightColor(2, { l_lightColor3, l_lightColor3, l_lightColor3, 1.0f });
	m_light.SetDiffuseLightColor(3, { l_lightColor4, l_lightColor4, l_lightColor4, 1.0f });

	SkinModelDataResources().Load(m_skinModelDataFirst, "Assets/modelData/snowman_first.X", &m_animation, false, 1);
	m_skinModelFirst.Init(m_skinModelDataFirst.GetBody());
	m_skinModelFirst.SetLight(&m_light);	//�f�t�H���g���C�g��ݒ�B
	m_skinModelDataThird.LoadModelData("Assets/modelData/snowman1-3.X", NULL);
	m_skinModelThird.Init(&m_skinModelDataThird);
	m_skinModelThird.SetLight(&m_light);	//�f�t�H���g���C�g��ݒ�B
	m_skinModelFirst.SetShadowCasterFlag(true);
	m_skinModelThird.SetShadowCasterFlag(true);
	m_skinModelFirst.SetShadowReceiverFlag(true);
	m_skinModelThird.SetShadowReceiverFlag(true);
	//�L�����N�^�R���g���[���̏������B
	m_characterController.Init(1.7f, 1.0f, m_position);
	m_characterController.SetGravity(0.0f);
	m_animation.SetAnimationLoopFlag(ANIMESTATE_WAIT, false);
	m_animation.SetAnimationLoopFlag(ANIMESTATE_SHOT, false);
	m_animation.SetAnimationLoopFlag(ANIMESTATE_RELOAD, false);
	m_animation.PlayAnimation(ANIMESTATE_WAIT);
	m_HPbar->SetPlayerNum(m_playernum);
	m_killCountSprite->SetPlayerNum(m_playernum);
	m_skinModelFirst.SetFresnelFlag(true);
	m_skinModelThird.SetFresnelFlag(true);
	//m_skinModelFirst.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere);
	//m_skinModelThird.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere);
	return true;
}

void Player::Init(CVector3 position, CQuaternion rotation, int playernum)
{
	m_rotation = rotation;
	m_position = position;
	m_recovery.Init(&m_hp, m_maxhp);

	m_playernum = playernum;
	m_weapon.Init(m_playernum, &m_animation, &m_light);
	float l_lightColor = 0.3f;
	float l_playerColor = 1.0f;
	CVector3 l_ambinetLight = { l_lightColor, l_lightColor, l_lightColor };
	switch (m_playernum)
	{
	case 0:
		break;
	case 1:
		l_ambinetLight.x = l_playerColor;
		break;
	case 2:
		l_ambinetLight.y = l_playerColor;
		break;
	case 3:
		l_ambinetLight.z = l_playerColor + 0.5f;
		break;
	}
	m_light.SetAmbinetLight(l_ambinetLight);
}

void Player::Update()
{
	m_weapon.Update();
	UpdateHPBar();
	m_killCountSprite->SetData(m_killCount);
	m_recovery.Update();
	Move();

	//���[���h�s��̍X�V
	m_skinModelFirst.Update(m_position, m_rotation, CVector3::One);
	m_skinModelThird.Update(m_position, m_rotation, { 5.0f,5.0f,5.0f });
	//�A�j���[�V�����̍X�V
	m_Animation.Update(1.0f / 50.0f);

	KeyOutput();
	DataOutput();
	Invincible();
	m_animation.Update(GameTime().GetFrameDeltaTime());
	//���G��ԂȂ�
	if (m_isInvincible)
	{
		if (0.2f <= m_invincibleTecCount)
		{
			m_isInvincibleTec = !m_isInvincibleTec;
			m_invincibleTecCount = 0.0f;
		}
		if (m_isInvincibleTec)
		{
			m_skinModelThird.SetTechnique(enTecShaderHandle_Invincible);
		}
		else
		{
			m_skinModelThird.SetTechnique(enTecShaderHandle_NoSkinModel);
		}
		m_invincibleTecCount += GameTime().GetFrameDeltaTime();
	}
}

void Player::Render(CRenderContext& renderContext, int playernum)
{
	//�����̃J��������͈�l�̎��_�̃��f�����A���̃J���������3�l�̎��_�̃��f����`�悷��B
	if (m_playernum == playernum)
	{
		m_skinModelFirst.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
	}
	else
	{
		m_skinModelThird.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
	}
}

void Player::Render(CRenderContext& renderContext)
{
	m_skinModelFirst.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}


void Player::UpdateHPBar()
{
	if (m_maxhp <= 0)
	{
		return;
	}

	float hp_per = (float)m_hp / (float)m_maxhp * 100.0f;

	//HP50%�ȏ�
	if (50.0f < hp_per)
	{
		m_HPbar->SetBarPath("Assets/sprite/Green.png");
	}
	//HP10%�ȏ�50%����
	else if (10.0f < hp_per)
	{
		m_HPbar->SetBarPath("Assets/sprite/Blue.png");
	}
	//HP10%����
	else
	{
		m_HPbar->SetBarPath("Assets/sprite/Red.png");
	}
	m_HPbar->SetData(m_hp, m_maxhp);
	
}

void Player::Move()
{
	float	l_angle = 0.0f;
	move = -13.0f; //�ړ����x
	CVector3 l_moveSpeed = m_characterController.GetMoveSpeed();
	CVector3 l_moveX;
	CVector3 l_moveZ;
	l_moveSpeed.x = 0.0f;
	l_moveSpeed.z = 0.0f;
	CMatrix l_pmatrix = m_skinModelFirst.GetWorldMatrix();

	Trap();

	l_moveX.x = l_pmatrix.m[0][0];
	l_moveX.y = l_pmatrix.m[0][1];
	l_moveX.z = l_pmatrix.m[0][2];
	l_moveX.Normalize();
	l_moveX.Scale(move);

	l_moveZ.x = l_pmatrix.m[2][0];
	l_moveZ.y = l_pmatrix.m[2][1];
	l_moveZ.z = l_pmatrix.m[2][2];
	l_moveZ.Normalize();
	l_moveZ.Scale(move);

	/*�ړ�*/
	l_moveX.Scale(Pad(m_playernum).GetLStickXF());
	l_moveZ.Scale(Pad(m_playernum).GetLStickYF());
	l_moveSpeed.Add(l_moveX);
	l_moveSpeed.Add(l_moveZ);

	/*�A���O��*/
	float angleSpeed = 7.0f;
	if (Pad(m_playernum).IsPress(enButtonLB1))
	{
		angleSpeed *= 0.5f;
	}
	l_angle += Pad(m_playernum).GetRStickXF() * angleSpeed;

	/*�W�����v*/
	//�d�l����ꉞ�폜
	/*if (!m_characterController.IsJump() && Pad(m_playernum).IsPress(enButtonX))
	{
		m_characterController.Jump();
		l_moveSpeed.y = move * -2.0f;
	}
		l_moveSpeed.y += 20.0f;
	}*/


	//���肵���ړ����x���L�����N�^�R���g���[���[�ɐݒ�B
	m_characterController.SetMoveSpeed(l_moveSpeed);
	//�L�����N�^�[�R���g���[���[�����s�B
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	//���s���ʂ��󂯎��B
	m_position = m_characterController.GetPosition();
	m_position.y += 3.4f;
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, CMath::DegToRad(l_angle));
	m_rotation.Multiply(multi);
}

void Player::Damage(int playerNum, int damage)
{
	if (m_isInvincible)
	{
		return;
	}
	//HP�����Z
	m_hp -= damage;
	if (m_hp <= 0)
	{
		//����HP���O�ɂȂ莀�񂾏ꍇ�E��������̃J�E���g�A�b�v�������X�|�[������B
		g_gameScene->GetPlayer(playerNum)->KillCountUp();
		Respawn();
	}
	else
	{
		m_recovery.Hit();
	}
}

void Player::Trap()
{
	if (Stup == true)
	{
		m_time--;
		if (m_time > 0)
		{
			move = 0.0f;
		}

		if (m_time < 0)
		{
			Ctime--;
			if (Ctime > 0)
			{
				move = -5.0f;
				Stup = false;
			}
		}

		//Stup = true;
	}

	//m_time = 30;
}

void Player::Startup()
{
	Stup = true;
	m_time = 30;
	Ctime = 15;
	move = -5.0f;
}

void Player::Eaten()
{
	m_hp -= 1;
	if (m_hp <= 0)
	{

		Respawn();
	}
	else
	{
		m_recovery.Hit();
	}
}

void Player::Respawn()
{
	SMapInfo l_mapDat = g_randomPosManager->GetPlayerRespawnPos(m_playernum);
	//HP���񕜂��č��W��������
	m_hp = m_maxhp;
	m_position = l_mapDat.s_position;
	m_characterController.SetPosition(m_position);
	m_rotation = l_mapDat.s_rotation;
	m_isInvincible = true;
	m_weapon.Respawn();
}

void Player::Invincible()
{
	if (!m_isInvincible)
	{
		return;
	}

	m_invincibleCount += GameTime().GetFrameDeltaTime();
	if (2.0f <= m_invincibleCount)
	{
		m_isInvincible = false;
		m_skinModelThird.SetTechnique(enTecShaderHandle_NoSkinModel);
		m_invincibleCount = 0.0f;
		m_invincibleTecCount = 0.0f;
	}
}

void Player::KillCountUp()
{
	m_killCount++;
	CountUpSprite *sprite = NewGO<CountUpSprite>(PRIORITY0);
	sprite->Init(m_playernum);
}

void Player::KeyOutput()
{
}

void Player::DataOutput()
{
	
}


