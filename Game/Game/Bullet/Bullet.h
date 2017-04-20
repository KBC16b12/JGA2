#pragma once
#include "../Player/Weapon.h"

/*
�e�̊��N���X
���̃A�C�e�����g�����Ƃ��ɏo��e�͂��̃N���X���p��������
*/

class Bullet : public IGameObject
{
public:
	Bullet();

	~Bullet();

	bool Start()override;


	/*
	*@brief �e�̏���������
	*@brief position �v���C���[�̃|�W�V����
	*@brief moveSpeed
	*/
	virtual void Init(CVector3 position, CVector3 moveSpeed, Weapon *weapon, int arraynum);


	/*
	*@brief �X�V����
	*/
	virtual void Update()override;


	/*
	*@brief �e�̓����̏���
	*/
	virtual void Move();

	/*
	*@brief �`��֐�
	*/
	void Render(CRenderContext& renderContext)override;

	/*
	*@brief �J�������ɌĂԕ`��֐�
	*@brief playernum �ǂ̃v���C���[�̎��_�ŕ`�悵������
	*/
	void Render(CRenderContext& renderContext, int playernum)override;

protected:
	CCharacterController	m_characterController;
	CVector3				m_position;
	CVector3				m_moveSpeed;
	CSkinModel				m_skinModel;
	CSkinModelDataHandle	m_modelData;
	CLight					m_light;
	Weapon*					m_weapon;
	int						m_lifeTime;
	int						m_arraynum;
};
