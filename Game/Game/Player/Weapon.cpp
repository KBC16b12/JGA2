#include "stdafx.h"
#include "Weapon.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/GrenadeBullet.h"
#include "../Bullet/BoundBullet.h"
#include "Player.h"
#include "../HUD/ItemSprite.h"
#include "../Scene/GameScene/GameScene.h"
#include "../PincerAttack/PincerAttack.h"

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
		//�e��łĂ��Ԃłڂ������������
		if (Pad(m_playerNum).IsTrigger(enButtonRB1))
		{
			BulletFilling();
			m_isStrike = false;
		}
	}
	else 
	{
		//���̒e��łĂ�܂ł̃C���^�[�o���^�C��
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
	//m_state�̏�Ԃɂ��ǂ̒e��ł��o�������߂�
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
	}while (m_state == BULLETSTATE_NOMAL);

	m_itemSprite->SetItem(m_state);
	m_bulletStrikeNum = STRIKE_NUM;

}

