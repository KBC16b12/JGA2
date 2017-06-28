#include "stdafx.h"
#include "TargetSprite.h"


TargetSprite::TargetSprite()
{
	m_isRender = true;
	m_playerNum = 0;
}


TargetSprite::~TargetSprite()
{
}


bool TargetSprite::Start()
{
	m_texture = TextureResources().LoadEx("Assets/sprite/target3.png");
	m_sprite.Init(m_texture);
	m_sprite.SetAlpha(1.0f);
	m_sprite.SetSize({ 200.0f, 200.0f });
	return true;
}

void TargetSprite::Update()
{

}

void TargetSprite::PostRender(CRenderContext& renderContext, int playerNum)
{
	if (m_playerNum != playerNum || !m_isRender)
	{
		return;
	}
	m_sprite.Draw(renderContext);

}