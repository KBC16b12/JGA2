#pragma once
#include "Bullet.h"

class BoundBullet : public Bullet
{
public:
	BoundBullet();

	~BoundBullet();

	void Init(CVector3 position, CVector3 movespeed, int plaerNum)override;

	void Move()override;

	void DeathCheck()override;

private:
	float m_timer;
};

