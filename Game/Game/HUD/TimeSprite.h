#pragma once

class TimeSprite : public IGameObject
{
public:
	TimeSprite();

	~TimeSprite();

	bool Start()override;

	void Update()override;

	void PostRender(CRenderContext& renderContext);
private:
	int m_time;				//タイマー
	CSprite						m_sprite[3];
	CTexture*					m_texture[10];
};