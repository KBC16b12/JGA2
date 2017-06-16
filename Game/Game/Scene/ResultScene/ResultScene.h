#pragma once
class ResultScene : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	ResultScene();
	/*!
	*@brief	デストラクタ。
	*/
	~ResultScene();
	/*!
	*@brief	開始関数。
	*@details
	* 初期化などをこの関数に実装してください。</br>
	* この関数がtrueを返すと本館数は以降のフレームでは呼ばれなくなります。</br>
	* そしてゲームオブジェクトの状態が初期化完了になりUpdate関数が呼ばれるようになります。</br>
	*@return	trueが帰ってきたら初期化完了。
	*/
	bool Start() override;
	/*!
	*@brief	更新関数。
	*/
	void Update() override;
	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender(CRenderContext& renderContext) override;

	void PostRender(CRenderContext& renderContext, int cameraNum) override;

	void SetPosition(CVector3 Spos)
	{
		Spos = Spos;
	}

	void SetData(int killCount)
	{
		m_killcount = killCount;
	}

	void SetPlayerNum(int playerNum)
	{
		m_playerNum = playerNum;
	}

	void SetPlayerKillScore(int *killscore)
	{
		for (int i = 0;i < 4;i++)
		{
			pKill[i] = killscore[i];
		}
	}
private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//BGMソース。

	CTexture*					m_SampleTex;						//!<サンプルのテクスチャ。
	CSprite						m_Sample;							//!<サンプルのスプライト。

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;

	CVector3					Spos;
	int							m_rcount;
	int							m_killcount;		//キル数
	int							m_playerNum;
	int							pNum[4];
	int                         pKill[4];
	int							tmp = 0;
	CTexture*					m_texture[4];
	CSprite						m_sprite[4];
	CSprite						m_sprite2[4];
};

