#include "stdafx.h"
#include "Item.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Map/MapChip.h"


Item::Item()
{
	m_isDeath = false;
	m_isSpriteRender = false;
}


Item::~Item()
{
	//PhysicsWorld().RemoveRigidBody(&m_rigidBody);
	//m_rigidBody.Release();
}

void Item::Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModel)
{
	m_position = position;
	m_rotation = rotation;
	CQuaternion l_rotation;
	l_rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(-90));
	m_rotation.Multiply(l_rotation);
	m_SkinModel.Init(skinModel);
	m_SkinModel.SetShadowCasterFlag(true);
	m_SkinModel.SetShadowReceiverFlag(true);
	m_SkinModel.SetLight(&g_defaultLight);
	m_SkinModel.SetAtomosphereParam(enAtomosphereFuncObjectFromAtomosphere);
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);

	//m_meshCollider.CreateFromSkinModel(&m_SkinModel, skinModel->GetRootBoneWorldMatrix());
	//RigidBodyInfo rbInfo;
	////���̂̃R���C�_�[��n���B
	//rbInfo.collider = &m_meshCollider;
	////���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	//rbInfo.mass = 0.0f;
	//rbInfo.pos = m_position;
	//rbInfo.rot = m_rotation;

	//m_rigidBody.Create(rbInfo);
	////�쐬�������̂𕨗����[���h�ɒǉ�����B
	//PhysicsWorld().AddRigidBody(&m_rigidBody);
}

bool Item::Start()
{
	m_texture = TextureResources().Load("Assets/sprite/a.png");
	m_sprite.Init(m_texture);
	m_sprite.SetSize(m_size);
	m_sprite.SetPosition({ 0.0f, 0.0f });
	return true;
}

void Item::Update()
{
	if (m_isDeath)
	{
		return;
	}
	if (g_gameScene == nullptr)
	{
		return;
	}
	m_isSpriteRender = false;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		CVector3 l_distance = m_position;
		Player* l_player = g_gameScene->GetPlayer(i);
		//�v���C���[�Ƃ̋������v�Z
		l_distance.Subtract(l_player->GetPosition());
		//���̋�����ϐ��Ɋi�[
		float distance = l_distance.Length();
		l_distance.y = 0.0f;
		l_distance.Normalize();
		CVector3 l_playerFrontVector = l_player->GetFrontWorldMatrix();
		l_playerFrontVector.Normalize();
		//���҂𐳋K�����ē��ς��v�Z
		float l_dot = l_distance.Dot(l_playerFrontVector);
		if (distance < 10.0f)
		{
			if (Pad(i).IsTrigger(enButtonA) && l_dot > cos(CMath::DegToRad(15)))
			{
				Death(l_player);
				break;
			}
			if (cos(CMath::DegToRad(90)) < l_dot)
			{
				m_isSpriteRender = true;
				SetSpritePosition();
			}
		}
	}
	m_SkinModel.Update(m_position, m_rotation, CVector3::One);
}

void Item::Render(CRenderContext& renderContext, int playerNum)
{
	renderContext.SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	renderContext.SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	if (m_isSpriteRender)
	{
		m_sprite.SetPosition(m_screenPos[playerNum]);
		m_sprite.SetSize(m_spriteSize[playerNum]);
		m_sprite.Draw(renderContext);
	}
	renderContext.SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_SkinModel.Draw(renderContext, g_gameCamera[playerNum]->GetViewMatrix(), g_gameCamera[playerNum]->GetProjectionMatrix());
}

void Item::Render(CRenderContext& renderContext)
{
	if (m_isSpriteRender)
	{
		m_sprite.Draw(renderContext);
	}
	m_SkinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}

void Item::PostRender(CRenderContext& renderContext, int playerNum)
{

}

void Item::PostRender(CRenderContext& renderContext)
{
}

void Item::Death(Player *player)
{
	m_isDeath = true;
}

void Item::SetSpritePosition()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		CMatrix m_worldMatrix = m_SkinModel.GetWorldMatrix();
		m_worldMatrix.m[3][1] += 3.0f;
		m_worldMatrix.Mul(m_worldMatrix, g_gameCamera[i]->GetViewMatrix());
		m_worldMatrix.Mul(m_worldMatrix, g_gameCamera[i]->GetProjectionMatrix());
		float zBuffer = m_worldMatrix.m[3][3];
		m_screenPos[i].x = m_worldMatrix.m[3][0] / zBuffer * Engine().GetScreenWidth() / 2;
		m_screenPos[i].y = m_worldMatrix.m[3][1] / zBuffer * Engine().GetScreenHeight() / 2;
		CVector2 l_size = m_size;
		l_size.Div(zBuffer);
		m_spriteSize[i] = l_size;
	}
}