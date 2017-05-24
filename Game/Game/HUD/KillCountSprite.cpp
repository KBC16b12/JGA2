#include "stdafx.h"
#include "KillCountSprite.h"


KillCountSprite::KillCountSprite()
{
	m_killcount = 0;

	for (int i = 0;i < 10;i++) {
		char cp[60];
		sprintf(cp, "Assets/sprite/NewNumber/%d.png", i);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0;i < 2;i++) {
		m_sprite[i].Init(m_texture[2]);
		m_sprite[i].SetPosition({ 400.0f + i * 50,320.0f });
		m_sprite[i].SetSize({ 50.0f,50.0f });
	}

}


KillCountSprite::~KillCountSprite()
{
}

bool KillCountSprite::Start()
{
	return true;
}

void KillCountSprite::Update()
{
	int l_num1 = 0, l_num10 = 0;

	l_num10 = (m_killcount % 100) / 10;
	l_num1 = m_killcount % 10;

	m_sprite[0].SetTexture(m_texture[l_num10]);
	m_sprite[1].SetTexture(m_texture[l_num1]);
}

void KillCountSprite::PostRender(CRenderContext& renderContext, int playernum)
{
	if (m_playerNum != playernum)
	{
		return;
	}
	for (int i = 0;i < 2;i++) 
	{
		m_sprite[i].Draw(renderContext);
	}
}

void KillCountSprite::PostRender(CRenderContext& renderContext)
{
	for (int i = 0;i < 2;i++)
	{
		m_sprite[i].Draw(renderContext);
	}
}