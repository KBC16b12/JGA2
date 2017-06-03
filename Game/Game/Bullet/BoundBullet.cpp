#include "stdafx.h"
#include "BoundBullet.h"
#include "Scene/GameScene/GameScene.h"
#include "Player/Player.h"


BoundBullet::BoundBullet()
{
	m_timer = 0.0f;
}


BoundBullet::~BoundBullet()
{
}

void BoundBullet::Init(CVector3 position, CVector3 movespeed, int playerNum)
{
	Bullet::Init(position, movespeed, playerNum);
}

void BoundBullet::Move()
{
	CVector3 l_wallNormal = m_characterController.Execute(GameTime().GetFrameDeltaTime());
	m_position = m_characterController.GetPosition();
	//跳ね返す処理
	if (m_characterController.IsCollision())
	{
		//壁の法線の外積で壁ずりのベクトルを求める
		l_wallNormal.Cross(CVector3::AxisY);
		l_wallNormal.Normalize();
		//移動ベクトルにその壁ずりベクトルを射影する
		float l_scale = l_wallNormal.Dot(m_moveSpeed) * 2.0f;
		CVector3 l_direction = l_wallNormal;
		l_direction.Scale(l_scale);
		m_moveSpeed.Subtract(l_direction, m_moveSpeed);
	}
	m_characterController.SetMoveSpeed(m_moveSpeed);
}

void BoundBullet::DeathCheck()
{
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		Player *l_player = g_gameScene->GetPlayer(i);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(m_position);
		if (m_playerNum != i)
		{
			//自分以外のプレイヤーに当たったら
			if (l_distance.Length() < 3.0f)
			{
				DeleteGO(this);
				l_player->Damage(m_playerNum, BULLET_DAMAGE);
				break;
			}
		}
		else
		{
			//一定時間経過で消滅
			m_timer += GameTime().GetFrameDeltaTime();
			if (20.0f < m_timer)
			{
				DeleteGO(this);
				break;
			}
		}
	}

	
}
