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
	
}
void PincerAttack::OnDestroy()
{
	for (int i = 0; i < PLAYER_NUM - 1; i++)
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
	//�v���C���[�̎擾
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		l_player[i] = g_gameScene->GetPlayer(i);
	}
	//���ς���邽�߂̃v���C���[�̑O�����̃x�N�g��
	CVector3 l_playerFront = l_player[m_playerNum]->GetFrontWorldMatrix();
	l_playerFront.Normalize();
	
	int l_pincerEffectNum = 0;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		//���ς���鑊�肪������������X���[
		if (m_playerNum == i)
		{
			continue;
		}
		float rad = CMath::DegToRad(8);
		//�v���C���[���狲�ނ̂Ɏg���v���C���[�܂ł̋������v�Z
		CVector3 l_direction1 = l_player[i]->GetPosition();
		l_direction1.Subtract(l_player[m_playerNum]->GetPosition());
		l_direction1.y = 0.0f;
		float l_distance1 = l_direction1.Length();
		//���K�����ē��ς����
		l_direction1.Normalize();
		float l_dot1 = l_direction1.Dot(l_playerFront);
		float l_dot = 0.0f;		//�ŏI�I�ȃG�t�F�N�g�̔Z��
		float l_zValue = 1.0f;	//���s���������̒l
		int l_zCount = 0;		//���ނ̂Ɏg�������莩���ɋ߂��v���C���[�̐�
		float l_distance2;		//���܂�鑊��Ƃ̋���
		float l_length = 10000000000.0f;	//���܂�鑊��̂Ȃ��ň�ԋ߂������il_zCount��0�̎��Ɏg��
		for (int j = 0;j < PLAYER_NUM;j++)
		{
			bool l_isPincerAttack = true;
			//�������������͋��ނ̂Ɏg���v���C���[�Ȃ�X���[
			if (m_playerNum == j || i == j)
			{
				continue;
			}
			//���܂�鑊��Ƃ̋������v�Z
			CVector3 l_direction2 = l_player[j]->GetPosition();
			l_direction2.Subtract(l_player[m_playerNum]->GetPosition());
			l_direction2.y = 0.0f;
			l_distance2 = l_direction2.Length();
			//�������v�Z���đ��肪�Ԃɂ��Ȃ������ꍇ
			if (l_distance1 < l_distance2)
			{
				l_isPincerAttack = false;
			}
			else
			{
				l_zCount++;
			}
			//���ޑ���ȊO�̎�������߂��v���C���[�����߂�
			if (l_distance2 < l_length)
			{
				l_length = l_distance2;
			}

			l_direction2.Normalize();
			float l_dot2 = l_direction2.Dot(l_direction1);
			//���ς�����Ċp�x���J�������Ă���ƑłĂȂ�
			if (l_dot1 < cos(rad))
			{
				l_isPincerAttack = false;
			}
			if (l_dot2 < cos(rad))
			{
				l_isPincerAttack = false;
			}

			//�łĂ���
			if (l_isPincerAttack)
			{
				if (Pad(m_playerNum).IsTrigger(enButtonLB2))
				{
					l_player[j]->Damage(m_playerNum, g_gameScene->GetPlayer(j)->GetMaxHP());
				}
			}
			//�����Ƌ��ނ̂Ɏg���v���C���[�̒��łň�Ԋp�x�������̂��g��
			if (l_dot < l_dot2)
			{
				l_dot = l_dot2;
			}
		}
		//���������ԋ߂��l��2�Ԗڂɋ߂��l������ւ��Ƃ��ɋ}�ɕς��̂�h��
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