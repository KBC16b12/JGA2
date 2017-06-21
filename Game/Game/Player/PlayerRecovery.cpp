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

bool PlayerRecovery::Start()
{
	m_texture = TextureResources().Load("Assets/sprite/Damage/1.png");
	m_sprite.Init(m_texture);
	m_sprite.SetTechnique("Recovery");
	m_sprite.SetSize({ (float)(Engine().GetScreenWidth()), (float)(Engine().GetScreenHeight()) });
	return true;
}

void PlayerRecovery::Recovery()
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

void PlayerRecovery::Update()
{
	float l_spriteAlpha = (float)*m_hp / m_maxHp;
	l_spriteAlpha = 1.0f - l_spriteAlpha;
	m_sprite.SetAlpha(l_spriteAlpha);
	Recovery();
}

void PlayerRecovery::Hit()
{
	m_isBulletHit = true;
	m_lifeRecoveryInterval = 0.0f;
	m_recoveryTime = 0.0f;
}

void PlayerRecovery::PostRender(CRenderContext& renderContext, int playerNum)
{
	if (m_playerNum != playerNum)
	{
		return;
	}
	m_sprite.Draw(renderContext);
}

void PlayerRecovery::PostRender(CRenderContext& renderContext)
{
	m_sprite.Draw(renderContext);
}