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
	//�d�͐ݒ�
	//m_characterController.SetGravity(-0.1f);
	m_moveSpeed.y += 1.0f;
	//m_characterController.SetMoveSpeed(m_moveSpeed);
	//�ł����u�ԂɎ����ɓ������Ă��܂����ߏ����������Ă���
	for (int i = 0;i < 2;i++)
	{
		//m_characterController.Execute(1.0f);
	}
	//m_characterController.SetCollisionFlg(false);
}

void GrenadeBullet::Update()
{
	Bullet::Update();
}

void GrenadeBullet::DethCheck()
{
	//�������ɓ����������������
	//if (m_characterController.IsCollision())
	{
		//�������Ƃ��ɔ����ŋ߂��ɂ���v���C���[�Ƀ_���[�W��^����
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