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
#include "DeadAfterPlayer.h"

Player::Player()
{
	//HP設定
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
	m_recovery = NewGO<PlayerRecovery>(PRIORITY1);
}

Player::~Player()
{
	DeleteGO(m_HPbar);
	DeleteGO(m_killCountSprite);
	DeleteGO(m_recovery);
}

bool Player::Start()
{
	//m_light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	//m_light.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	//m_light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	//m_light.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });
	m_light.SetDiffuseLightDirection(0, { 0.0f, 1.0f, 0.0f });
	m_light.SetDiffuseLightDirection(1, { 0.0f, -1.0f, 0.0f });
	m_light.SetDiffuseLightDirection(2, { 0.0f, 0.707f, 0.707f });
	m_light.SetDiffuseLightDirection(3, { 0.0f, 0.707f, -0.707f });

	float l_lightColor1 = 0.15f;
	float l_lightColor2 = 0.4f;
	float l_lightColor3 = 0.2f;

	float l_lightColor4 = 0.3f;
	m_light.SetDiffuseLightColor(0, { l_lightColor1, l_lightColor1, l_lightColor1, 1.0f });
	m_light.SetDiffuseLightColor(1, { l_lightColor2, l_lightColor2, l_lightColor2, 1.0f });
	m_light.SetDiffuseLightColor(2, { l_lightColor3, l_lightColor3, l_lightColor3, 1.0f });
	m_light.SetDiffuseLightColor(3, { l_lightColor4, l_lightColor4, l_lightColor4, 1.0f });

	m_skinModelDataFirst.LoadModelData("Assets/modelData/snowman_first.X", &m_animation);
	m_skinModelFirst.Init(&m_skinModelDataFirst);
	m_skinModelFirst.SetLight(&m_light);	//デフォルトライトを設定。
	m_skinModelDataThird.LoadModelData("Assets/modelData/snowman1-3.X", NULL);
	m_skinModelThird.Init(&m_skinModelDataThird);
	m_skinModelThird.SetLight(&m_light);	//デフォルトライトを設定。
	m_skinModelFirst.SetShadowCasterFlag(true);
	m_skinModelThird.SetShadowCasterFlag(true);
	m_skinModelFirst.SetShadowReceiverFlag(true);
	m_skinModelThird.SetShadowReceiverFlag(true);
	//キャラクタコントローラの初期化。
	m_characterController.Init(1.7f, 1.0f, m_position);
	//m_characterController.SetGravity(0.0f);
	m_animation.SetAnimationLoopFlag(ANIMESTATE_WAIT, false);
	m_animation.SetAnimationLoopFlag(ANIMESTATE_SHOT, false);
	m_animation.SetAnimationLoopFlag(ANIMESTATE_RELOAD, false);
	m_animation.PlayAnimation(ANIMESTATE_WAIT);
	m_HPbar->SetPlayerNum(m_playernum);
	m_killCountSprite->SetPlayerNum(m_playernum);
	m_skinModelFirst.SetFresnelFlag(true);
	m_skinModelThird.SetFresnelFlag(true);
	m_skinModelThird.SetTechnique(enTecShaderHandle_Toon);
	//m_skinModelFirst.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere);
	//m_skinModelThird.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere);
	return true;
}

void Player::Init(CVector3 position, CQuaternion rotation, int playernum)
{
	m_rotation = rotation;
	m_position = position;
	m_playernum = playernum;
	m_recovery->Init(&m_hp, m_maxhp, m_playernum);
	m_weapon.Init(m_playernum, &m_animation, &m_light);
	float l_lightColor = 0.2f;
	float l_playerColor = 0.5f;
	CVector3 l_ambinetLight = { l_lightColor, l_lightColor, l_lightColor };
	switch (m_playernum)
	{
	case 0:
		l_ambinetLight.Set(1.2f, 1.2f, 1.2f);
		break;
	case 1:
		l_ambinetLight.Set(1.8f, 0.2f, 0.2f);
		break;
	case 2:
		l_ambinetLight.Set(0.2f, 1.8f, 0.2f);
		break;
	case 3:
		l_ambinetLight.Set(0.2f, 0.2f, 1.8f);
		break;
	}
	m_light.SetAmbinetLight(l_ambinetLight);
}

void Player::Update()
{
	if (g_gameScene == nullptr || g_gameScene->IsTimeOver())
	{
		return;
	}

	UpdateHPBar();
	m_killCountSprite->SetData(m_killCount);
	Move();

	//ワールド行列の更新
	m_skinModelFirst.Update(m_position, m_rotation, CVector3::One);
	m_skinModelThird.Update(m_position, m_rotation, CVector3::One);
	//アニメーションの更新
	m_Animation.Update(1.0f / 50.0f);

	KeyOutput();
	DataOutput();
	Invincible();
	m_animation.Update(GameTime().GetFrameDeltaTime());
	//無敵状態なら
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
			m_skinModelThird.SetTechnique(enTecShaderHandle_Toon);
		}
		m_invincibleTecCount += GameTime().GetFrameDeltaTime();
	}

	m_weapon.Update();
}

void Player::Render(CRenderContext& renderContext, int playernum)
{
	//自分のカメラからは一人称視点のモデルを、他のカメラからは3人称視点のモデルを描画する。
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

	//HP50%以上
	if (50.0f < hp_per)
	{
		m_HPbar->SetBarPath("Assets/sprite/Green.png");
	}
	//HP10%以上50%未満
	else if (10.0f < hp_per)
	{
		m_HPbar->SetBarPath("Assets/sprite/Blue.png");
	}
	//HP10%未満
	else
	{
		m_HPbar->SetBarPath("Assets/sprite/Red.png");
	}
	m_HPbar->SetData(m_hp, m_maxhp);
	
}

void Player::Move()
{
	float	l_angle = 0.0f;
	move = -13.0f; //移動速度
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

	/*移動*/
	l_moveX.Scale(Pad(m_playernum).GetLStickXF());
	l_moveZ.Scale(Pad(m_playernum).GetLStickYF());
	l_moveSpeed.Add(l_moveX);
	l_moveSpeed.Add(l_moveZ);

	/*アングル*/
	float angleSpeed = 7.0f;
	if (Pad(m_playernum).IsPress(enButtonLB1))
	{
		angleSpeed *= 0.5f;
	}
	l_angle += Pad(m_playernum).GetRStickXF() * angleSpeed;

	/*ジャンプ*/
	//仕様から一応削除
	/*if (!m_characterController.IsJump() && Pad(m_playernum).IsPress(enButtonX))
	{
		m_characterController.Jump();
		l_moveSpeed.y = move * -2.0f;
	}
		l_moveSpeed.y += 20.0f;
	}*/


	//決定した移動速度をキャラクタコントローラーに設定。
	m_characterController.SetMoveSpeed(l_moveSpeed);
	//キャラクターコントローラーを実行。
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	//実行結果を受け取る。
	m_position = m_characterController.GetPosition();
	m_position.y += 3.4f;
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, CMath::DegToRad(l_angle));
	m_rotation.Multiply(multi);
}

void Player::Damage(int playerNum, int damage, CVector3 moveSpeed)
{
	if (m_isInvincible || !m_isActive)
	{
		return;
	}
	//HPを減算
	m_hp -= damage;
	if (m_hp <= 0)
	{
		//もしHPが０になり死んだ場合殺した相手のカウントアップをしリスポーンする。
		g_gameScene->GetPlayer(playerNum)->KillCountUp();
		Death(moveSpeed);
	}
	else
	{
		m_recovery->Hit();
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

		Death(CVector3::Zero);
	}
	else
	{
		m_recovery->Hit();
	}
}

void Player::Respawn()
{
	SMapInfo l_mapDat = g_randomPosManager->GetPlayerRespawnPos(m_playernum);
	//HPを回復して座標を初期化
	m_hp = m_maxhp;
	m_position = l_mapDat.s_position;
	m_characterController.SetPosition(m_position);
	m_rotation = l_mapDat.s_rotation;
	m_isInvincible = true;
	m_weapon.Respawn();
	m_isActive = true;
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
		m_skinModelThird.SetTechnique(enTecShaderHandle_Toon);
		m_invincibleCount = 0.0f;
		m_invincibleTecCount = 0.0f;
	}
}

void Player::Death(CVector3 moveSpeed)
{

	m_isActive = false;
	g_gameCamera[m_playernum]->PlayAnime();
	for (int i = 0; i < PLAYERMESHNUM; i++)
	{
		DeadAfterPlayer *l_deadPlayer = NewGO<DeadAfterPlayer>(PRIORITY1);
		CMatrix l_worldMatrix = *m_skinModelDataThird.FindBoneWorldMatrix(g_playerMeshState[i].name);
		CVector3 l_position;
		l_position.x = l_worldMatrix.m[3][0];
		l_position.y = l_worldMatrix.m[3][1];
		l_position.z = l_worldMatrix.m[3][2];
		l_deadPlayer->Init(g_playerMeshModel[i], l_position, m_rotation, m_light, moveSpeed, g_playerMeshState[i]);
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


