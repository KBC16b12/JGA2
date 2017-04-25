#pragma once
#include "C:\Users\kbc16\Documents\github\JGA2\Game\Game\Map\MapChip.h"
class MapObject : public MapChip
{
public:
	MapObject();


	~MapObject();


	/*!
	*@brief 初期化関数
	*/
	void Init(SMapInfo map_dat) override;

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
	*@param[in]		playernum			どのプレイヤーに描画したいか
	*/
	void Render(CRenderContext& renderContext, int cameranum) override;

private:
	CMeshCollider				m_meshCollider;		//メッシュコライダー。
	CRigidBody					m_rigidBody;		//剛体。

};

