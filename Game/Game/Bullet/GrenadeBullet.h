#pragma once
#include "BULLET.H"

/*
*@brief �O���l�[�h�����`���[�̃N���X
*/


class GrenadeBullet : public Bullet
{
public:
	GrenadeBullet();

	~GrenadeBullet()override;

	/*
	*@brief �������֐�
	*/
	void Init(CVector3 position, CVector3 movespeed, int playerNum, CLight* light)override;

	void DeathCheck()override;

private:
};

