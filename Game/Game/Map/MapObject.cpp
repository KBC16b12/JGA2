#include "stdafx.h"
#include "MapObject.h"
#include "Camera/GameCamera.h"

MapObject::MapObject()
{
	m_isInstancing = false;
	m_isCulling = true;
}


MapObject::~MapObject()
{
	if (m_isInstancing)
	{
		for (int i = 0; i < m_map_data->size(); i++)
		{
			PhysicsWorld().RemoveRigidBody(&m_rigidBody[i]);
			m_rigidBody[i].Release();
		}
		delete[] m_rigidBody;
		delete[] m_worldMatrix;
		delete[] m_meshCollider;
		delete m_map_data;
	}
	else
	{
		PhysicsWorld().RemoveRigidBody(m_rigidBody);
		m_rigidBody->Release();
		delete m_rigidBody;
		delete m_meshCollider;
	}
}


void MapObject::Init(SMapInfo map_dat)
{
	MapChip::Init(map_dat);
	if (!strcmp(map_dat.s_modelName, "Road") ||
		!strcmp(map_dat.s_modelName, "T_Roads") ||
		!strcmp(map_dat.s_modelName, "L_Roads") ||
		!strcmp(map_dat.s_modelName, "X_Roads"))
	{
		m_isCulling = false;
	}
	m_meshCollider = new CMeshCollider;
	m_meshCollider->CreateFromSkinModel(&m_SkinModel, m_SkinModelData.GetBody()->GetRootBoneWorldMatrix());
	RigidBodyInfo rbInfo;
	//剛体のコライダーを渡す。
	rbInfo.collider = m_meshCollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	m_rigidBody = new CRigidBody;
	m_rigidBody->Create(rbInfo);
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(m_rigidBody);

	CVector3 aabbMax = m_meshCollider->GetAABBMax();
	CVector3 aabbMin = m_meshCollider->GetAABBMin();
	CVector3 centerPos;
	centerPos.Add(aabbMax, aabbMin);
	centerPos.Scale(0.5f);
	CVector3 aabbHalfSize;
	aabbHalfSize.Subtract(aabbMax, aabbMin);
	aabbHalfSize.Scale(0.5f);
	m_aabb.Init(centerPos, aabbHalfSize);
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_culling[i].Init(g_gameCamera[i]->GetCamera());
	}

}

void MapObject::Init(std::vector<SMapInfo>* map_data)
{
	m_map_data = map_data;
	int l_mapChipNum = m_map_data->size();
	//スキンモデルロード
	char modelPath[1024];
	sprintf(modelPath, "Assets/modelData/%s.x", (*map_data)[0].s_modelName);
	SkinModelDataResources().Load(m_SkinModelData, modelPath, NULL, true, l_mapChipNum);
	m_SkinModel.Init(m_SkinModelData.GetBody());
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);
	m_worldMatrix = new CMatrix[l_mapChipNum];
	m_rigidBody = new CRigidBody[l_mapChipNum];
	m_meshCollider = new CMeshCollider[l_mapChipNum];

	int i = 0;
	for (SMapInfo mapInfo : *map_data)
	{
		CQuaternion l_mulRot;
		l_mulRot.SetRotation(CVector3::AxisX, CMath::DegToRad(90));
		mapInfo.s_rotation.Multiply(l_mulRot);
		CMatrix	l_trans;
		CMatrix l_rotation;
		l_trans.MakeTranslation(mapInfo.s_position);
		l_rotation.MakeRotationFromQuaternion(mapInfo.s_rotation);
		m_worldMatrix[i].Mul(l_rotation, l_trans);
		i++;
	}
	m_SkinModel.UpdateInstancingDrawData(m_worldMatrix);
	m_SkinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	i = 0;
	CMatrix *l_boneWorldMatrix = m_SkinModelData.GetBody()->GetRootBoneWorldMatrix();
	for (SMapInfo mapInfo : *map_data)
	{
		CMatrix l_world;
		l_world.Mul(*l_boneWorldMatrix, m_worldMatrix[i]);
		m_meshCollider[i].CreateFromSkinModel(&m_SkinModel, &l_world);
		RigidBodyInfo rbInfo;
		//剛体のコライダーを渡す。
		rbInfo.collider = &m_meshCollider[i];
		//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
		rbInfo.mass = 0.0f;

		m_rigidBody[i].Create(rbInfo);
		//作成した剛体を物理ワールドに追加する。
		PhysicsWorld().AddRigidBody(&m_rigidBody[i]);
		i++;
	}
	m_isInstancing = true;
}

bool MapObject::Start()
{
	return true;
}

void MapObject::Update()
{
	if (m_isInstancing)
	{
		m_SkinModel.EntryShadowMap();
	}
	else
	{
		m_SkinModel.EntryShadowMap();
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			m_culling[i].Execute(m_aabb);
		}
	}
}

void MapObject::Render(CRenderContext& renderContext, int cameranum)
{
	if (m_isInstancing)
	{
		//renderContext.SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_SkinModel.Draw(renderContext, g_gameCamera[cameranum]->GetViewMatrix(), g_gameCamera[cameranum]->GetProjectionMatrix());
		//renderContext.SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
	else
	{
		if (m_isCulling && m_culling[cameranum].IsCulling())
		{
			return;
		}
		m_SkinModel.Draw(renderContext, g_gameCamera[cameranum]->GetViewMatrix(), g_gameCamera[cameranum]->GetProjectionMatrix());
	}

}
