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
		//�e��ł����v���C���[�Ƃ̋������v�Z
		Player* l_player = g_gameScene->GetPlayer(m_playerNum);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(m_position);
		//�e��ł����v���C���[���炠����x����Ă��ĉ����ɂԂ���Ώ���
		if (3.0f < l_distance.Length() && m_characterController.IsCollision())
		{
			l_isDelete = true;
		}
	}
	if (l_isDelete)
	{
		//�����Ŏ��͂̃v���C���[�Ƀ_���[�W(�e��ł����v���C���[�͏���)
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			Player* l_player = g_gameScene->GetPlayer(i);
			CVector3 l_distance = l_player->GetPosition();
			l_distance.Subtract(m_position);
			if (l_distance.Length() < 8.0f && m_playerNum != i)
			{
				l_player->Damage(m_playerNum, GRENADE_DAMAGE);
			}
		}
		DeleteGO(this);
		CParticleEmitter *l_particleEmitter = NewGO<CParticleEmitter>(PRIORITY0);
		l_particleEmitter->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(), 
		{
		"Assets/particle/Explosion5.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
		{0.0f, 0.0f, 0.0f},								//!<�����x�B
		0.1f,											//!<�����B�P�ʂ͕b�B
		0.01f,											//!<�������ԁB�P�ʂ͕b�B
		3.0f,											//!<�p�[�e�B�N���̕��B
		3.0f,											//!<�p�[�e�B�N���̍����B
		{2.5f, 2.5f, 2.5f,},							//!<�����ʒu�̃����_�����B
		{0.0f, 0.0f, 0.0f,},							//!<�����x�̃����_�����B
		{0.0f, 0.0f, 0.0f},								//!<���x�̐ϕ��̂Ƃ��̃����_�����B
		{

			{0.333f, 0.0f, 0.5f, 0.166f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f}
		},												//!<UV�e�[�u���B�ő�4�܂ŕێ��ł���Bx�������u�Ay�������v�Az���E����u�Aw���E����v�ɂȂ�B
		1,												//!<UV�e�[�u���̃T�C�Y�B
		{0.0f, 0.0f, 0.0f},								//!<�d�́B
		true,											//!<���ʂƂ��Ƀt�F�[�h�A�E�g����H
		0.05f,											//!<�t�F�[�h���鎞�ԁB
		1.0f,											//!<�����A���t�@�l�B
		true,											//!<�r���{�[�h�H
		0.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,												//!<0�����������A1���Z�����B
		{0.1f, 0.1f, 0.1f},								//!<��Z�J���[�B
		0.15f,											//!<�p�[�e�B�N���G�~�b�^�[�̎���
		1.2f											//!<�T�C�Y�X�P�[��
		},
		m_position);
		CParticleEmitter *l_particleEmitter2 = NewGO<CParticleEmitter>(PRIORITY0);
		l_particleEmitter2->Init(g_random, g_gameCamera[m_playerNum]->GetCamera(),
		{
			"Assets/particle/Explosion1.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
			{ 0.0f, 0.0f, 0.0f },								//!<�����x�B
			0.1f,											//!<�����B�P�ʂ͕b�B
			0.01f,											//!<�������ԁB�P�ʂ͕b�B
			3.0f,											//!<�p�[�e�B�N���̕��B
			3.0f,											//!<�p�[�e�B�N���̍����B
			{ 2.0f, 2.0f, 2.0f, },							//!<�����ʒu�̃����_�����B
			{ 0.0f, 0.0f, 0.0f, },							//!<�����x�̃����_�����B
			{ 0.0f, 0.0f, 0.0f },								//!<���x�̐ϕ��̂Ƃ��̃����_�����B
			{
				{ 0.333f, 0.0f, 0.5f, 0.166f },
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
			1,												//!<0�����������A1���Z�����B
			{ 0.1f, 0.1f, 0.1f },								//!<��Z�J���[�B
			0.15f,											//!<�p�[�e�B�N���G�~�b�^�[�̎���
			1.2f											//!<�T�C�Y�X�P�[��
		},
			m_position);
		for (int i = 0;i < PLAYER_NUM;i++)
		{
			l_particleEmitter->AddCamera(g_gameCamera[i]->GetCamera());
			l_particleEmitter2->AddCamera(g_gameCamera[i]->GetCamera());
		}
	}
}