#pragma once
class Player;

class GameCamera : public IGameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/

	GameCamera();

	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~GameCamera();

	/*!
	*@brief	�X�V�֐��B
	*/
	void Update();

	/*
	*@brief �`��֐�
	�����ŃJ�������̃I�u�W�F�N�g��`�悷��
	*/
	void Render(CRenderContext&)override;

	void PostRender(CRenderContext&)override;

	/*
	*@brief �r���[�|�[�g�̋�`�̏ꏊ�ƃJ�����̔ԍ��t������֐�
	x		�������x���W
	y		�������y���W
	width	x����̉���
	height	y����̏c��
	cameranum �J�����̔ԍ�
	*/
	void SetViewPort(int x, int y, int width, int height, int cameranum);


	/*
	*@brief ��ʕ������I�������ĂԊ֐�
	*/
	void FinishViewPort()
	{
		m_ViewportFlg = false;
	}

	void SetPos();
	/*!
	*@brief	�r���[�}�g���b�N�X��Ԃ��B
	*/
	const CMatrix& GetViewMatrix() const
	{
		return m_camera.GetViewMatrix();
	}

	/*!
	*@brief	�v���W�F�N�V�����}�g���b�N�X��Ԃ��B
	*/
	const CMatrix& GetProjectionMatrix() const
	{
		return m_camera.GetProjectionMatrix();
	}

	int GetPlayerNum()
	{
		return m_playernum;
	}

private:
	CCamera					m_camera;				//�J����
	//CCharacterController	m_characterController;	//�L�����N�^�\�R���g���[���[
	CVector3				m_position;				//���W
	CVector3				m_look_position;		//�����_

	SViewport				m_sviewPort;
	float					m_angle;				//�p�x
	int						m_playernum;			//�r���[�|�[�g�ŋ�؂����Ƃ��̃J�����̔ԍ�
	bool					m_ViewportFlg;
	Player*					m_player;
};

extern GameCamera* g_gameCamera[PLAYER_NUM];