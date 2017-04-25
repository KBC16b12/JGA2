#pragma once

#include "MapChip.h"

class Map : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	Map();
	
	/*!
	*@brief	デストラクタ。
	*/
	~Map();
	
	/*!
	*@brief 初期化関数
	*@details 
	*/
	void Init(std::vector<SMapInfo> map_dat);

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
	void Render(CRenderContext& renderContext, int playernum) override;

	void PostRender(CRenderContext& renderContext, int playernum) override;

	const std::vector<MapChip*>& GetMap()
	{
		return m_mapchip;
	}

private:

	std::vector<MapChip*>		m_mapchip;			//マップチップリスト
};

