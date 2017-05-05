#include "stdafx.h"
#include "Weapon.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/GrenadeBullet.h"
#include "../Bullet/BoundBullet.h"
#include "Player.h"

Weapon::Weapon()
{
	for (int i = 0;i < BULLET_NUM;i++)
	{
		m_bullet[i] = nullptr;
	}
	m_state = BULLETSTATE_NOMAL;
	m_bulletStrikeNum = 30;
}


Weapon::~Weapon()
{
}

void Weapon::Init(Player* player, int playerNum)
{
	m_player = player;
	m_playerNum = playerNum;
}

bool Weapon::Start()
{
	return true;
}

void Weapon::Update()
{
}


void Weapon::BulletFilling()
{
	int l_ArrayNum;
	//�z��̋󂢂Ă�ꏊ��T��
	for (l_ArrayNum = 0;l_ArrayNum < BULLET_NUM;l_ArrayNum++)
	{
		if (m_bullet[l_ArrayNum] == nullptr)
		{
			break;
		}
	}
	Bullet *l_bullet;
	//m_state�̏�Ԃɂ��ǂ̒e��ł��o�������߂�
	switch (m_state)
	{
	case BULLETSTATE_NOMAL:
		l_bullet = NewGO<GrenadeBullet>(PRIORITY1);
		break;
	case BULLETSTATE_BOUND:
		l_bullet = NewGO<BoundBullet>(PRIORITY1);
		break;
	case BULLETSTATE_GRENADE:

		l_bullet = NewGO<GrenadeBullet>(PRIORITY1);
		break;
	}
	l_bullet->Init(m_player->GetFrontWorldMatrix(), this, l_ArrayNum, m_playerNum);
	m_bullet[l_ArrayNum] = l_bullet;
	//�A�C�e�����g������Ԃ̏ꍇ�������炷
	m_bulletStrikeNum--;
	if (m_bulletStrikeNum <= 0)
	{
		m_state = BULLETSTATE_NOMAL;
	}
}

void Weapon::SetWeapon()
{
	//�A�C�e�����擾�����ꍇ�̍X�V
	do
	{
		m_state = (BULLETSTATE)(g_random.GetRandInt() % BULLETSTATE_NUM);
	} while (m_state == BULLETSTATE_NOMAL);
	m_bulletStrikeNum = STRIKE_NUM;

}

void Weapon::Render(CRenderContext& renderContext, int playernum)
{
	for (int i = 0;i < BULLET_NUM;i++)
	{
		if (m_bullet[i] != nullptr)
		{
			m_bullet[i]->Render(renderContext, playernum);
		}
	}
}

void Weapon::OnDestroy()
{
	for (int i = 0; i < BULLET_NUM;i++)
	{
		if (m_bullet[i] != nullptr)
		{
			DeleteGO(m_bullet[i]);
			m_bullet[i] = nullptr;
		}
	}
}