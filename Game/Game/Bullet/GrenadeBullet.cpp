#include "stdafx.h"
#include "GrenadeBullet.h"

GrenadeBullet::GrenadeBullet()
{
}


GrenadeBullet::~GrenadeBullet()
{
}

void GrenadeBullet::Init(CVector3 position, CVector3 moveSpeed, Weapon* weapon ,int arraynum)
{
	Bullet::Init(position, moveSpeed, weapon, arraynum);
	//重力設定
	m_characterController.SetGravity(-0.1f);
	m_moveSpeed.y += 1.0f;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	//打った瞬間に自分に当たってしまうため少し動かしておく
	for (int i = 0;i < 2;i++)
	{
		m_characterController.Execute(1.0f);
	}
	m_characterController.SetCollisionFlg(false);
}

void GrenadeBullet::Update()
{
	Bullet::Update();
	//何か物に当たったら消去する
	if (m_characterController.IsCollision())
	{
		m_weapon->Delete(m_arraynum);
	}
}