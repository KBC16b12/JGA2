#pragma once
#include "Bullet.h"
/*
挟み撃ちの時のバレット
*/

class PincerBullet : public Bullet
{
public:
	PincerBullet();

	~PincerBullet()override;

	bool Start()override;
private:
	void PlayerDamage(Player* player)override;

private:
	CSkinModelData m_modelData;
};

