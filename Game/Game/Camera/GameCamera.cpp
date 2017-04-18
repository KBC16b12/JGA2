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

void GameCamera::SetViewPort(int x, int y, int width, int height, int cameranum)
{
	m_cameranum = cameranum;
	m_sviewPort = { (DWORD)x, (DWORD)y, (DWORD)width, (DWORD)height, 0.0f, 1.0f };
	m_player = g_gameScene->GetPlayer(m_cameranum);
	m_ViewportFlg = true;
}

void GameCamera::Render(CRenderContext& renderContext)
{
	if (!m_ViewportFlg)
	{
		return;
	}
	renderContext.SetViewport(m_sviewPort);
	if (g_gameScene != nullptr)
	{
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			Player* l_player = g_gameScene->GetPlayer(i);
			l_player->Render(renderContext, m_cameranum);
		}
		const std::vector<MapChip*>& l_mapchip = g_gameScene->GetMap();
		for (MapChip* chip : l_mapchip)
		{
			chip->Render(renderContext, m_cameranum);
		}
	}
}

void GameCamera::PostRender(CRenderContext& rendercontext)
{

}