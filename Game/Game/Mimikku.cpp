#include "stdafx.h"
#include "Mimikku.h"
#include "../Game/Player/Player.h"

Mimikku::Mimikku()
{
}

Mimikku::~Mimikku()
{
}

void Mimikku::Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModelData, CAnimation* animation)
{
	Item::Init(position, rotation, skinModelData, animation);
	//m_animation->SetAnimationLoopFlag(0, false);
}
void Mimikku::Death(Player *player)
{
	Item::Death(player);
	player->Eaten();
	CVector3 l_distance = m_position;
	l_distance.Subtract(player->GetPosition());
	l_distance.y = 0.0f;
	float length = 7.0f;
	length -= l_distance.Length();
	l_distance.Normalize();
	l_distance.Scale(length);
	m_position.Add(l_distance);
}