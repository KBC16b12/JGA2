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
	m_isDead = false;
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	SkinModelDataResources().Load(m_skinModelData, "Assets/modelData/camera.X", &m_animation, false, 1);
	m_skinModel.Init(m_skinModelData.GetBody());
	m_skinModel.SetLight(&m_light);
	m_animation.SetAnimationLoopFlag(0, false);
	m_worldMatrix = m_skinModelData.GetBody()->FindBoneWorldMatrix("Body");
	return true;
}

void GameCamera::Update()
{
	if (!m_isViewport)
	{
		return;
	}

	SetPos();


	m_camera.Update();
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
}


void GameCamera::SetPos()
{
	if (!m_isViewport)
	{
		return;
	}
	if (!m_isDead)
	{
		m_position = m_player->GetPosition();
		m_rotation = m_player->GetRotation();
		m_camera.SetUp(CVector3::AxisY);
		m_camera.SetPosition(m_position);
		CVector3 l_tarbget = m_position;
		l_tarbget.Add(m_player->GetFrontWorldMatrix());
		m_camera.SetTarget(l_tarbget);
	}
	else
	{
		CVector3 l_position;
		l_position.x = m_worldMatrix->m[3][0];
		l_position.y = m_worldMatrix->m[3][1];
		l_position.z = m_worldMatrix->m[3][2];
		m_camera.SetPosition(l_position);
		CVector3 l_target;
		l_target.x = m_worldMatrix->m[2][0];
		l_target.y = m_worldMatrix->m[2][1];
		l_target.z = m_worldMatrix->m[2][2];
		l_target.Add(l_position);
		m_camera.SetTarget(l_target);
		CVector3 l_up;
		l_up.x = m_worldMatrix->m[1][0];
		l_up.y = m_worldMatrix->m[1][1];
		l_up.z = m_worldMatrix->m[1][2];
		m_camera.SetUp(l_up);
		m_animation.Update(GameTime().GetFrameDeltaTime());
		if (!m_animation.IsPlay())
		{
			m_isDead = false;
			m_player->Respawn();
		}

	}
}


void GameCamera::Render(CRenderContext& renderContext)
{
}

void GameCamera::PostRender(CRenderContext& renderContext)
{
}