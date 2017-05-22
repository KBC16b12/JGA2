#pragma once

class TimeSprite : public IGameObject
{
public:
	TimeSprite();

	~TimeSprite();
	
	/*
	*@brief �������֐�
	*/
	bool Start()override;

	/*
	*@brief �X�V����
	*/
	void Update()override;

	/*
	*@brief �`��֐�
	*@brief playernum �ǂ̃v���C���[�̎��_�ŕ`�悵������
	*/
	void PostRender(CRenderContext& renderContext, int playernum);

	void PostRender(CRenderContext& renderContext);

	bool IsFinish()
	{
		return m_isFinish;
	}

private:
	float m_time;				//�^�C�}�[
	CSprite						m_sprite[3];
	CTexture*					m_texture[10];
	bool						m_isFinish;
};