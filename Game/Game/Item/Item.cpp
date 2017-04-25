#include "stdafx.h"
#include "Item.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"


Item::Item()
{
	m_activeFlg = false;
	m_intervalTime = 0;
	m_rigidBodyFlg = false;
}


Item::~Item()
{
	if (!m_rigidBodyFlg)
	{
		return;
	}
	PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	m_rigidBody.Release();
}

void Item::Init(SMapInfo map_dat)
{
	MapChip::Init(map_dat);
	m_meshCollider.CreateFromSkinModel(&m_SkinModel, m_SkinModelData.GetBody()->GetRootBoneWorldMatrix());
	//���̂̃R���C�_�[��n���B
	m_rbInfo.collider = &m_meshCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	m_rbInfo.mass = 0.0f;
	m_rbInfo.pos = m_position;
	m_rbInfo.rot = m_rotation;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i] = g_gameScene->GetPlayer(i);
	}
}

void Item::Update()
{
	if (m_activeFlg)
	{
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			if (Pad(i).IsTrigger(enButtonY))
			{
				CVector3 l_distance = m_position;
				//�v���C���[�Ƃ̋������v�Z
				l_distance.Subtract(m_player[i]->GetPosition());
				//���̋�����ϐ��Ɋi�[
				float distance = l_distance.Length();
				l_distance.Normalize();
				CVector3 l_playerFrontVector = m_player[i]->GetFrontWorldMatrix();
				l_playerFrontVector.Normalize();
				//���҂𐳋K�����ē��ς��v�Z
				if (distance < 8.0f && l_distance.Dot(l_playerFrontVector) > cos(70))
				{
					m_activeFlg = false;
					m_player[i]->SetWeapon();
					//���̂��폜
					PhysicsWorld().RemoveRigidBody(&m_rigidBody);
					m_rigidBody.Release();
					m_rigidBodyFlg = false;
					break;
				}
			}
		}
	}
	else
	{
		m_intervalTime++;
		if (200 < m_intervalTime)
		{
			m_activeFlg = true;
			m_intervalTime = 0;
			m_rigidBody.Create(m_rbInfo);
			//�쐬�������̂𕨗����[���h�ɒǉ�����B
			PhysicsWorld().AddRigidBody(&m_rigidBody);
			m_rigidBodyFlg = true;
		}
	}
}

void Item::Render(CRenderContext& renderContext, int playernum)
{
	if (!m_activeFlg)
	{
		return;
	}
	m_SkinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}