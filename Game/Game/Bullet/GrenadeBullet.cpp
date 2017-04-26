#include "stdafx.h"
#include "GrenadeBullet.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"

GrenadeBullet::GrenadeBullet()
{
}


GrenadeBullet::~GrenadeBullet()
{
}

void GrenadeBullet::Init(Weapon* weapon ,int arraynum, int playerNum)
{
	Bullet::Init(weapon, arraynum, playerNum);
	m_characterController.Init(0.3f, 0.3f, m_position);
	m_moveSpeed.Scale(10.0f);
	m_characterController.SetGravity(-24.0f);
	m_moveSpeed.y += 10.0f;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetCollisionFlg(false);
}

void GrenadeBullet::Update()
{
	Bullet::Update();
}

void GrenadeBullet::Move()
{
	m_moveSpeed.y = m_characterController.GetMoveSpeed().y;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	m_position = m_characterController.GetPosition();
}

void GrenadeBullet::DethCheck()
{
	bool l_isDelete = false;
	Player* l_player = g_gameScene->GetPlayer(m_playerNum);
	CVector3 l_distance = l_player->GetPosition();
	l_distance.Subtract(m_position);
	if (3.0f < l_distance.Length() && m_characterController.IsCollision())
	{
		l_isDelete = true;
	}
	if (l_isDelete)
	{
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			Player* l_player = g_gameScene->GetPlayer(i);
			CVector3 l_distance = l_player->GetPosition();
			l_distance.Subtract(m_position);
			if (l_distance.Length() < 8.0f && m_playerNum != i)
			{
				l_player->Damage(m_playerNum);
			}

		}
		m_weapon->Delete(m_arraynum);
	}
}