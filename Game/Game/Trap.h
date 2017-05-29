#pragma once
#include "../Game/Map/MapChip.h"

class Player;

class TrapA : public MapChip
{
public:
	TrapA();
	~TrapA();
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
	bool						m_stup;
	bool						m_activeFlg;			//死んでるか生きてるか
	CMeshCollider				m_meshCollider;			//メッシュコライダー。
	CRigidBody					m_rigidBody;			//剛体。
	bool						Flg;
	float						l_playerRadiusF = 3.0f;
};