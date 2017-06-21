#include "stdafx.h"
#include "GrenadeBullet.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"
#include "../Player/Weapon.h"

GrenadeBullet::GrenadeBullet()
{
}


GrenadeBullet::~GrenadeBullet()
{
}

void GrenadeBullet::Init(CVector3 position, CVector3 moveSpeed, int playerNum, CLight* light)
{
	Bullet::Init(position, moveSpeed, playerNum, light);
	m_characterController.SetGravity(-35.0f);
	float l_moveSpeedY = 10.0f;
	l_moveSpeedY += g_random.GetRandDouble() * 10.0f;
	CVector3 l_moveSpeedX;
	l_moveSpeedX.Cross(m_moveSpeed, CVector3::AxisY);
	m_moveSpeed.y += l_moveSpeedY;
	l_moveSpeedX.Normalize();
	if (g_random.GetRandInt() % 2 == 0)
	{
		l_moveSpeedX.Scale(-1.0f);
	}
	m_moveSpeed.Scale(0.7f);
	l_moveSpeedX.Scale(g_random.GetRandDouble() * 5.0f);
	m_moveSpeed.Add(l_moveSpeedX);
	m_characterController.SetMoveSpeed(m_moveSpeed);
}


void GrenadeBullet::DeathCheck()
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
			if (l_distance.Length() <11.0f && m_playerNum != i)
			{
				PlayerDamage(l_player);
			}
		}
		DeleteGO(this);
		std::vector<CCamera*> l_camera;
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			l_camera.push_back(&g_gameCamera[i]->GetCamera());
		}
		CVector3 l_emitPosition = m_position;
		l_emitPosition.y += 2.0f;
		CParticleEmitter *l_particleEmitter = NewGO<CParticleEmitter>(PRIORITY0);
		l_particleEmitter->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(), 
		{
		"Assets/particle/Explosion5.png",				//!<テクスチャのファイルパス。
		{0.0f, 0.0f, 0.0f},								//!<初速度。
		0.1f,											//!<寿命。単位は秒。
		0.01f,											//!<発生時間。単位は秒。
		3.0f,											//!<パーティクルの幅。
		3.0f,											//!<パーティクルの高さ。
		{2.5f, 2.5f, 2.5f,},							//!<初期位置のランダム幅。
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
		0.05f,											//!<フェードする時間。
		1.0f,											//!<初期アルファ値。
		true,											//!<ビルボード？
		0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		3,												//!<0半透明合成、1加算合成。
		{0.1f, 0.1f, 0.1f},								//!<乗算カラー。
		0.15f,											//!<パーティクルエミッターの寿命
		1.2f											//!<サイズスケール
		},
		l_emitPosition, l_camera);
		CParticleEmitter *l_particleEmitter2 = NewGO<CParticleEmitter>(PRIORITY0);
		l_particleEmitter2->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(),
		{
			"Assets/particle/Explosion1.png",				//!<テクスチャのファイルパス。
			{ 0.0f, 0.0f, 0.0f },								//!<初速度。
			0.1f,											//!<寿命。単位は秒。
			0.01f,											//!<発生時間。単位は秒。
			3.0f,											//!<パーティクルの幅。
			3.0f,											//!<パーティクルの高さ。
			{ 2.0f, 2.0f, 2.0f, },							//!<初期位置のランダム幅。
			{ 0.0f, 0.0f, 0.0f, },							//!<初速度のランダム幅。
			{ 0.0f, 0.0f, 0.0f },								//!<速度の積分のときのランダム幅。
			{
				{ 0.333f, 0.0f, 0.5f, 0.166f },
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			},												//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
			1,												//!<UVテーブルのサイズ。
			{ 0.0f, 0.0f, 0.0f },								//!<重力。
			true,											//!<死ぬときにフェードアウトする？
			0.05f,											//!<フェードする時間。
			1.0f,											//!<初期アルファ値。
			true,											//!<ビルボード？
			0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
			3,												//!<0半透明合成、1加算合成。
			{ 0.1f, 0.1f, 0.1f },								//!<乗算カラー。
			0.15f,											//!<パーティクルエミッターの寿命
			1.2f											//!<サイズスケール
		},
			l_emitPosition, l_camera);
	}
}