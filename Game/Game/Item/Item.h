#pragma once
#include "../Map/MapChip.h"

/*
マップにあるアイテムボックスのクラス
*/

class Player;

class Item : public MapChip
{
public:
	Item();

	~Item();
	/*
	*@brief 初期化関数
	*/
	void Init(SMapInfo map_dat)override;

	/*
	*@brief 更新関数
	*/
	void Update()override;

	/*
	*@brief 描画関数
	*@brief playernum どのプレイヤーの視点で描画したいか
	*/
	void Render(CRenderContext& renderContext, int playernum)override;

private:
	RigidBodyInfo				m_rbInfo;				//剛体のステータス
	bool						m_activeFlg;			//死んでるか生きてるか
	CMeshCollider				m_meshCollider;			//メッシュコライダー。
	CRigidBody					m_rigidBody;			//剛体。
	Player*						m_player[PLAYER_NUM];	//プレイヤーのインスタンス
	int							m_intervalTime;			//壊されてから次出現するまでの時間をカウントする変数
	bool						m_rigidBodyFlg;
};
