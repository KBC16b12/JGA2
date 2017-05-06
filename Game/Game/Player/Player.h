#pragma once

#include "../Network/Network.h"
#include "Weapon.h"
class KillCountSprite;
class Bar;

class Player : public IGameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	Player();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~Player();

	/*!
	*@brief	�J�n�֐��B
	*@details
	* �������Ȃǂ����̊֐��Ɏ������Ă��������B</br>
	* ���̊֐���true��Ԃ��Ɩ{�ِ��͈ȍ~�̃t���[���ł͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �����ăQ�[���I�u�W�F�N�g�̏�Ԃ������������ɂȂ�Update�֐����Ă΂��悤�ɂȂ�܂��B</br>
	*@return	true���A���Ă����珉���������B
	*/
	bool Start() override;

	/*!
	*@brief	�X�V�֐��B
	*/
	void Update() override;

	/*!
	*@brief	�`��֐��B
	*/
	void Render(CRenderContext& renderContext, int cameranum)override;

	void PostRender(CRenderContext& renderContext, int cameranum)override;

	void Move();

	/*
	*@brief �_���[�W���󂯂����ɌĂ΂��֐�
	*@brief int playerNum
	*/
	void Damage(int playerNum);

	/*
	*@brief ���X�|�[������
	*/
	void Respawn();

	CVector3 GetPosition()
	{
		return m_position;
	}

	/*
	*@brief �v���C���[�̑O���̃��[���h�s��
	*/
	CVector3 GetFrontWorldMatrix()
	{
		CVector3 l_frontWorldMatrix;
		CMatrix l_worldMatrix = m_skinModelFirst.GetWorldMatrix();
		l_frontWorldMatrix.x = l_worldMatrix.m[2][0];
		l_frontWorldMatrix.y = l_worldMatrix.m[2][1];
		l_frontWorldMatrix.z = l_worldMatrix.m[2][2];
		l_frontWorldMatrix.Scale(-1.0f);
		return l_frontWorldMatrix;
	}

	/*
	*@brief �v���C���[�����Ă镐��N���X�ɃA�C�e�����Z�b�g����֐�
	*/
	void SetWeapon()
	{
		m_weapon.SetWeapon();
	}

	void SetPosition(CVector3 position)
	{
		m_position = position;
		m_respawnPosition = position;
	}

	/*
	�v���C���[�̔ԍ����Z�b�g����֐�
	�v���C���[�̔ԍ��ƃJ�����̔ԍ��͓���
	*/
	void SetPlayerNum(int playernum)
	{
		m_playernum = playernum;
		m_weapon.Init(this, m_playernum);
	}

	int GetPlayerNum()
	{
		return m_playernum;
	}

	bool IsLoadEnd()
	{
		return (m_skinModelDataFirst.IsLoadEnd() && m_skinModelDataThird.IsLoadEnd());
	}
	
	void KillCountUp()
	{
		m_killCount++;
	}

private:
	/*!
	*@brief	HP�o�[�X�V�֐��B
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModelFirst;					//�X�L�����f��
	CSkinModelDataHandle	m_skinModelDataFirst;				//�X�L�����f���f�[�^
	CSkinModel				m_skinModelThird;
	CSkinModelDataHandle	m_skinModelDataThird;
	CQuaternion				m_rotation;					//��]
	CAnimation				m_Animation;					//�A�j���[�V����
	CCharacterController	m_characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position = { 0.0f, 0.0f, 0.0f };
	CVector3				m_respawnPosition;
	CQuaternion				m_respawnRotation;

	int						m_currentAnimationNo;
	float					m_angle = 180;

	KillCountSprite*		m_killCountSprite;					//�L�����̃X�v���C�g
	Bar*					m_HPbar;		//HP�o�[
	int						m_hp;			//HP
	int						m_maxhp;		//�ő�HP
	int						m_playernum;
	int						m_killCount;
	Weapon					m_weapon;
	CLight					m_light;
	Network					m_network;
};

