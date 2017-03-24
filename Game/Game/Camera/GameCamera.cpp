#include "stdafx.h"
#include "GameCamera.h"

GameCamera* g_gameCamera;

GameCamera::GameCamera()
{
	//ƒJƒƒ‰‚Ì‰Šú‰»
	m_position = CVector3::Zero;
	m_position.z -= 50.0f;
	m_look_position = CVector3::Zero;

	m_angle = 0.0f;

	m_camera.SetPosition(m_position);
	m_camera.SetTarget(m_look_position);
	m_camera.SetUp(CVector3::AxisY);
	m_camera.Update();
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	Move();
}

void GameCamera::Move()
{
	CVector3 C_movespeed = m_characterController.GetMoveSpeed();
	CVector3 C_moveX;
	CVector3 C_moveY;

	if (Pad(0).GetRStickXF() > 0.0f)
	{
		;
	}
	if (Pad(0).GetRStickXF() < 0.0f)
	{
		;
	}
}