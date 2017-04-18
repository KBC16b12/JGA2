#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"

GameCamera* g_gameCamera[PLAYER_NUM];

GameCamera::GameCamera()
{
	
	//�J�����̏�����
	m_position = CVector3::Zero;
	m_position.z -= 50.0f;
	m_look_position = CVector3::Zero;

	m_angle = 0.0f;

	m_camera.SetPosition(m_position);
	m_camera.SetTarget(m_look_position);
	m_camera.SetUp(CVector3::AxisY);
	m_camera.Update();
	m_ViewportFlg = false;
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{

	m_camera.Update();
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

void GameCamera::SetViewPort(int x, int y, int width, int height, int playernum)
{
	m_playernum = playernum;
	m_sviewPort = { (DWORD)x, (DWORD)y, (DWORD)width, (DWORD)height, 0.0f, 1.0f };
	m_player = g_gameScene->GetPlayer(m_playernum);
	m_ViewportFlg = true;
}

void GameCamera::Render(CRenderContext& renderContext)
{
	if (!m_ViewportFlg)
	{
		return;
	}
	renderContext.SetViewport(m_sviewPort);
	g_gameScene->Render(renderContext, m_playernum);
}

void GameCamera::PostRender(CRenderContext& renderContext)
{
	if (!m_ViewportFlg)
	{
		return;
	}
	renderContext.SetViewport(m_sviewPort);
	g_gameScene->PostRender(renderContext, m_playernum);
}