#include "stdafx.h"
#include "PincerBullet.h"
#include "Player/Player.h"
#include "Scene/GameScene/GameScene.h"
#include "Camera/GameCamera.h"

PincerBullet::PincerBullet()
{
}


PincerBullet::~PincerBullet()
{
}

bool PincerBullet::Start()
{
	m_modelData.CloneModelData(*g_bulletModel, NULL);
	m_skinModel.Init(&m_modelData);
	m_skinModel.SetLight(&m_light);
	m_skinModel.SetTechnique(enTecShaderHandle_PincerBullet);
	m_skinModel.SetShadowCasterFlag(true);
	return true;
}


void PincerBullet::PlayerDamage(Player *player)
{
	if (!player->IsActive() || player->IsInvincible())
	{
		return;
	}
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if (i == m_playerNum)
		{
			continue;
		}
		Player *l_player = g_gameScene->GetPlayer(i);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(player->GetPosition());
		if (l_distance.Length() < 100.0f)
		{

			int l_playerDamage = l_player->GetHP();
			if (player->GetPlayerNum() != i)
			{
				l_playerDamage--;
			}
			l_player->Damage(m_playerNum, l_playerDamage, m_moveSpeed, m_position);
		}
	}
	CSoundSource *l_pincerSound = NewGO<CSoundSource>(PRIORITY0);
	l_pincerSound->Init("Assets/sound/exprosion.wav");
	l_pincerSound->SetVolume(1.5f);
	l_pincerSound->Play(false);
	std::vector<CCamera*> l_camera;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		l_camera.push_back(&g_gameCamera[i]->GetCamera());
	}
	CParticleEmitter *l_particleEmitter = NewGO<CParticleEmitter>(PRIORITY0);
	l_particleEmitter->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(),
	{
		"Assets/particle/Explosion1.png",				//!<テクスチャのファイルパス。
		{ 0.0f, 0.0f, 0.0f },								//!<初速度。
		0.45f,											//!<寿命。単位は秒。
		0.3f,											//!<発生時間。単位は秒。
		3.0f,											//!<パーティクルの幅。
		3.0f,											//!<パーティクルの高さ。
		{ 0.0f, 0.0f, 0.0f },							//!<初期位置のランダム幅。
		{ 0.0f, 0.0f, 0.0f },							//!<初速度のランダム幅。
		{ 0.0f, 0.0f, 0.0f },								//!<速度の積分のときのランダム幅。
		{
			{ 0.333f, 0.f, 0.5f, 0.166f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		},												//!<UVテーブル。最大4まで保持できる。xが左上のu、yが左上のv、zが右下のu、wが右下のvになる。
		1,												//!<UVテーブルのサイズ。
		{ 0.0f, 0.0f, 0.0f },								//!<重力。
		true,											//!<死ぬときにフェードアウトする？
		0.15f,											//!<フェードする時間。
		1.0f,											//!<初期アルファ値。
		true,											//!<ビルボード？
		0.0f,											//!<輝度。ブルームが有効になっているとこれを強くすると光が溢れます。
		2,												//!<0半透明合成、1加算合成。
		{ 1.0f, 1.0f, 1.0f },								//!<乗算カラー。
		0.15f,											//!<パーティクルエミッターの寿命
		2.0f											//!<サイズスケール
	},
		m_position, l_camera);
}