#pragma once

#include "Map/MapChip.h"

class MapObject : public MapChip
{
public:
	MapObject();


	~MapObject();


	/*!
	*@brief 初期化関数
	*/
	void Init(SMapInfo map_dat) override;

private:
	CMeshCollider				m_meshCollider;		//メッシュコライダー。
	CRigidBody					m_rigidBody;		//剛体。

};

