#include "stdafx.h"
#include "MapObject.h"
#include "Camera/GameCamera.h"

MapObject::MapObject()
{
}


MapObject::~MapObject()
{
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}


void MapObject::Init(SMapInfo map_dat)
{
	MapChip::Init(map_dat);
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

	CVector3 aabbMax = m_meshCollider.GetAABBMax();
	CVector3 aabbMin = m_meshCollider.GetAABBMin();
	CVector3 centerPos;
	centerPos.Add(aabbMax, aabbMin);
	centerPos.Scale(0.5f);
	CVector3 aabbHalfSize;
	aabbHalfSize.Subtract(aabbMax, aabbMin);
	aabbHalfSize.Scale(0.5f);
	m_aabb.Init(centerPos, aabbHalfSize);

}

bool MapObject::Start()
{
	return true;
}

/*void MapObject::Update()
{
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);
}*/

void MapObject::Render(CRenderContext& renderContext, int cameranum)
{
	MapChip::Render(renderContext, cameranum);
}
