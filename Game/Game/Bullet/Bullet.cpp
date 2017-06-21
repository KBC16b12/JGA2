#include "stdafx.h"
#include "Bullet.h"
#include "../Camera/GameCamera.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Player/Weapon.h"


Bullet::Bullet()
{
	m_position = CVector3::Zero;
	m_moveSpeed = CVector3::Zero;
	m_lifeTime = 0.0f;
}


Bullet::~Bullet()
{
}

void Bullet::Init(CVector3 position, CVector3 movespeed, int playerNum, CLight* light)
{
	//どのプレイヤーが打ったのかの番号割り当て
	m_playerNum = playerNum;
	//座標の初期化
	m_position = position;
	CVector3 l_addPosition = movespeed;
	l_addPosition.Cross(CVector3::AxisY);
	l_addPosition.Scale(-1.3f);
	l_addPosition.y -= 0.8f;
	m_position.Add(l_addPosition);

	m_moveSpeed = movespeed;
	//弾の移動方向と発射位置の調整
	m_moveSpeed.Normalize();
	m_moveSpeed.Scale(100.0f);
	m_moveSpeed.Subtract(m_moveSpeed, l_addPosition);
	m_moveSpeed.Normalize();
	l_addPosition = m_moveSpeed;
	m_moveSpeed.Scale(50.0f);
	l_addPosition.Scale(2.5f);
	m_position.Add(l_addPosition);

	//characterControllerの初期化
	m_characterController.Init(0.2f, 0.3f, m_position);
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetGravity(0.0f);
	m_pLight = light;
}

bool Bullet::Start()
{
	SkinModelDataResources().Load(m_modelData, "Assets/modelData/Bullet.X", NULL, false, 1);
	m_skinModel.Init(m_modelData.GetBody());
	m_skinModel.SetLight(m_pLight);
	return true;
}

void Bullet::Update()
{
	if(g_gameScene == nullptr)
	{
		DeleteGO(this);
		return;
	}
	Move();
	DeathCheck();
	m_skinModel.Update(m_position, CQuaternion::Identity, CVector3::One);
	m_lifeTime += GameTime().GetFrameDeltaTime();
}

void Bullet::DeathCheck()
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
				DeleteGO(this);
				PlayerDamage(l_player);
				break;
			}
		}
		else
		{
			//弾を打ったプレイヤーとある程度離れていればオブジェクトと衝突して消滅
			if (m_characterController.IsCollision() || 40.0f < m_lifeTime)
			{
				DeleteGO(this);
				break;
			}
		}
	}

}

void Bullet::Move()
{
	m_moveSpeed.y = m_characterController.GetMoveSpeed().y;
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.Execute(GameTime().GetFrameDeltaTime());
	m_position = m_characterController.GetPosition();
}

void Bullet::PlayerDamage(Player *player)
{
	player->Damage(m_playerNum, BULLET_DAMAGE);
}

void Bullet::Render(CRenderContext& renderContext)
{
	m_skinModel.Draw(renderContext, g_gameCamera[0]->GetViewMatrix(), g_gameCamera[0]->GetProjectionMatrix());
}

void Bullet::Render(CRenderContext& renderContext, int playernum)
{
	m_skinModel.Draw(renderContext, g_gameCamera[playernum]->GetViewMatrix(), g_gameCamera[playernum]->GetProjectionMatrix());
}

