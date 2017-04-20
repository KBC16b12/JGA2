#pragma once
#include "BULLET.H"
#include "../Player/Weapon.h"

class GrenadeBullet : public Bullet
{
public:
	GrenadeBullet();

	~GrenadeBullet();

	/*
	*@brief 初期化関数
	*/
	void Init(CVector3 position, CVector3 moveSpeed, Weapon* weapon, int arraynum)override;

	/*
	*@brief 更新処理
	*/
	void Update()override;

private:

};

