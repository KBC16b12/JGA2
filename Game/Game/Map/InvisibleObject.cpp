#include "stdafx.h"
#include "InvisibleObject.h"
#include "Camera/GameCamera.h"


InvisibleObject::InvisibleObject()
{
}


InvisibleObject::~InvisibleObject()
{
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}


void InvisibleObject::Init(SMapInfo map_dat)
{
	MapChip::Init(map_dat);
	m_SkinModel.SetShadowCasterFlag(false);
	m_meshCollider.CreateFromSkinModel(&m_SkinModel, m_SkinModelData.GetBody()->GetRootBoneWorldMatrix());
	RigidBodyInfo rbInfo;
	//剛体のコライダーを渡す。
	rbInfo.collider = &m_meshCollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;

	m_rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(&m_rigidBody);
}

bool InvisibleObject::Start()
{
	
	return true;
}

void InvisibleObject::Update()
{
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);
}

void InvisibleObject::Render(CRenderContext& renderContext, int cameranum)
{
}
