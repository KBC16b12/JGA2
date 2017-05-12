#include "stdafx.h"
#include "Player.h"
#include "HUD/Bar.h"
#include "../Camera/GameCamera.h"
#include "../HUD/KillCountSprite.h"
#include "../Scene/GameScene/GameScene.h"

Player *player;
Player::Player()
{
	m_respawnPosition = CVector3::Zero;
	//HP設定
	m_maxhp = m_hp = 15;
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
	m_light.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });

	SkinModelDataResources().Load(m_skinModelDataFirst, "Assets/modelData/snowman_first.X", NULL, false, 1);
	m_skinModelFirst.Init(m_skinModelDataFirst.GetBody());
	m_skinModelFirst.SetLight(&m_light);	//デフォルトライトを設定。
	SkinModelDataResources().Load(m_skinModelDataThird, "Assets/modelData/snowman1-3.X", NULL, false, 1);
	m_skinModelThird.Init(m_skinModelDataThird.GetBody());
	m_skinModelThird.SetLight(&m_light);	//デフォルトライトを設定。
	m_skinModelFirst.SetShadowCasterFlag(true);
	m_skinModelThird.SetShadowCasterFlag(true);
	m_skinModelFirst.SetShadowReceiverFlag(true);
	m_skinModelThird.SetShadowReceiverFlag(true);

	m_rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));
	m_respawnRotation = m_rotation;
	//キャラクタコントローラの初期化。
	m_characterController.Init(0.5f, 1.0f, m_position);
	

	m_HPbar->SetPlayerNum(m_playernum);
	m_killCountSprite->SetPlayerNum(m_playernum);
	return true;
}

void Player::Update()
{
	if (Pad(m_playernum).IsTrigger(enButtonRB1))
	{
		m_weapon.BulletFilling();
	}

	m_weapon.Update();
	UpdateHPBar();
	m_killCountSprite->SetData(m_killCount);

	Move();

	//ワールド行列の更新
	m_skinModelFirst.Update(m_position, m_rotation, CVector3::One);
	m_skinModelThird.Update(m_position, m_rotation, { 5.0f,5.0f,5.0f });
	//アニメーションの更新
	m_Animation.Update(1.0f / 50.0f);
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
	float move;
	move = -5.0f; //移動速度
	CVector3 l_moveSpeed = m_characterController.GetMoveSpeed();
	CVector3 l_moveX;
	CVector3 l_moveZ;
	l_moveSpeed.x = 0.0f;
	l_moveSpeed.z = 0.0f;
	CMatrix l_pmatrix = m_skinModelFirst.GetWorldMatrix();

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
	m_angle += Pad(m_playernum).GetRStickXF() * 5.0f;

	/*ジャンプ*/
	if (!m_characterController.IsJump() && Pad(m_playernum).IsPress(enButtonX))
	{
		m_characterController.Jump();
		l_moveSpeed.y += 15.0f;
	}

	//決定した移動速度をキャラクタコントローラーに設定。
	m_characterController.SetMoveSpeed(l_moveSpeed);
	//キャラクターコントローラーを実行。
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	//実行結果を受け取る。
	m_position = m_characterController.GetPosition();
	m_position.y += 2.0f;
	m_rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(m_angle));
}

void Player::Damage(int playerNum)
{
	//HPを減算
	m_hp--;
	if (m_hp <= 0)
	{
		//もしHPが０になり死んだ場合殺した相手のカウントアップをしリスポーンする。
		g_gameScene->GetPlayer(playerNum)->KillCountUp();
		Respawn();
	}
}

void Player::Respawn()
{
	//HPを回復して座標を初期化
	m_hp = m_maxhp;
	m_position = m_respawnPosition;
	m_characterController.SetPosition(m_position);
	m_rotation = m_respawnRotation;
}

