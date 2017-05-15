#pragma once

#define NUM 10
class ItemSprite : public IGameObject
{
public:
	ItemSprite();

	~ItemSprite();

	void Init(int playerNum)
	{
		m_playerNum = playerNum;
	}

	void SetItem(int state);

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
	CTexture*			m_countTexture[NUM];
	CSprite				m_countSprite1;
	CSprite				m_countSprite10;
	int					m_playerNum;				//�v���C���[�̔ԍ�
	int					m_bulletStrikeNum;			//�c�e��
};