#include "stdafx.h"
#include "TimeSprite.h"


TimeSprite::TimeSprite()
{
	m_time = 999;
	for (int i = 0;i < 10;i++) {
		char cp[60];
		sprintf(cp, "Assets/sprite/NewNumber/%d.png", i);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0;i < 3;i++) {
		m_sprite[i].Init(m_texture[9]);
		m_sprite[i].SetPosition({ -50.0f + i * 50,320.0f });
		m_sprite[i].SetSize({ 50.0f,50.0f });
	}
}


TimeSprite::~TimeSprite()
{
}

bool TimeSprite::Start()
{
	return true;
}

void TimeSprite::Update()
{
	if (m_time > 0) {
		m_time--;
	}
	int l_n1 = 0, l_n10 = 0, l_n100 = 0;

	l_n100 = m_time / 100;			//3Œ…–Ú‚Ì”š
	l_n10 = (m_time % 100) / 10;	//2Œ…–Ú‚Ì”š
	l_n1 = m_time % 10;			    //1Œ…–Ú‚Ì”š

	m_sprite[0].SetTexture(m_texture[l_n100]);
	m_sprite[1].SetTexture(m_texture[l_n10]);
	m_sprite[2].SetTexture(m_texture[l_n1]);
}

void TimeSprite::PostRender(CRenderContext& renderContext, int playernum)
{
	for (int i = 0;i < 3;i++)
	{
		m_sprite[i].Draw(renderContext);
	}
}