#include "stdafx.h"
#include "Bullet.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"


Bullet::Bullet()
{
	m_position = CVector3::Zero;
	m_moveSpeed = CVector3::Zero;
}


Bullet::~Bullet()
{
}

void Bullet::Init(Weapon *weapon, int arrayNum, int playerNum)
{
	//どのプレイヤーが打ったのかの番号割り当て
	m_playerNum = playerNum;
	//座標の初期化
	Player *l_player = g_gameScene->GetPlayer(m_playerNum);
	m_position = l_player->GetPosition();
	m_position.y += 3.5f;
	//
	//m_characterController.Init(0.3f, 0.5f, m_position);
	//m_characterController.SetGravity(0.001f);
	//移動速度をプレイヤーの向きから求める
	m_moveSpeed = l_player->GetFrontWorldMatrix();
	m_moveSpeed.Normalize();
	m_moveSpeed.Scale(1.0f);

	//m_characterController.SetMoveSpeed(m_moveSpeed);
	m_weapon = weapon;
	m_arraynum = arrayNum;
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
	if(g_gameScene == nullptr)
	{
		return;
	}
	Move();
	DethCheck();
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
}

void Bullet::DethCheck()
{
	float l_playerRadius = 5.0f;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		Player *l_player = g_gameScene->GetPlayer(i);
		CVector3 l_distance = l_player->GetPosition();
		l_distance.Subtract(m_position);
		if (m_playerNum != i)
		{
			//プレイヤーに当たったら
			if (l_distance.Length() < l_playerRadius)
			{
				m_weapon->Delete(m_arraynum);
				l_player->Damage(m_playerNum);
				break;
			}
		}
		else
		{
			//弾を打ったプレイヤーとある程度離れていればオブジェクトと衝突して消滅
			if (100.0f < l_distance.Length()/* && m_characterController.IsCollision()*/)
			{
				m_weapon->Delete(m_arraynum);
			}
		}
	}
}

void Bullet::Move()
{
	//m_moveSpeed.y = m_characterController.GetMoveSpeed().y;
	//m_characterController.Execute(GameTime().GetFrameDeltaTime());
	//m_position = m_characterController.GetPosition();
	m_position.Add(m_moveSpeed);
}

void Bullet::Render(CRenderContext& renderContext)
{
}

void Bullet::Render(CRenderContext& renderContext, int playernum)
{
	m_skinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}

