#pragma once
#include "Bullet.h"
/*
���e����o���b�g�̃N���X
*/


class BoundBullet : public Bullet
{
public:
	BoundBullet();

	~BoundBullet()override;

	void Move()override;

	void DeathCheck()override;


private:
	float m_timer;
};

