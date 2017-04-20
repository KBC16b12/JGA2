#pragma once
#include "BULLET.H"
#include "../Player/Weapon.h"

class GrenadeBullet : public Bullet
{
public:
	GrenadeBullet();

	~GrenadeBullet();

	/*
	*@brief ‰Šú‰»ŠÖ”
	*/
	void Init(CVector3 position, CVector3 moveSpeed, Weapon* weapon, int arraynum)override;

	/*
	*@brief XVˆ—
	*/
	void Update()override;

private:

};

