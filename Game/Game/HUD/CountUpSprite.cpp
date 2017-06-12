#include "stdafx.h"
#include "CountUpSprite.h"


CountUpSprite::CountUpSprite()
{
}


CountUpSprite::~CountUpSprite()
{
}

bool CountUpSprite::Start()
{
	m_texturePlus = TextureResources().LoadEx("Assets/sprite/plus.png");
	m_textureNum = TextureResources().LoadEx("Assets/sprite/NewNumber/1.png");
	m_spritePlus.Init(m_texturePlus);
	m_spriteNum.Init(m_textureNum);
	CVector2 size = { 100.0f, 100.0f };
	m_spriteNum.SetSize(size);
	size.Scale(0.6f);
	m_spritePlus.SetSize(size);
	CVector2 position = { 0.0f, 0.0f };
	m_spriteNum.SetPosition(position);
	position.x -= 65.0f;
	m_spritePlus.SetPosition(position);
	m_alpha = 1.0f;
	return true;
}

void CountUpSprite::Update()
{

	//少しずつ上に上がってく
	float l_moveSpeed = 10.0f;
	CVector2 position = m_spriteNum.GetPosition();
	position.y += l_moveSpeed;
	m_spriteNum.SetPosition(position);
	position = m_spritePlus.GetPosition();
	position.y += l_moveSpeed;
	//少しづつフェードアウトしていく
	m_spritePlus.SetPosition(position);
	m_spriteNum.SetAlpha(m_alpha);
	m_spritePlus.SetAlpha(m_alpha);
	m_alpha -= 0.05f;
	if (m_alpha <= 0.0f)
	{
		DeleteGO(this);
	}
}

void CountUpSprite::PostRender(CRenderContext& renderContext)
{
	m_spriteNum.Draw(renderContext);
	m_spritePlus.Draw(renderContext);
}

void CountUpSprite::PostRender(CRenderContext& renderContext, int playerNum)
{
	if (m_playerNum != playerNum)
	{
		return;
	}
	m_spriteNum.Draw(renderContext);
	m_spritePlus.Draw(renderContext);
}


