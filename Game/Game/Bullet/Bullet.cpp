#include "stdafx.h"
#include "Bullet.h"
#include "../Camera/GameCamera.h"


Bullet::Bullet()
{
	m_position = CVector3::Zero;
	m_moveSpeed = CVector3::Zero;
	m_lifeTime = 0;
}


Bullet::~Bullet()
{
}

void Bullet::Init(CVector3 position, CVector3 moveSpeed, Weapon *weapon, int arraynum)
{
	m_position = position;
	m_position.y += 3.5f;
	m_characterController.Init(0.3f, 0.3f, m_position);
	m_characterController.SetGravity(0.0f);
	m_moveSpeed = moveSpeed;
	m_moveSpeed.Normalize();
	m_moveSpeed.Scale(1.0f);
	m_weapon = weapon;
	m_arraynum = arraynum;
}

bool Bullet::Start()
{
	m_modelData.LoadModelData("Assets/modelData/Bullet.X", NULL);
	m_skinModel.Init(m_modelData.GetBody());
	m_skinModel.SetLight(&m_light);
	return true;
}

void Bullet::Update()
{
	Move();
	m_lifeTime++;
	if (300 < m_lifeTime)
	{
		m_weapon->Delete(m_arraynum);
	}
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
}

void Bullet::Move()
{
	m_moveSpeed.y = m_characterController.GetMoveSpeed().y;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.Execute(1.0f);
	m_position = m_characterController.GetPosition();
}

void Bullet::Render(CRenderContext& renderContext)
{
}

void Bullet::Render(CRenderContext& renderContext, int playernum)
{
	m_skinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}

