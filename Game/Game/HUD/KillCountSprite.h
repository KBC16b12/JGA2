#pragma once

class KillCountSprite : public IGameObject
{
public:
	KillCountSprite();

	~KillCountSprite();

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
	void PostRender(CRenderContext& renderContext, int playernum)override;

private:
	CTexture*					m_texture[10];
	CSprite						m_sprite[2];
	int							m_killcount;		//�L����
};
