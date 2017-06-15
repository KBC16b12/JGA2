#pragma once

#include "../Network/Network.h"
#include "Weapon.h"
#include "PlayerRecovery.h"
class KillCountSprite;
class Bar;


enum
{
	ANIMESTATE_WAIT,
	ANIMESTATE_SHOT,
	ANIMESTATE_RELOAD,
	ANIMESTATE_NUM,
};
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

	void Render(CRenderContext& renderContext)override;

	void Move();



	/*
	*@brief �_���[�W���󂯂����ɌĂ΂��֐�
	*@brief int playerNum	���Ă��v���C���[�̔ԍ�
	*@brief int damage		�v���C���[���󂯂�_���[�W��
	*/
	void Damage(int playerNum, int damage);

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

	void Init(CVector3 position, CQuaternion rotation, int playernum);


	int GetPlayerNum()
	{
		return m_playernum;
	}
	
	void KillCountUp();

	void Startup();

	bool IsStup()
	{
		return Stup;
	}
	CMatrix GetWorldMatrix()
	{
		return m_skinModelFirst.GetWorldMatrix();
	}

	void Eaten();

	
	int GetMaxHP()
	{
		return m_maxhp;
	}

	void SetIsPincer(bool isPincerAttack)
	{
		m_weapon.SetIsPincer(isPincerAttack);
	}

private:
	/*!
	*@brief	HP�o�[�X�V�֐��B
	*/
	void UpdateHPBar();

	/*!
	*@brief	�L�[���͏��o�́B
	*/
	void KeyOutput();

	/*!
	*@brief	���f�[�^�o�́B
	*/
	void DataOutput();

	void Invincible();

private:
	CSkinModel				m_skinModelFirst;					//�������猩�����̃��f��
	CSkinModelDataHandle	m_skinModelDataFirst;				//�X�L�����f���f�[�^
	CSkinModel				m_skinModelThird;					//���l���猩�����̃��f��
	CSkinModelData			m_skinModelDataThird;
	CQuaternion				m_rotation;					//��]
	CAnimation				m_Animation;					//�A�j���[�V����
	CCharacterController	m_characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position = { 0.0f, 0.0f, 0.0f };

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
	int						m_time = 30;
	int						Ctime = 15;
	bool					m_isInvincible;
	bool					m_isInvincibleTec;
	float					m_invincibleTecCount;	//�e�N�j�b�N��؂�ւ��鎞��
	float					m_invincibleCount;		//���X�L���h�~�̖��G���Ԃ𐔂���ϐ�
	Weapon					m_weapon;
	CLight					m_light;
	PlayerRecovery			m_recovery;
	CAnimation				m_animation;
};

