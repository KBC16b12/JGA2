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
}