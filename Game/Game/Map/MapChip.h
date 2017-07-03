#pragma once

struct Status::SMapInfo;

/*
*@brief マップチップとしてマップに配置するオブジェクトの親クラス
*/

class MapChip : public IGameObject
{
public:	
	/*!
	*@brief	コンストラクタ。
	*/
	MapChip();

	/*!
	*@brief	デストラクタ。
	*/
	~MapChip();

	/*!
	*@brief 初期化関数
	*/
	virtual void Init(SMapInfo map_dat);

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
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void Render(CRenderContext& renderContext) override;

	void Render(CRenderContext& renderContext, int cameranum) override;

	bool IsLoadEnd()
	{
		return m_SkinModelData.IsLoadEnd();
	}

protected:
	/*
	*@brief 読み込みなどモデルの初期化関数
	*/
	virtual void ModelInit(const char * modelName);

protected:
	CSkinModel					m_SkinModel;		//スキンモデル
	CSkinModelDataHandle		m_SkinModelData;	//スキンモデルのハンドル
	CVector3					m_position;			//座標
	CQuaternion					m_rotation;			//回転
	CObjectFrustumCulling		m_culling[PLAYER_NUM];
	CAabb						m_aabb;
	bool						m_isCulling;
};

