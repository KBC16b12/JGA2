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
	//d—Íİ’è
	m_characterController.SetGravity(-0.1f);
	m_moveSpeed.y += 1.0f;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	//‘Å‚Á‚½uŠÔ‚É©•ª‚É“–‚½‚Á‚Ä‚µ‚Ü‚¤‚½‚ß­‚µ“®‚©‚µ‚Ä‚¨‚­
	for (int i = 0;i < 2;i++)
	{
		m_characterController.Execute(1.0f);
	}
	m_characterController.SetCollisionFlg(false);
}

void GrenadeBullet::Update()
{
	Bullet::Update();
	//‰½‚©•¨‚É“–‚½‚Á‚½‚çÁ‹‚·‚é
	if (m_characterController.IsCollision())
	{
		m_weapon->Delete(m_arraynum);
	}
}