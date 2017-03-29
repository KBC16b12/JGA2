#include "stdafx.h"
#include "Player.h"
#include "../Bar/Bar.h"
#include "../Camera/GameCamera.h"

Player::Player()
{
	//HP設定
	m_maxhp = m_hp = 15;

	m_HPbar = NewGO<Bar>(0);
	m_HPbar->SetBarPos({ -592.95f, 320.0f });
	m_HPbar->SetBarMaxSize({ 230.5f, 14.2f });
	m_HPbar->SetGaugePos({ -600.0f, 320.0f });
	m_HPbar->SetGaugeMaxSize({ 245.0f, 31.5f });
	m_HPbar->SetBarPath("Assets/sprite/Green.png");
	m_HPbar->SetGaugePath("Assets/sprite/Black.png");
	m_HPbar->SetBarBackPath("Assets/sprite/Black.png");
	m_HPbar->SetData(m_hp, m_maxhp);
	m_HPbar->SetBerQuarter(Bar::enBarQuarter::enQuaLeft);
}

Player::~Player()
{
	DeleteGO(m_HPbar);
}

bool Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/snowman.X", NULL);
	m_skinModel.Init(&m_skinModelData);
	g_defaultLight.SetAmbinetLight(CVector3::One);
	m_skinModel.SetLight(&g_defaultLight);	//デフォルトライトを設定。
	m_rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(0.0f));

	//キャラクタコントローラの初期化。
	m_characterController.Init(0.5f, 1.0f, m_position);

	return true;
}

void Player::Update()
{
	UpdateHPBar();

	Move();

	//ワールド行列の更新
	m_skinModel.Update(m_position, m_rotation, { 5.0f,5.0f,5.0f });
	//アニメーションの更新
	m_Animation.Update(1.0f / 50.0f);
}

void Player::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(), g_gameCamera->GetProjectionMatrix());
}

void Player::UpdateHPBar()
{
	if (m_maxhp <= 0)
	{
		return;
	}

	//HP50%以上
	if (50.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_HPbar->SetBarPath("Assets/sprite/Green.png");
	}
	//HP10%以上50%以下
	else if (10.0f < (float)m_hp / (float)m_maxhp * 100.0f)
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
	CMatrix l_pmatrix = m_skinModel.GetWorldMatrix();

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
	l_moveX.Scale(Pad(0).GetLStickXF());
	l_moveZ.Scale(Pad(0).GetLStickYF());
	l_moveSpeed.Add(l_moveX);
	l_moveSpeed.Add(l_moveZ);

	/*アングル*/
	if (Pad(0).GetRStickXF() > 0.0f)
	{
		m_angle += 5.0f;
	}
	if (Pad(0).GetRStickXF() < 0.0f)
	{
		m_angle -= 5.0f;
	}

	/*ジャンプ*/
	if (!m_characterController.IsJump() && Pad(0).IsPress(enButtonX))
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


	m_rotation.SetRotation(CVector3(0.0f, 1.0f, 0.0f), CMath::DegToRad(m_angle));
}