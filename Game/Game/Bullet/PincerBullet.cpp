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
	m_skinModel.SetLight(m_pLight);
	m_skinModel.SetTechnique(enTecShaderHandle_PincerBullet);
	return true;
}


void PincerBullet::PlayerDamage(Player *player)
{
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
			l_player->Damage(m_playerNum, l_player->GetMaxHP(), m_moveSpeed);
		}
	}
	CSoundSource *l_pincerSound = NewGO<CSoundSource>(PRIORITY0);
	l_pincerSound->Init("Assets/sound/exprosion.wav");
	l_pincerSound->Play(false);
	std::vector<CCamera*> l_camera;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		l_camera.push_back(&g_gameCamera[i]->GetCamera());
	}
	CParticleEmitter *l_particleEmitter = NewGO<CParticleEmitter>(PRIORITY0);
	l_particleEmitter->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(),
	{
		"Assets/particle/Explosion1.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
		{ 0.0f, 0.0f, 0.0f },								//!<�����x�B
		0.15f,											//!<�����B�P�ʂ͕b�B
		0.1f,											//!<�������ԁB�P�ʂ͕b�B
		3.0f,											//!<�p�[�e�B�N���̕��B
		3.0f,											//!<�p�[�e�B�N���̍����B
		{ 0.0f, 0.0f, 0.0f },							//!<�����ʒu�̃����_�����B
		{ 0.0f, 0.0f, 0.0f },							//!<�����x�̃����_�����B
		{ 0.0f, 0.0f, 0.0f },								//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{
			{ 0.333f, 0.f, 0.5f, 0.166f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		},												//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		1,												//!<UV�e�[�u���̃T�C�Y�B
		{ 0.0f, 0.0f, 0.0f },								//!<�d�́B
		true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.05f,											//!<�t�F�[�h���鎞�ԁB
		1.0f,											//!<�����A���t�@�l�B
		true,											//!<�r���{�[�h�H
		0.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		2,												//!<0�����������A1���Z�����B
		{ 1.0f, 1.0f, 1.0f },								//!<��Z�J���[�B
		0.15f,											//!<�p�[�e�B�N���G�~�b�^�[�̎���
		2.0f											//!<�T�C�Y�X�P�[��
	},
		m_position, l_camera);
}