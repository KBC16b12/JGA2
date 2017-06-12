#include "stdafx.h"
#include "PlayerRecovery.h"


PlayerRecovery::PlayerRecovery()
{
	m_hp = nullptr;
	m_recoveryTime = 0.0f;
	m_lifeRecoveryInterval = 0.0f;
	m_isBulletHit = false;
}


PlayerRecovery::~PlayerRecovery()
{
}

void PlayerRecovery::Update()
{
	//被弾してなかったら戻る
	if (!m_isBulletHit)
	{
		return;
	}
	m_recoveryTime += GameTime().GetFrameDeltaTime();
	//被弾してからある程度じかんがたつと回復し始める
	if (3.0f < m_recoveryTime)
	{
		m_lifeRecoveryInterval += GameTime().GetFrameDeltaTime();
		//徐々に回復してるように見せるためのインターバルタイム
		if (1.0f < m_lifeRecoveryInterval)
		{
			*m_hp += 1;
			if (m_maxHp <= *m_hp)
			{
				*m_hp = m_maxHp;
				m_isBulletHit = false;
			}
			m_lifeRecoveryInterval = 0.0f;

		}
	}

}

void PlayerRecovery::Hit()
{
	m_isBulletHit = true;
	m_lifeRecoveryInterval = 0.0f;
	m_recoveryTime = 0.0f;

}
