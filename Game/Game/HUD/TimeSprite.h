#pragma once

class TimeSprite : public IGameObject
{
public:
	TimeSprite();

	~TimeSprite();
	
	/*
	*@brief 初期化関数
	*/
	bool Start()override;

	/*
	*@brief 更新処理
	*/
	void Update()override;

	/*
	*@brief 描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	void PostRender(CRenderContext& renderContext, int playernum);

	void PostRender(CRenderContext& renderContext);

private:
	int m_time;				//タイマー
	CSprite						m_sprite[3];
	CTexture*					m_texture[10];
};