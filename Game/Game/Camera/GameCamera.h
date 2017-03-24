#pragma once
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

	void Move();

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


private:
	CCamera					m_camera;				//�J����
	CCharacterController	m_characterController;	//�L�����N�^�\�R���g���[���[
	CVector3				m_position;				//���W
	CVector3				m_look_position;		//�����_
	
	float					m_angle;				//�p�x
};

extern GameCamera* g_gameCamera;