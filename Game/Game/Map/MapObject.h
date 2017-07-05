#pragma once

#include "Map/MapChip.h"
class MapObject : public MapChip
{
public:
	MapObject();


	~MapObject();

	bool Start()override;

	void Update()override;

	void Render(CRenderContext& renderContext, int cameraNum)override;


	/*!
	*@brief 初期化関数
	*/
	void Init(SMapInfo map_dat) override;

	void Init(std::vector<SMapInfo>* map_data);

private:
	CMeshCollider*				m_meshCollider;		//メッシュコライダー。
	CRigidBody*					m_rigidBody;		//剛体。
	CMatrix*					m_worldMatrix;
	std::vector<SMapInfo>*		m_map_data;
	CAabb						m_aabb;
	bool						m_isCulling;
	CObjectFrustumCulling		m_culling[PLAYER_NUM];
	bool						m_isInstancing;
};

