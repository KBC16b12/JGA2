#include "stdafx.h"
#include "Item.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Map/MapChip.h"


Item::Item()
{
	m_isDeth = false;
}


Item::~Item()
{
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}

void Item::Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModel)
{
	m_position = position;
	m_rotation = rotation;
	m_SkinModel.Init(skinModel);
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);

	m_meshCollider.CreateFromSkinModel(&m_SkinModel, skinModel->GetRootBoneWorldMatrix());
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

bool Item::Start()
{
	return true;
}

void Item::Update()
{
	if (m_isDeth)
	{
		return;
	}
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		if (Pad(i).IsTrigger(enButtonY))
		{
			CVector3 l_distance = m_position;
			Player* l_player = g_gameScene->GetPlayer(i);
			//プレイヤーとの距離を計算
			l_distance.Subtract(l_player->GetPosition());
			//その距離を変数に格納
			float distance = l_distance.Length();
			l_distance.y = 0.0f;
			l_distance.Normalize();
			CVector3 l_playerFrontVector = l_player->GetFrontWorldMatrix();
			l_playerFrontVector.Normalize();
			//両者を正規化して内積を計算
			if (distance < 4.0f && l_distance.Dot(l_playerFrontVector) > cos(CMath::DegToRad(15)))
			{
				Deth(l_player);
				break;
			}
		}
	}
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);
}

void Item::Render(CRenderContext& renderContext, int playernum)
{
	m_SkinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}

void Item::Render(CRenderContext& renderContext)
{
	m_SkinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}

void Item::Deth(Player *player)
{
	m_isDeth = true;
}