#pragma once

/*
*@brief プレイヤーを殺した数のスプライト
*/

class KillCountSprite : public IGameObject
{
public:
	KillCountSprite();

	~KillCountSprite();

	/*
	*@brief 初期化関数
	*/
	bool Start()override;
	
	/*
	*@brief 更新処理
	*/
	void Update()override;

	void SetData(int killCount)
	{
		m_killcount = killCount;
	}

	/*
	*@brief 描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	void PostRender(CRenderContext& renderContext, int playernum)override;

	void PostRender(CRenderContext& renderContext)override;

private:
	CTexture*					m_texture[10];
	CSprite						m_sprite[2];
	int							m_killcount;		//キル数
};
