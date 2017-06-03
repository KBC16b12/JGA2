#include "stdafx.h"
#include "MagazineSprite.h"


MagazineSprite::MagazineSprite()
{
	m_playerNum = 0;
	m_magazineNum = 0;
}


MagazineSprite::~MagazineSprite()
{
}


bool MagazineSprite::Start()
{
	for (int i = 0; i < NUM; i++)
	{
		char l_filePath[128];
		sprintf(l_filePath, "Assets/sprite/NewNumber/%d.png", i);
		m_countTexture[i] = TextureResources().LoadEx(l_filePath);
	}

	int spriteNum1 = m_magazineNum % 10;
	int spriteNum10 = m_magazineNum / 10;
	m_countSprite1.Init(m_countTexture[spriteNum1]);
	m_countSprite10.Init(m_countTexture[spriteNum10]);

	//サイズの設定
	float l_sizeY = 100.0f;
	float l_itemSizeX = 100.0f;
	float l_countSizeX = 70.0f;
	m_countSprite1.SetSize({ l_countSizeX, l_sizeY });
	m_countSprite10.SetSize({ l_countSizeX, l_sizeY });

	//座標の設定
	float l_positionY = -270.0f;
	float l_positionX = -550.0f;
	m_countSprite10.SetPosition({ l_positionX + 100.0f, l_positionY });
	m_countSprite1.SetPosition({ l_positionX + 200.0f, l_positionY });
	return true;
}

void MagazineSprite::Update()
{
	int spriteNum1 = m_magazineNum % 10;
	int spriteNum10 = m_magazineNum / 10;
	m_countSprite1.SetTexture(m_countTexture[spriteNum1]);
	m_countSprite10.SetTexture(m_countTexture[spriteNum10]);
}

void MagazineSprite::PostRender(CRenderContext& renderContext)
{

	m_countSprite1.Draw(renderContext);
	m_countSprite10.Draw(renderContext);
}

void MagazineSprite::PostRender(CRenderContext& renderContext, int playerNum)
{
	if (m_playerNum != playerNum)
	{
		return;
	}
	m_countSprite1.Draw(renderContext);
	m_countSprite10.Draw(renderContext);
}