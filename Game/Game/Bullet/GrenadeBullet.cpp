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

void GrenadeBullet::Init(CVector3 moveSpeed, Weapon* weapon ,int arrayNum, int playerNum)
{
	Bullet::Init(moveSpeed, weapon, arrayNum, playerNum);
	//キャラクターコントローラーの初期化
	m_characterController.Init(0.3f, 0.3f, m_position);
	//移動速度と重力の設定
	m_moveSpeed.Scale(15.0f);
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
	//弾を打ったプレイヤーとの距離を計算
	Player* l_player = g_gameScene->GetPlayer(m_playerNum);
	CVector3 l_distance = l_player->GetPosition();
	l_distance.Subtract(m_position);
	//弾を打ったプレイヤーからある程度離れていて何かにぶつかれば消去
	if (3.0f < l_distance.Length() && m_characterController.IsCollision())
	{
		l_isDelete = true;
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
		m_weapon->Delete(m_arraynum);
		g_gameScene->ParticleEmit(g_random, g_gameCamera[0]->GetCamera(), 
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
		false,											//!<ビルボード？
		0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		1,												//!<0半透明合成、1加算合成。
		{1.0f, 1.0f, 1.0f}								//!<乗算カラー。
		},
		m_position);
	}
}