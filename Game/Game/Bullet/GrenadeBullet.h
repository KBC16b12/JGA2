#pragma once
#include "BULLET.H"

/*
*@brief グレネードランチャーのクラス
*/


class GrenadeBullet : public Bullet
{
public:
	GrenadeBullet();

	~GrenadeBullet()override;

	/*
	*@brief 初期化関数
	*/
	void Init(CVector3 position, CVector3 movespeed, int playerNum, CLight* light)override;

	void DeathCheck()override;

private:
};

