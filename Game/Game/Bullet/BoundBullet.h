#pragma once
#include "Bullet.h"

class BoundBullet : public Bullet
{
public:
	BoundBullet();

	~BoundBullet();

	void Init(CVector3 movespeed, Weapon* weapon, int arrayNum, int plaerNum)override;

	void Move()override;

	void DethCheck()override;
private:
	float m_timer;
};

