#include "stdafx.h"
#include "ItemSprite.h"


ItemSprite::ItemSprite()
{
	m_playerNum = 0;
	m_bulletStrikeNum = 0;
	
}



ItemSprite::~ItemSprite()
{
}

bool ItemSprite::Start()
{
	m_boundTexture = TextureResources().LoadEx("Assets/sprite/bound.jpg");
	m_grenadeTexture = TextureResources().LoadEx("Assets/sprite/bomb.jpg");
	for (int i = 0;i < NUM;i++)
	{
		char l_filePath[128];
		sprintf(l_filePath, "Assets/sprite/NewNumber/%d.png", i);
		m_countTexture[i] = TextureResources().LoadEx(l_filePath);
	}

	int spriteNum1 = m_bulletStrikeNum % 10;
	int spriteNum10 = m_bulletStrikeNum / 10;
	m_countSprite1.Init(m_countTexture[spriteNum1]);
	m_countSprite10.Init(m_countTexture[spriteNum10]);
	m_itemSprite.Init(m_boundTexture);
	
	//サイズの設定
	float l_sizeY = 100.0f;
	float l_itemSizeX = 100.0f;
	float l_countSizeX = 70.0f;
	m_itemSprite.SetSize({ l_itemSizeX, l_sizeY });
	m_countSprite1.SetSize({ l_countSizeX, l_sizeY });
	m_countSprite10.SetSize({ l_countSizeX, l_sizeY });

	//座標の設定
	float l_positionY = -270.0f;
	float l_positionX = 50.0f;
	m_itemSprite.SetPosition({ l_positionY, l_positionY});
	m_countSprite10.SetPosition({ l_positionY + 100.0f, l_positionY });
	m_countSprite1.SetPosition({ l_positionY + 200.0f, l_positionY });
	return true;

}

void ItemSprite::SetItem(BULLETSTATE state)
{
	switch (state)
	{
	case BULLETSTATE_BOUND:
		m_itemSprite.SetTexture(m_boundTexture);
		break;
	case BULLETSTATE_GRENADE:
		m_itemSprite.SetTexture(m_grenadeTexture);
		break;
	}
}

void ItemSprite::Update()
{

	int spriteNum1 = m_bulletStrikeNum % 10;
	int spriteNum10 = m_bulletStrikeNum / 10;
	m_countSprite1.SetTexture(m_countTexture[spriteNum1]);
	m_countSprite10.SetTexture(m_countTexture[spriteNum10]);
}

void ItemSprite::PostRender(CRenderContext& renderContext)
{
	if (m_bulletStrikeNum <= 0)
	{
		return;
	}
	m_itemSprite.Draw(renderContext);
	m_countSprite1.Draw(renderContext);
	m_countSprite10.Draw(renderContext);
}

void ItemSprite::PostRender(CRenderContext& renderContext, int playerNum)
{
	if (m_playerNum != playerNum)
	{
		return;
	}
	if (m_bulletStrikeNum <= 0)
	{
		return;
	}
	m_itemSprite.Draw(renderContext);
	m_countSprite1.Draw(renderContext);
	m_countSprite10.Draw(renderContext);
}