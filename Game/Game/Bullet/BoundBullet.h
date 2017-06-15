#pragma once
#include "Bullet.h"
/*
跳弾するバレットのクラス
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

