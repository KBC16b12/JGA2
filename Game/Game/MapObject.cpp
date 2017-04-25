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
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &m_meshCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	m_rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&m_rigidBody);
}

bool MapObject::Start()
{
	return true;
}

void MapObject::Update()
{
	m_SkinModel.Update(m_position, m_rotation, m_scale);
}

void MapObject::Render(CRenderContext& renderContext, int cameranum)
{
	MapChip::Render(renderContext, cameranum);
}