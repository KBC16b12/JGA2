#include "stdafx.h"
#include "GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"

//extern GameScene* g_player;
extern Player* g_player;
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
	float move;
	move = -5.0f;

	CVector3 l_move = m_characterController.GetPosition();
	CVector3 l_moveX, l_moveY, l_moveZ;
	CVector3 Ppos;

	l_move.x = 0.0f;
	l_move.y = 0.0f;
	l_move.z = 0.0f;

	l_moveX.Scale(move);
	l_moveY.Scale(move);
	l_moveZ.Scale(move);

	l_moveX.Scale(Pad(0).GetLStickXF());
	l_moveZ.Scale(Pad(0).GetLStickYF());
	l_move.Add(l_moveX);
	l_move.Add(l_moveZ);

	if (g_gameScene != nullptr)
	{
		Ppos = g_player->GetPos();
	}

	m_camera.SetPosition(m_position);
	m_camera.SetTarget(Ppos);
}