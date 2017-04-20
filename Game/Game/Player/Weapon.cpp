#include "stdafx.h"
#include "Weapon.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/GrenadeBullet.h"
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

void Weapon::Init(Player* player)
{
	m_player = player;
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
	//配列の空いてる場所を探す
	for (l_ArrayNum = 0;l_ArrayNum < BULLET_NUM;l_ArrayNum++)
	{
		if (m_bullet[l_ArrayNum] == nullptr)
		{
			break;
		}
	}
	Bullet *l_bullet;
	//m_stateの状態によりどの弾を打ち出すか決める
	switch (m_state)
	{
	case BULLETSTATE_NOMAL:
		l_bullet = NewGO<Bullet>(PRIORITY1);
		break;
	case BULLETSTATE_GRENADE:
		l_bullet = NewGO<GrenadeBullet>(PRIORITY1);
		break;
	}
	l_bullet->Init(m_player->GetPosition(), m_player->GetFrontWorldMatrix(), this, l_ArrayNum);
	m_bullet[l_ArrayNum] = l_bullet;
	//アイテムを使った状態の場合数を減らす
	m_bulletStrikeNum--;
	if (m_bulletStrikeNum <= 0)
	{
		m_state = BULLETSTATE_NOMAL;
	}
}

void Weapon::SetWeapon()
{
	//アイテムを取得した場合の更新
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