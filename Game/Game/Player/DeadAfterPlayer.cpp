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
		if (l_moveSpeed.Length() < 0.1f)
		{
			m_isOnGround = true;
			PhysicsWorld().RemoveRigidBody(&m_rigidBody);
			m_rigidBody.Release();
			ParticleEmit();

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

void DeadAfterPlayer::ParticleEmit()
{
	std::vector<CCamera*> l_camera;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		l_camera.push_back(&g_gameCamera[i]->GetCamera());
	}
	CVector3 l_moveSpeed;
	l_moveSpeed.Cross(CVector3::AxisY, m_moveSpeed);
	l_moveSpeed.Normalize();
	l_moveSpeed.Scale(20.0f);
	l_moveSpeed.Scale(-1.0f);
	CVector3 l_emitPosition = m_position;
	//l_emitPosition.y = 0.0f;
	CParticleEmitter *l_particleEmitter = NewGO<CParticleEmitter>(PRIORITY0);
	l_particleEmitter->Init(g_random, g_gameCamera[0]->GetCamera(),
	{
		"Assets/particle/snowman.png",				//!<テクスチャのファイルパス。
		l_moveSpeed,								//!<初速度。
		0.2f,											//!<寿命。単位は秒。
		0.02f,											//!<発生時間。単位は秒。
		3.0f,											//!<パーティクルの幅。
		3.0f,											//!<パーティクルの高さ。
		{ 5.0f, 0.0f, 4.0f, },							//!<初期位置のランダム幅。
		{ 0.0f, 0.0f, 0.0f, },							//!<初速度のランダム幅。
		{ 0.0f, 0.0f, 0.0f },								//!<速度の積分のときのランダム幅。
		{

			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		},												//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		1,												//!<UVテーブルのサイズ。
		{ 0.0f, 0.0f, 0.0f },								//!<重力。
		true,											//!<死ぬときにフェードアウトする？
		0.1f,											//!<フェードする時間。
		1.0f,											//!<初期アルファ値。
		true,											//!<ビルボード？
		0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		2,												//!<0半透明合成、1加算合成。
		{ 1.0f, 1.0f, 1.0f },								//!<乗算カラー。
		m_time / 2.0f,											//!<パーティクルエミッターの寿命
		1.0f,											//!<サイズスケール
		false
	},
		l_emitPosition, l_camera);

}

void DeadAfterPlayer::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}

void DeadAfterPlayer::Render(CRenderContext& renderContext, int playerNum)
{
	m_skinModel.Draw(renderContext, g_gameCamera[playerNum]->GetViewMatrix(), g_gameCamera[playerNum]->GetProjectionMatrix());
}