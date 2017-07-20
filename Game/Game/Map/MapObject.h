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
	*@brief �������֐�
	*/
	void Init(SMapInfo map_dat) override;

	void Init(std::vector<SMapInfo>* map_data);

private:
	CBoxCollider*				m_boxCollider;
	CMeshCollider*				m_meshCollider;		//���b�V���R���C�_�[�B
	CRigidBody*					m_rigidBody;		//���́B
	CMatrix*					m_worldMatrix;
	std::vector<SMapInfo>*		m_map_data;
	CAabb*						m_aabb;
	bool						m_isCulling;
	CObjectFrustumCulling*		m_culling[PLAYER_NUM];
	bool						m_isInstancing;
	CMatrix*					m_instancingWorldMatrix;
	int							m_mapChipNum;

};

