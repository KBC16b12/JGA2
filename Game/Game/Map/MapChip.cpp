#include "stdafx.h"
#include "MapChip.h"
#include "../Camera/GameCamera.h"

MapChip::MapChip()
{
	//������
	m_position = CVector3::Zero;
	m_rotation = CQuaternion::Identity;
	m_scale = CVector3::Zero;
}

MapChip::~MapChip()
{
	//���̍폜
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}

void MapChip::Init(SMapInfo map_dat)
{
	//�X�L�����f�����[�h
	char modelPath[1024];
	sprintf(modelPath, "Assets/modelData/%s.x", map_dat.s_modelName);
	SkinModelDataResources().Load(m_SkinModelData, modelPath, NULL, false, 1);
	m_SkinModel.Init(m_SkinModelData.GetBody());
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);

	//��{���ݒ�
	m_position = map_dat.s_position;
	m_rotation = map_dat.s_rotation;
	m_scale = map_dat.s_scale;

	m_SkinModel.Update(m_position, m_rotation, m_scale);

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

bool MapChip::Start()
{
	return true;
}

void MapChip::Update()
{
}

void MapChip::Render(CRenderContext& renderContext)
{
	m_SkinModel.Draw(renderContext, g_gameCamera->GetViewMatrix(),
		g_gameCamera->GetProjectionMatrix());
}