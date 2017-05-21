#include "stdafx.h"
#include "PincerAttack.h"
#include "../Scene/GameScene/GameScene.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"
#include "PincerAttackEffect.h"

PincerAttack::PincerAttack()
{
}

PincerAttack::~PincerAttack()
{
	for (int i = 0;i < PLAYER_NUM - 1;i++)
	{
		DeleteGO(m_pincerEffect[i]);
	}
}

void PincerAttack::Update()
{
	Shoot();
}

bool PincerAttack::Start()
{
	int l_playerNum = 0;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		if (m_playerNum != i)
		{
			m_pincerEffect[l_playerNum] = NewGO<PincerAttackEffect>(PRIORITY2);
			m_pincerEffect[l_playerNum]->Init(m_playerNum, i);
			l_playerNum++;
		}
	}
	return true;
}

void PincerAttack::Shoot()
{
	Player *l_player[PLAYER_NUM];
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		l_player[i] = g_gameScene->GetPlayer(i);
	}
	for (int i = 0;i < PLAYER_NUM - 1;i++)
	{
		m_pincerEffect[i]->SetDot(0.4f);
	}
	CVector3 l_playerFront = l_player[m_playerNum]->GetFrontWorldMatrix();
	l_playerFront.Normalize();
	int l_pincerEffectNum = 0 - 1;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		if (m_playerNum == i)
		{
			continue;
		}
		l_pincerEffectNum++;
		float rad = CMath::DegToRad(8);
		//他プレイヤーとの内積を取る
		CVector3 l_direction1 = l_player[i]->GetPosition();
		l_direction1.Subtract(l_player[m_playerNum]->GetPosition());
		l_direction1.y = 0.0f;
		float l_distance1 = l_direction1.Length();
		l_direction1.Normalize();
		//違う方向を向いてたらやり直す
		if (l_direction1.Dot(l_playerFront) < cos(rad))
		{
			continue;
		}
		//間に誰かいないか判定
		for (int j = 0;j < PLAYER_NUM;j++)
		{
			if (m_playerNum == j || i == j)
			{
				continue;
			}
			CVector3 l_direction2 = l_player[j]->GetPosition();
			l_direction2.Subtract(l_player[m_playerNum]->GetPosition());
			l_direction2.y = 0.0f;
			float l_distance2 = l_direction2.Length();
			if (l_distance1 < l_distance2)
			{
				continue;
			}
			l_direction2.Normalize();
			float l_dot = l_direction1.Dot(l_direction2);
			if (l_dot < cos(rad))
			{
				continue;
			}
			if (Pad(m_playerNum).IsTrigger(enButtonLB1))
			{
				l_player[j]->Damage(m_playerNum, 5);
			}
			m_pincerEffect[l_pincerEffectNum]->SetDot(1.0f);
		}
	}
}

void PincerAttack::CreatePrimitiv()
{
}


void PincerAttack::Render(CRenderContext& renderContext)
{
}

void PincerAttack::Render(CRenderContext& renderContext, int playerNum)
{
}