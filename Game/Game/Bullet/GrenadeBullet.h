#pragma once
#include "BULLET.H"
#include "../Player/Weapon.h"

/*
*@brief グレネードランチャーのクラス
*/


class GrenadeBullet : public Bullet
{
public:
	GrenadeBullet();

	~GrenadeBullet();

	/*
	*@brief 初期化関数
	*/
	void Init(Weapon* weapon, int arraynum, int playerNum)override;

	/*
	*@brief 更新処理
	*/
	void Update()override;

	void DethCheck()override;

private:

};

