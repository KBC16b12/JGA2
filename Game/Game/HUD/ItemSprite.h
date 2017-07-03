#pragma once
#include "Player/Weapon.h"

class ItemSprite : public IGameObject
{
public:
	ItemSprite();

	~ItemSprite();

	void Init(int playerNum)
	{
		m_playerNum = playerNum;
	}

	void SetItem(BULLETSTATE state);

	bool Start()override;

	void Update()override;

	void SetStrikeNum(int bulletNum)
	{
		m_bulletStrikeNum = bulletNum;
	}

	void PostRender(CRenderContext& renderContext)override;

	void PostRender(CRenderContext& renderContext, int playerNum)override;
private:

	CTexture*			m_grenadeTexture;
	CTexture*			m_boundTexture;
	CSprite				m_itemSprite;
	CTexture*			m_countTexture[DECI];
	CSprite				m_countSprite1;
	CSprite				m_countSprite10;
	int					m_playerNum;				//プレイヤーの番号
	int					m_bulletStrikeNum;			//残弾数
};