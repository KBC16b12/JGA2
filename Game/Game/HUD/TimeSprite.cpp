#include "stdafx.h"
#include "TimeSprite.h"

/*
*@brief ゲーム内の時間を表示するスプライト
*/
TimeSprite::TimeSprite()
{
	m_time = 120.0f;
	for (int i = 0;i < 10;i++) {
		char cp[60];
		sprintf(cp, "Assets/sprite/NewNumber/%d.png", i);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0;i < 3;i++) {
		m_sprite[i].Init(m_texture[9]);
		float size = 65.0f;
		m_sprite[i].SetPosition({ -size + i * size,320.0f });
		m_sprite[i].SetSize({ size,size });
	}
	m_isFinish = false;
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
	if (m_time > 0.0f) {
		m_time -= GameTime().GetFrameDeltaTime();
	}
	else
	{
		m_isFinish = true;
	}
	int l_n1 = 0, l_n10 = 0, l_n100 = 0;

	l_n100 = (int)m_time / 100;			//3桁目の数字
	l_n10 = ((int)m_time % 100) / 10;	//2桁目の数字
	l_n1 = (int)m_time % 10;			    //1桁目の数字

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

void TimeSprite::PostRender(CRenderContext& renderContext)
{
	for (int i = 0;i < 3;i++)
	{
		m_sprite[i].Draw(renderContext);
	}
}