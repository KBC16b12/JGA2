#include "stdafx.h"
#include "Weapon.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/GrenadeBullet.h"
#include "../Bullet/BoundBullet.h"
#include "../Bullet/PincerBullet.h"
#include "Player.h"
#include "../HUD/ItemSprite.h"
#include "../Scene/GameScene/GameScene.h"
#include "../PincerAttack/PincerAttack.h"
#include "../Network/Network.h"
#include "HUD/MagazineSprite.h"

Weapon::Weapon()
{
	m_isStrike = true;
	m_isReload = false;
	m_strikeInterval = 0.0f;
	m_reloadTime = 0.0f;
	m_state = BULLETSTATE_NOMAL;
	m_bulletStrikeNum = 0;
	m_magazine = MAGAZINE_SIZE;
	m_itemSprite = NewGO<ItemSprite>(PRIORITY1);
	m_pincer = NewGO<PincerAttack>(PRIORITY0);
	m_magazineSprite = NewGO<MagazineSprite>(PRIORITY0);
	m_isReloadSound = true;
	m_isPincerAttack = false;
}


Weapon::~Weapon()
{
	DeleteGO(m_itemSprite);
	DeleteGO(m_pincer);
	DeleteGO(m_magazineSprite);
}
void Weapon::Init(int playerNum, CAnimation* animation, CLight* light)
{
	m_playerNum = playerNum;
	m_itemSprite->Init(playerNum);
	m_pincer->Init(playerNum);
	m_magazineSprite->Init(playerNum);
	m_playerAnime = animation;
	m_pLight = light;
}

void Weapon::Update()
{
	if (m_isStrike)
	{
			//�e��łĂ��Ԃłڂ������������
		if (Pad(m_playerNum).IsPress(enButtonRB1))
		{
			BulletFilling();
			m_isStrike = false;
		}
	}
	else 
	{
		if (0.11f < m_strikeInterval)
		{
			m_isStrike = true;
			m_strikeInterval = 0.0f;
		}
		//���̒e��łĂ�܂ł̃C���^�[�o���^�C��
		m_strikeInterval += GameTime().GetFrameDeltaTime();
	}
	//�����[�h��
	if (m_isReload)
	{
		if (!m_playerAnime->IsPlay())
		{
			m_magazine = MAGAZINE_SIZE;
			m_isReload = false;
		}
		//����炷�̂Ƀ��O������
		if (0.7f < m_reloadTime && m_isReloadSound)
		{
			CSoundSource* m_reloadSound;
			m_reloadSound = NewGO<CSoundSource>(PRIORITY0);
			m_reloadSound->Init("Assets/sound/reload.wav");
			m_reloadSound->SetVolume(1.3f);
			m_reloadSound->Play(false);
			m_isReloadSound = false;
		}
		m_reloadTime += GameTime().GetFrameDeltaTime();
	}
	else
	{
		//�����[�h�{�^������������
		if (m_magazine != MAGAZINE_SIZE &&  Pad(m_playerNum).IsTrigger(enButtonX) || m_magazine == 0)
		{
			Reload();
		}
	}
	m_itemSprite->SetStrikeNum(m_bulletStrikeNum);
	m_magazineSprite->SetMagazineNum(m_magazine);
}


void Weapon::BulletFilling()
{
	if (m_isReload || g_gameScene == nullptr)
	{
		return;
	}
	CSoundSource* m_shotSound;
	m_shotSound = NewGO<CSoundSource>(PRIORITY0);
	m_shotSound->Init("Assets/sound/shot2.wav");
	m_shotSound->SetVolume(0.3f);
	m_shotSound->Play(false);

	m_playerAnime->PlayAnimation(ANIMESTATE_SHOT);
	Bullet *l_bullet = nullptr;
	//m_state�̏�Ԃɂ��ǂ̒e��ł��o�������߂�
	switch (m_state)
	{
	case BULLETSTATE_NOMAL:
		if (m_isPincerAttack)
		{
			l_bullet = NewGO<PincerBullet>(PRIORITY1);
		}
		else
		{
			l_bullet = NewGO<Bullet>(PRIORITY1);
		}
		break;
	case BULLETSTATE_BOUND:
		l_bullet = NewGO<BoundBullet>(PRIORITY1);
		break;
	case BULLETSTATE_GRENADE:
		l_bullet = NewGO<GrenadeBullet>(PRIORITY1);
		break;
	}
	Player *l_player = g_gameScene->GetPlayer(m_playerNum);
	l_bullet->Init(l_player->GetPosition(), l_player->GetFrontWorldMatrix(), m_playerNum, m_pLight);
	//�A�C�e�����g������Ԃ̏ꍇ�������炷
	m_bulletStrikeNum--;
	m_magazine--;
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
		if (m_state == BULLETSTATE_GRENADE && g_random.GetRandInt() % 2 == 0)
		{
			m_state = BULLETSTATE_BOUND;
		}
	}while (m_state == BULLETSTATE_NOMAL);

	m_itemSprite->SetItem(m_state);
	m_bulletStrikeNum = STRIKE_NUM;

}

void Weapon::Reload()
{
	m_isReload = true;
	m_isReloadSound = true;
	m_reloadTime = 0.0f;
	m_playerAnime->PlayAnimation(ANIMESTATE_RELOAD);
}

void Weapon::PlayerDeath()
{
	m_magazine = MAGAZINE_SIZE;
	m_bulletStrikeNum = 0;
	m_state = BULLETSTATE_NOMAL;
	m_itemSprite->SetStrikeNum(m_bulletStrikeNum);
}