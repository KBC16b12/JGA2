#pragma once
#include "PlayerMeshCommon.h"

class DeadAfterPlayer : public IGameObject
{
public:
	DeadAfterPlayer();

	~DeadAfterPlayer();

	void Init(CSkinModelData* modelData, CVector3 position, CQuaternion rotation, CLight light, CVector3 bulletPosition, PlayerMeshState meshState);

	void Update()override;

	void Render(CRenderContext& renderContext, int playerNum)override;

	void Render(CRenderContext& renderContext)override;

private:
	CSkinModelData			m_skinModelData;
	CSkinModel				m_skinModel;
	CVector3				m_moveSpeed;
	CVector3				m_position;
	CQuaternion				m_rotation;
	CLight					m_light;
	float					m_time;
	CSphereCollider			m_sphereCollider;		//���b�V���R���C�_�[�B
	CRigidBody				m_rigidBody;		//���́B
	float					m_isOnGround;
};

