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
	void Init(Weapon* weapon, int arraynum, int playerNum)override;

	/*
	*@brief �X�V����
	*/
	void Update()override;

	void DethCheck()override;

private:

};

