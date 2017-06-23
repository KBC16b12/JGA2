#include "stdafx.h"
#include "DeadAfterPlayer.h"
#include "Camera/GameCamera.h"



DeadAfterPlayer::DeadAfterPlayer()
{
	m_time = 0.0f;
	m_moveSpeed = CVector3::Zero;
	m_isOnGround = false;
}


DeadAfterPlayer::~DeadAfterPlayer()
{
}

void DeadAfterPlayer::Init(CSkinModelData* modeldata, CVector3 position, CQuaternion rotation, CLight light, CVector3 bulletPosition, PlayerMeshState meshState)
{
	m_skinModelData.CloneModelData(*modeldata, NULL);
	m_skinModel.Init(&m_skinModelData);
	m_position = position;
	m_rotation = rotation;
	m_light = light;
	bulletPosition.y = 0.6f;
	m_moveSpeed.Subtract(m_position, bulletPosition);
	m_moveSpeed.Normalize();
	//m_moveSpeed.y = 0.8f + g_random.GetRandDouble() * 1.0f;
	m_moveSpeed.Scale(80.0f);
	m_skinModel.SetLight(&m_light);
	m_sphereCollider.Create(meshState.radius);
	RigidBodyInfo rbInfo;
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &m_sphereCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 1.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;

	m_rigidBody.Create(rbInfo);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(rbInfo.pos.x, rbInfo.pos.y, rbInfo.pos.z));
	transform.setRotation(btQuaternion(rbInfo.rot.x, rbInfo.rot.y, rbInfo.rot.z, rbInfo.rot.w));
	m_rigidBody.GetBody()->setWorldTransform(transform);
	//m_rigidBody.GetBody()->Se
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&m_rigidBody);

	//m_rigidBody.GetBody()->applyForce(btVector3(m_moveSpeed.x, m_moveSpeed.y, m_moveSpeed.z), btVector3(0.0f, 0.0f, 0.0f));
	m_rigidBody.GetBody()->setLinearVelocity(btVector3(m_moveSpeed.x, m_moveSpeed.y, m_moveSpeed.z));

	//���f�����S�����܂�܂ł̎���(Body�����␳��������A��������]���Ȃ��ꍇ�Ɍ���
	float l_manip = 0.0f;
	if (!strcmp("Body", meshState.name))
	{
		l_manip = 0.7f;
	}
	m_time = meshState.radius * 2.0f + l_manip;
}

void DeadAfterPlayer::Update()
{
	//���ł���Ƃ�
	if (!m_isOnGround)
	{
		btRigidBody* btBody = m_rigidBody.GetBody();
		//���̂𓮂����B

		btTransform& trans = btBody->getWorldTransform();
		m_position.Set(trans.getOrigin());
		btQuaternion l_rotation = trans.getRotation();
		m_rotation.x = l_rotation.x();
		m_rotation.y = l_rotation.y();
		m_rotation.z = l_rotation.z();
		m_rotation.w = l_rotation.w();

		CVector3 l_moveSpeed;
		btVector3 l_linearVel = btBody->getLinearVelocity();
		l_moveSpeed.Set(l_linearVel);
		//�ړ����x�����ȉ��ɂȂ�����n�ʂɒ���
		if (l_moveSpeed.Length() < 0.3f)
		{
			m_isOnGround = true;
			PhysicsWorld().RemoveRigidBody(&m_rigidBody);
			m_rigidBody.Release();
		}
	}
	//�������~�܂��Ēn�ʂɒ��ݎn�߂�Ƃ�
	else
	{
		float l_deltaTime = GameTime().GetFrameDeltaTime() * 2.0f;
		m_time -= l_deltaTime;
		m_position.y -= l_deltaTime;
		if (m_time < 0.0f)
		{
			DeleteGO(this);
		}
	}
	m_skinModel.Update(m_position, m_rotation, CVector3::One);

}

void DeadAfterPlayer::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}

void DeadAfterPlayer::Render(CRenderContext& renderContext, int playerNum)
{
	m_skinModel.Draw(renderContext, g_gameCamera[playerNum]->GetViewMatrix(), g_gameCamera[playerNum]->GetProjectionMatrix());
}