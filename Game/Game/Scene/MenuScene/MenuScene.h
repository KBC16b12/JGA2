#pragma once
class MenuScene : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	MenuScene();

	/*!
	*@brief	デストラクタ。
	*/
	~MenuScene();

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
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext);

	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender(CRenderContext& renderContext) override;

	void PostRender(CRenderContext& renderContext, int cameraNum) override;

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	CSoundSource*				m_bgm;							//BGMソース。

	CTexture*					m_SampleTex;					//!<サンプルのテクスチャ。
	CSprite						m_Sample;						//!<サンプルのスプライト。

	RunStat						m_runstat = enFadeIn;			//フェードステータス

	SceneData					m_scenedata;					//画面遷移データ
};

