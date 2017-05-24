#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"

//extern GameScene* g_player;
extern Player* g_player;
GameCamera* g_gameCamera[PLAYER_NUM];

GameCamera::GameCamera()
{
	
	//ƒJƒƒ‰‚Ì‰Šú‰»
	m_position = CVector3::Zero;
	m_position.z -= 50.0f;
	m_look_position = CVector3::Zero;
	m_camera.SetPosition(m_position);
	m_camera.SetTarget(m_look_position);
	m_camera.SetUp(CVector3::AxisY);

	m_camera.Update();
	m_angle = 0.0f;
	m_isViewport = false;
	m_playernum = 0;
}

GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	SetPos();
	m_camera.Update();
}


void GameCamera::SetPos()
{
	if (!m_isViewport)
	{
		return;
	}
	CVector3 l_tarbget = m_player->GetPosition();
	m_camera.SetPosition(l_tarbget);
	l_tarbget.Add(m_player->GetFrontWorldMatrix());
	m_camera.SetTarget(l_tarbget);
}


void GameCamera::Render(CRenderContext& renderContext)
{
}

void GameCamera::PostRender(CRenderContext& renderContext)
{
}