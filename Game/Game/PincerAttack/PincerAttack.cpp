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
	if (g_gameScene == nullptr)
	{
		return;
	}
	Player *l_player[PLAYER_NUM];
	//プレイヤーの取得
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		l_player[i] = g_gameScene->GetPlayer(i);
	}
	//内積を取るためのプレイヤーの前方向のベクトル
	CVector3 l_playerFront = l_player[m_playerNum]->GetFrontWorldMatrix();
	l_playerFront.Normalize();
	
	int l_pincerEffectNum = 0;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		//内積を取る相手が自分だったらスルー
		if (m_playerNum == i)
		{
			continue;
		}
		float rad = CMath::DegToRad(8);
		//プレイヤーから挟むのに使うプレイヤーまでの距離を計算
		CVector3 l_direction1 = l_player[i]->GetPosition();
		l_direction1.Subtract(l_player[m_playerNum]->GetPosition());
		l_direction1.y = 0.0f;
		float l_distance1 = l_direction1.Length();
		//正規化して内積を取る
		l_direction1.Normalize();
		float l_dot1 = l_direction1.Dot(l_playerFront);
		float l_dot = 0.0f;		//最終的なエフェクトの濃さ
		float l_zValue = 1.0f;	//奥行を見た時の値
		int l_zCount = 0;		//挟むのに使う相手より自分に近いプレイヤーの数
		float l_distance2;		//挟まれる相手との距離
		float l_length = 10000000000.0f;	//挟まれる相手のなかで一番近い距離（l_zCountが0の時に使う
		for (int j = 0;j < PLAYER_NUM;j++)
		{
			bool l_isPincerAttack = true;
			//自分かもしくは挟むのに使うプレイヤーならスルー
			if (m_playerNum == j || i == j)
			{
				continue;
			}
			//挟まれる相手との距離を計算
			CVector3 l_direction2 = l_player[j]->GetPosition();
			l_direction2.Subtract(l_player[m_playerNum]->GetPosition());
			l_direction2.y = 0.0f;
			l_distance2 = l_direction2.Length();
			//距離を計算して相手が間にいなかった場合
			if (l_distance1 < l_distance2)
			{
				l_isPincerAttack = false;
			}
			else
			{
				l_zCount++;
			}
			//挟む相手以外の自分から近いプレイヤーを求める
			if (l_distance2 < l_length)
			{
				l_length = l_distance2;
			}

			l_direction2.Normalize();
			float l_dot2 = l_direction2.Dot(l_direction1);
			//内積を取って角度が開きすぎていると打てない
			if (l_dot1 < cos(rad))
			{
				l_isPincerAttack = false;
			}
			if (l_dot2 < cos(rad))
			{
				l_isPincerAttack = false;
			}

			//打てる状態
			if (l_isPincerAttack)
			{
				if (Pad(m_playerNum).IsTrigger(enButtonLB1))
				{
					l_player[j]->Damage(m_playerNum, 5);
				}
			}
			//自分と挟むのに使うプレイヤーの中でで一番角度がきついのを使う
			if (l_dot < l_dot2)
			{
				l_dot = l_dot2;
			}
		}
		//自分から一番近い人と2番目に近い人が入れ替わるときに急に変わるのを防ぐ
		if (l_zCount == 0)
		{
			float l_distance = l_length - l_distance1;
			if (l_distance < 0.0f)
			{
				l_distance *= -1.0f;
			}
			float l_distanceRange = 10.0f;
			if (l_distance < l_distanceRange)
			{
				l_zValue = 1.0f - l_distance / l_distanceRange;
			}
			else
			{
				l_zValue = 0.01f;
			}
		}

		float l_zDotRate = 0.5f;
		l_dot = l_zValue * l_zDotRate + l_dot * (1.0f - l_zDotRate);
		m_pincerEffect[l_pincerEffectNum]->SetDot(l_dot);
		l_pincerEffectNum++;
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