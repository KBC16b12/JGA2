#pragma once

#include "Map/MapChip.h"

class MapObject : public MapChip
{
public:
	MapObject();


	~MapObject();


	/*!
	*@brief �������֐�
	*/
	void Init(SMapInfo map_dat) override;

private:
	CMeshCollider				m_meshCollider;		//���b�V���R���C�_�[�B
	CRigidBody					m_rigidBody;		//���́B

};

