#pragma once
#include "MapChip.h"

class InvisibleObject : public MapChip
{
public:
	InvisibleObject();
	~InvisibleObject();

	bool Start()override;

	void Update()override;

	void Render(CRenderContext& renderContext, int cameraNum)override;


	/*!
	*@brief �������֐�
	*/
	void Init(SMapInfo map_dat) override;

private:
	CMeshCollider				m_meshCollider;		//���b�V���R���C�_�[�B
	CRigidBody					m_rigidBody;		//���́B
	CLight						m_skyLight;
};

