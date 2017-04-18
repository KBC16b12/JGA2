#pragma once

class KillCountSprite : public IGameObject
{
public:
	KillCountSprite();

	~KillCountSprite();

	bool Start()override;

	void Update()override;

	void PostRender(CRenderContext& renderContext, int playernum)override;

private:
	CTexture*					m_texture[10];
	CSprite						m_sprite[2];
	int							m_killcount;		//�L����
};
