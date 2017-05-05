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
				l_player->Damage(m_playerNum);
			}
		}
		m_weapon->Delete(m_arraynum);
		g_gameScene->ParticleEmit(g_random, g_gameCamera[0]->GetCamera(), 
		{
		"Assets/particle/Explosion5.png",				//!<�e�N�X�`���̃t�@�C���p�X�B
		{0.0f, 0.0f, 0.0f},								//!<�����x�B
		0.3f,											//!<�����B�P�ʂ͕b�B
		0.01f,											//!<�������ԁB�P�ʂ͕b�B
		6.0f,											//!<�p�[�e�B�N���̕��B
		6.0f,											//!<�p�[�e�B�N���̍����B
		{3.0f, 3.0f, 3.0f,},							//!<�����ʒu�̃����_�����B
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
		0.3f,											//!<�t�F�[�h���鎞�ԁB
		1.0f,											//!<�����A���t�@�l�B
		false,											//!<�r���{�[�h�H
		0.0f,											//!<�P�x�B�u���[�����L���ɂȂ��Ă���Ƃ������������ƌ������܂��B
		1,												//!<0�����������A1���Z�����B
		{1.0f, 1.0f, 1.0f}								//!<��Z�J���[�B
		},
		m_position);
	}
}