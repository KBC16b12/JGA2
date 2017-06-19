#pragma once

class CountUpSprite : public IGameObject
{
public:
	CountUpSprite();

	~CountUpSprite();

	void Init(int playerNum)
	{
		m_playerNum = playerNum;
	}

	bool Start();

	void Update();

	void PostRender(CRenderContext& renderContext);

	void PostRender(CRenderContext& renderContext, int playerNum);
private:

	CTexture *m_texturePlus;
	CSprite		m_spritePlus;
	CTexture *m_textureNum;
	CSprite		m_spriteNum;
	int			m_playerNum;
	float		m_alpha;
};

