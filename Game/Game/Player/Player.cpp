#include "stdafx.h"
#include "Player.h"
#include "../Bar/Bar.h"

Player::Player()
{
	//HPê›íË
	m_maxhp = m_hp = 15;

	m_HPbar = NewGO<Bar>(0);
	m_HPbar->SetBarPos({ -592.95f, 320.0f });
	m_HPbar->SetBarMaxSize({ 230.5f, 14.2f });
	m_HPbar->SetGaugePos({ -600.0f, 320.0f });
	m_HPbar->SetGaugeMaxSize({ 245.0f, 31.5f });
	m_HPbar->SetBarPath("Assets/sprite/Green.png");
	m_HPbar->SetGaugePath("Assets/sprite/Black.png");
	m_HPbar->SetBarBackPath("Assets/sprite/Black.png");
	m_HPbar->SetData(m_hp, m_maxhp);
	m_HPbar->SetBerQuarter(Bar::enBarQuarter::enQuaLeft);
}

Player::~Player()
{
	DeleteGO(m_HPbar);
}

bool Player::Start()
{
	return true;
}

void Player::Update()
{
	UpdateHPBar();
}

void Player::Render(CRenderContext& renderContext)
{

}

void Player::UpdateHPBar()
{
	if (m_maxhp <= 0)
	{
		return;
	}

	//HP50%à»è„
	if (50.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_HPbar->SetBarPath("Assets/sprite/Green.png");
	}
	//HP10%à»è„50%à»â∫
	else if (10.0f < (float)m_hp / (float)m_maxhp * 100.0f)
	{
		m_HPbar->SetBarPath("Assets/sprite/Blue.png");
	}
	//HP10%ñ¢ñû
	else
	{
		m_HPbar->SetBarPath("Assets/sprite/Red.png");
	}
	m_HPbar->SetData(m_hp, m_maxhp);
}