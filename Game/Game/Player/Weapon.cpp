#include "stdafx.h"
#include "Weapon.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/GrenadeBullet.h"
#include "../Bullet/BoundBullet.h"
#include "Player.h"
#include "../HUD/ItemSprite.h"
#include "../Scene/GameScene/GameScene.h"
#include "../PincerAttack/PincerAttack.h"
#include "../Network/Network.h"

Weapon::Weapon()
{
	m_isStrike = true;
	m_strikeInterval = 0.0f;
	m_state = BULLETSTATE_NOMAL;
	m_bulletStrikeNum = 0;
	m_itemSprite = NewGO<ItemSprite>(PRIORITY1);
	m_pincer = NewGO<PincerAttack>(PRIORITY0);
}


Weapon::~Weapon()
{
	DeleteGO(m_itemSprite);
}

void Weapon::Init(int playerNum)
{
	m_playerNum = playerNum;
	m_itemSprite->Init(playerNum);
	m_pincer->Init(playerNum);
}

bool Weapon::Start()
{
	return true;
}

void Weapon::Update()
{
	if (m_isStrike)
	{
			//弾を打てる状態でぼたんを押したら
		if (Pad(m_playerNum).IsTrigger(enButtonRB1))
		{
			BulletFilling();
			m_isStrike = false;
		}
	}
	else 
	{
		//次の弾を打てるまでのインターバルタイム
		m_strikeInterval += GameTime().GetFrameDeltaTime();
		if (0.2f < m_strikeInterval)
		{
			m_isStrike = true;
			m_strikeInterval = 0.0f;
		}
	}
	m_itemSprite->SetStrikeNum(m_bulletStrikeNum);
}


void Weapon::BulletFilling()
{
	Bullet *l_bullet;
	//m_stateの状態によりどの弾を打ち出すか決める
	switch (m_state)
	{
	case BULLETSTATE_NOMAL:
		l_bullet = NewGO<Bullet>(PRIORITY1);
		break;
	case BULLETSTATE_BOUND:
		l_bullet = NewGO<BoundBullet>(PRIORITY1);
		break;
	case BULLETSTATE_GRENADE:
		l_bullet = NewGO<GrenadeBullet>(PRIORITY1);
		break;

	}
	Player *l_player = g_gameScene->GetPlayer(m_playerNum);
	l_bullet->Init(l_player->GetPosition(), l_player->GetFrontWorldMatrix(), m_playerNum);
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
	}while (m_state == BULLETSTATE_NOMAL);

	m_itemSprite->SetItem(m_state);
	m_bulletStrikeNum = STRIKE_NUM;

}

