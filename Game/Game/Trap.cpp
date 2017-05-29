#include "stdafx.h"
#include "Trap.h"
#include "Camera\GameCamera.h"
#include "../Game/Scene/GameScene/GameScene.h"
#include "../Game/Player/Player.h"

TrapA::TrapA()
{
	m_activeFlg = true;
	Flg = false;
	m_stup = false;
}

TrapA::~TrapA()
{
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}

void TrapA::Init(SMapInfo map_dat)
{
	MapChip::Init(map_dat);
	RigidBodyInfo m_rbInfo;
	m_meshCollider.CreateFromSkinModel(&m_SkinModel, m_SkinModelData.GetBody()->GetRootBoneWorldMatrix());
	//���̂̃R���C�_�[��n���B
	m_rbInfo.collider = &m_meshCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	m_rbInfo.mass = 0.0f;
	m_rbInfo.pos = CVector3(0.0f,0.0f,0.0f);
	m_rbInfo.rot = m_rotation;
	m_rigidBody.Create(m_rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&m_rigidBody);

}

void TrapA::Update()
{
	if (g_gameScene == nullptr)
	{
		return;
	}
	if (m_stup == true)
	{
		return;
	}
	for (int i = 0; i < PLAYER_NUM; i++)
	{

		Player* l_player = g_gameScene->GetPlayer(i);
		CVector3 l_distanceF = l_player->GetPosition();
		l_distanceF.Subtract(m_position);

		if (!l_player->IsStup() && l_distanceF.Length() < l_playerRadiusF)
		{
			l_player->Startup();
			m_stup = true;
			SetActiveFlag(false);
		}
	
	}
}

void TrapA::Render(CRenderContext& renderContext, int playernum)
{
	m_SkinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}