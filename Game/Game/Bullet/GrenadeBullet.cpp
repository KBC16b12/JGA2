#include "stdafx.h"
#include "GrenadeBullet.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

GrenadeBullet::GrenadeBullet()
{
}


GrenadeBullet::~GrenadeBullet()
{
}

void GrenadeBullet::Init(CVector3 position, CVector3 moveSpeed, int playerNum)
{
	Bullet::Init(position, moveSpeed, playerNum);
	m_characterController.SetGravity(-35.0f);
	m_moveSpeed.y += 15.0f;
	m_characterController.SetMoveSpeed(m_moveSpeed);
}

void GrenadeBullet::Update()
{
	Bullet::Update();
}

void GrenadeBullet::Move()
{
	m_moveSpeed.y = m_characterController.GetMoveSpeed().y;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	m_position = m_characterController.GetPosition();
}

void GrenadeBullet::DethCheck()
{
	bool l_isDelete = false;
	{
		//弾を打ったプレイヤーとの距離を計算
		Player* l_player = g_gameScene->GetPlayer(m_playerNum);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(m_position);
		//弾を打ったプレイヤーからある程度離れていて何かにぶつかれば消去
		if (3.0f < l_distance.Length() && m_characterController.IsCollision())
		{
			l_isDelete = true;
		}
	}
	if (l_isDelete)
	{
		//爆発で周囲のプレイヤーにダメージ(弾を打ったプレイヤーは除く)
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			Player* l_player = g_gameScene->GetPlayer(i);
			CVector3 l_distance = l_player->GetPosition();
			l_distance.Subtract(m_position);
			if (l_distance.Length() < 8.0f && m_playerNum != i)
			{
				l_player->Damage(m_playerNum);
			}
		}
		DeleteGO(this);
		CParticleEmitter *l_particleEmitter = NewGO<CParticleEmitter>(PRIORITY0);
		l_particleEmitter->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(), 
		{
		"Assets/particle/Explosion5.png",				//!<テクスチャのファイルパス。
		{0.0f, 0.0f, 0.0f},								//!<初速度。
		0.3f,											//!<寿命。単位は秒。
		0.01f,											//!<発生時間。単位は秒。
		6.0f,											//!<パーティクルの幅。
		6.0f,											//!<パーティクルの高さ。
		{3.0f, 3.0f, 3.0f,},							//!<初期位置のランダム幅。
		{0.0f, 0.0f, 0.0f,},							//!<初速度のランダム幅。
		{0.0f, 0.0f, 0.0f},								//!<速度の積分のときのランダム幅。
		{
			{0.333f, 0.0f, 0.5f, 0.166f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f}
		},												//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		1,												//!<UVテーブルのサイズ。
		{0.0f, 0.0f, 0.0f},								//!<重力。
		true,											//!<死ぬときにフェードアウトする？
		0.3f,											//!<フェードする時間。
		1.0f,											//!<初期アルファ値。
		true,											//!<ビルボード？
		0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,												//!<0半透明合成、1加算合成。
		{1.0f, 1.0f, 1.0f}								//!<乗算カラー。
		},
		m_position);
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			l_particleEmitter->AddCamera(g_gameCamera[i]->GetCamera());
		}
	}
}