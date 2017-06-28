#pragma once
class TargetSprite : public IGameObject
{
public:
	TargetSprite();

	~TargetSprite();

	bool Start()override;

	void Update()override;

	void PostRender(CRenderContext& renderContext, int playerNum)override;

	void Init(int playerNum)
	{
		m_playerNum = playerNum;
	}

	void SetRenderFlg(bool isRender)
	{
		m_isRender = isRender;
	}

private:

	bool m_isRender;
	int m_playerNum;
	CSprite m_sprite;
	CTexture* m_texture;
};

