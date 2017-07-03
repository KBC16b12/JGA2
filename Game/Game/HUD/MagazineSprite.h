#pragma once
class MagazineSprite : public IGameObject
{
public:
	MagazineSprite();
	~MagazineSprite();

	void Init(int playerNum)
	{
		m_playerNum = playerNum;
	}

	bool Start()override;

	void Update()override;

	void SetMagazineNum(int bulletNum)
	{
		m_magazineNum = bulletNum;
	}

	void PostRender(CRenderContext& renderContext)override;

	void PostRender(CRenderContext& renderContext, int playerNum)override;
private:
	CTexture*			m_countTexture[DECI];
	CSprite				m_countSprite1;
	CSprite				m_countSprite10;
	int					m_playerNum;				//�v���C���[�̔ԍ�
	int					m_magazineNum;				//�c�e��
};

