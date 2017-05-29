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
	*@brief �r���[�|�[�g��ݒ肷��֐�
	x		�������x���W
	y		�������y���W
	width	x����̉���
	height	y����̏c��
	Player* �J�����������Ă�v���C���[
	*/
	void SetViewPort(ViewPortParam param, Player* player)
	{
		GetViewSprit().SetSprit(param);
		m_player = player;
		m_isViewport = true;
	}

	void FinishViewPort()
	{
		m_isViewport = false;
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

	CCamera& GetCamera()
	{
		return m_camera;
	}

private:

	CCamera				m_camera;				//�J����
	CVector3				m_position;				//���W
	CVector3				m_look_position;		//�����_

	SViewport				m_sviewPort;
	float					m_angle;				//�p�x
	int						m_playernum;			//�r���[�|�[�g�ŋ�؂����Ƃ��̃J�����̔ԍ�
	bool					m_isViewport;
	Player*					m_player;
};

extern GameCamera* g_gameCamera[PLAYER_NUM];