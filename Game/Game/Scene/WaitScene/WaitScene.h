#pragma once

#define JOIN_NUM 4

class WaitScene : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	WaitScene();

	/*!
	*@brief	デストラクタ。
	*/
	~WaitScene();

	/*!
	*@brief 初期化関数
	*/
	void Init(bool isHost);

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

private:

	void Host();

	void Join();

	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//BGMソース。

	CTexture*					m_SampleTex;						//!<サンプルのテクスチャ。
	CSprite						m_Sample;							//!<サンプルのスプライト。

	RunStat						m_runstat = enFadeIn;

	SceneData					m_scenedata;

	bool						m_isHost;

	ULONG						m_addressList[JOIN_NUM];

	int							m_IPcount;
};

