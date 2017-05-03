#pragma once
#include "BULLET.H"
#include "../Player/Weapon.h"

/*
*@brief �O���l�[�h�����`���[�̃N���X
*/


class GrenadeBullet : public Bullet
{
public:
	GrenadeBullet();

	~GrenadeBullet();

	/*
	*@brief �������֐�
	*/
	void Init(CVector3 movespeed, Weapon* weapon, int arraynum, int playerNum)override;

	void Move()override;

	/*
	*@brief �X�V����
	*/
	void Update()override;

	void DethCheck()override;

private:
	CCharacterController	m_characterController;
};

