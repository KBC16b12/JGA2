#pragma once

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

	void Trap();

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
		CMatrix l_worldMatrix = m_skinModel.GetWorldMatrix();
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

	/*
	�v���C���[�̔ԍ����Z�b�g����֐�
	�v���C���[�̔ԍ��ƃJ�����̔ԍ��͓���
	*/
	void SetPlayerNum(int playernum)
	{
		m_playernum = playernum;
		m_weapon.Init(this, m_playernum);
	}

	int GetPlayerNUm()
	{
		return m_playernum;
	}
	
	void KillCountUp()
	{
		m_killCount++;
	}

	void Startup();

	bool IsStup()
	{
		return Stup;
	}
private:
	/*!
	*@brief	HP�o�[�X�V�֐��B
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModel;					//�X�L�����f��
	CSkinModelData			m_skinModelData;				//�X�L�����f���f�[�^
	CQuaternion				m_rotation;						//��]
	CAnimation				m_Animation;					//�A�j���[�V����
	CCharacterController	m_characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position = { 0.0f, 40.0f, 0.0f };
	CVector3				m_respawnPosition;
	CQuaternion				m_respawnRotation;

	int						m_currentAnimationNo;
	float					m_angle = 180;
	float					move = -5.0f;	//�ړ����x
	bool					Stup = false;
	KillCountSprite*		m_killCountSprite;					//�L�����̃X�v���C�g
	Bar*					m_HPbar;		//HP�o�[
	int						m_hp;			//HP
	int						m_maxhp;		//�ő�HP
	int						m_playernum;
	int						m_killCount;
	int						m_time = 75;
	int						Ctime = 100;
	Weapon					m_weapon;
};

