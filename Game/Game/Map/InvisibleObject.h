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
	*@brief 初期化関数
	*/
	void Init(SMapInfo map_dat) override;

private:
	CMeshCollider				m_meshCollider;		//メッシュコライダー。
	CRigidBody					m_rigidBody;		//剛体。
	CLight						m_skyLight;
};

