#include "stdafx.h"
#include "BoundBullet.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"


BoundBullet::BoundBullet()
{
	m_timer = 0.0f;
}


BoundBullet::~BoundBullet()
{
}

void BoundBullet::Init(CVector3 movespeed, Weapon* weapon, int arrayNum, int playerNum)
{
	Bullet::Init(movespeed, weapon, arrayNum, playerNum);
}

void BoundBullet::Move()
{
	CVector3 l_wallNormal = m_characterController.Execute(GameTime().GetFrameDeltaTime());
	m_position = m_characterController.GetPosition();
	//���˕Ԃ�����
	if (m_characterController.IsCollision())
	{
		//�ǂ̖@���̊O�ςŕǂ���̃x�N�g�������߂�
		l_wallNormal.Cross(CVector3::AxisY);
		l_wallNormal.Normalize();
		//�ړ��x�N�g���ɂ��̕ǂ���x�N�g�����ˉe����
		float l_scale = l_wallNormal.Dot(m_moveSpeed) * 2.0f;
		CVector3 l_direction = l_wallNormal;
		l_direction.Scale(l_scale);
		m_moveSpeed.Subtract(l_direction, m_moveSpeed);
	}
	m_characterController.SetMoveSpeed(m_moveSpeed);
}

void BoundBullet::DethCheck()
{
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		Player *l_player = g_gameScene->GetPlayer(i);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(m_position);
		if (m_playerNum != i)
		{
			//�����ȊO�̃v���C���[�ɓ���������
			if (l_distance.Length() < 3.0f)
			{
				m_weapon->Delete(m_arraynum);
				l_player->Damage(m_playerNum);
				break;
			}
		}
		else
		{
			//��莞�Ԍo�߂ŏ���
			m_timer += GameTime().GetFrameDeltaTime();
			if (20.0f < m_timer)
			{
				m_weapon->Delete(m_arraynum);
				break;
			}
		}
	}

	
}
