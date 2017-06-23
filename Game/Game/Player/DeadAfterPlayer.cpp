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
	//剛体のコライダーを渡す。
	rbInfo.collider = &m_sphereCollider;
	//剛体の質量。0.0だと動かないオブジェクト。背景などは0.0にしよう。
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
	//作成した剛体を物理ワールドに追加する。
	PhysicsWorld().AddRigidBody(&m_rigidBody);

	//m_rigidBody.GetBody()->applyForce(btVector3(m_moveSpeed.x, m_moveSpeed.y, m_moveSpeed.z), btVector3(0.0f, 0.0f, 0.0f));
	m_rigidBody.GetBody()->setLinearVelocity(btVector3(m_moveSpeed.x, m_moveSpeed.y, m_moveSpeed.z));

	//モデルが全部埋まるまでの時間(Bodyだけ補正を加える、ただし回転しない場合に限る
	float l_manip = 0.0f;
	if (!strcmp("Body", meshState.name))
	{
		l_manip = 0.7f;
	}
	m_time = meshState.radius * 2.0f + l_manip;
}

void DeadAfterPlayer::Update()
{
	//飛んでいるとき
	if (!m_isOnGround)
	{
		btRigidBody* btBody = m_rigidBody.GetBody();
		//剛体を動かす。

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
		//移動速度が一定以下になったら地面に沈む
		if (l_moveSpeed.Length() < 0.3f)
		{
			m_isOnGround = true;
			PhysicsWorld().RemoveRigidBody(&m_rigidBody);
			m_rigidBody.Release();
		}
	}
	//動きが止まって地面に沈み始めるとき
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