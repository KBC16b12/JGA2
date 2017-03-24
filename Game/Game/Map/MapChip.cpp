#include "stdafx.h"
#include "MapChip.h"
#include "../Camera/GameCamera.h"

MapChip::MapChip()
{
	//初期化
	m_position = CVector3::Zero;
	m_rotation = CQuaternion::Identity;
	m_scale = CVector3::Zero;
}

MapChip::~MapChip()
{
	//剛体削除
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}

void MapChip::Init(SMapInfo map_dat)
{
	//スキンモデルロード
	char modelPath[1024];
	sprintf(modelPath, "Assets/modelData/%s.x", map_dat.s_modelName);
	SkinModelDataResources().Load(m_SkinModelData, modelPath, NULL, false, 1);
	m_SkinModel.Init(m_SkinModelData.GetBody());
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);

	//基本情報設定
	m_position = map_dat.s_position;
	m_rotation = map_dat.s_rotation;
	m_scale = map_dat.s_scale;

	m_SkinModel.Update(m_position, m_rotation, m_scale);

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