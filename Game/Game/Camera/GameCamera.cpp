#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"

GameCamera* g_gameCamera[PLAYER_NUM];

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
	m_ViewportFlg = false;
	m_playernum = 0;
	m_PlayerFlg = false;
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	SetPos();
	Move();
	m_camera.Update();
}


void GameCamera::SetPos()
{
	if (!m_PlayerFlg && !m_ViewportFlg)
	{
		return;
	}
	CVector3 l_tarbget = m_player->GetPosition();
	m_camera.SetPosition(l_tarbget);
	l_tarbget.Add(m_player->GetFrontWorldMatrix());
	m_camera.SetTarget(l_tarbget);
}

void GameCamera::Move()
{
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