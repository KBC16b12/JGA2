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
	//重力設定
	m_characterController.SetGravity(-0.1f);
	m_moveSpeed.y += 1.0f;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	//打った瞬間に自分に当たってしまうため少し動かしておく
	for (int i = 0;i < 2;i++)
	{
		m_characterController.Execute(1.0f);
	}
	m_characterController.SetCollisionFlg(false);
}

void GrenadeBullet::Update()
{
	Bullet::Update();
}

void GrenadeBullet::DethCheck()
{
	//何か物に当たったら消去する
	if (m_characterController.IsCollision())
	{
		//消されるときに爆発で近くにいるプレイヤーにダメージを与える
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			Player* l_player = g_gameScene->GetPlayer(i);
			CVector3 l_distance = l_player->GetPosition();
			l_distance.Subtract(m_position);
			if (l_distance.Length() < 8.0f)
			{
				l_player->Damage(m_playerNum);
			}
		}

		m_weapon->Delete(m_arraynum);
	}
}