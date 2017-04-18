#pragma once

#include "Weapon.h"
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

	/*
	�v���C���[�̔ԍ����Z�b�g����֐�
	�v���C���[�̔ԍ��ƃJ�����̔ԍ��͓���
	*/
	void SetPlayerNum(int playernum)
	{
		m_playernum = playernum;
	}

	/*!
	*@brief	�`��֐��B
	*/
	void Render(CRenderContext& renderContext, int cameranum)override;

	void Move();

private:
	/*!
	*@brief	HP�o�[�X�V�֐��B
	*/
	void UpdateHPBar();
	
	CSkinModel				m_skinModel;					//�X�L�����f��
	CSkinModelData			m_skinModelData;				//�X�L�����f���f�[�^
	CQuaternion				m_rotation;					//��]
	CAnimation				m_Animation;					//�A�j���[�V����
	CCharacterController	m_characterController;		//�L�����N�^�\�R���g���[���[�B
	CVector3				m_position = { 0.0f, 40.0f, 0.0f };

	int						m_currentAnimationNo;
	float					m_angle = 180;

	Bar*			m_HPbar;		//HP�o�[
	int				m_hp;			//HP
	int				m_maxhp;		//�ő�HP
	int				m_playernum;
};

