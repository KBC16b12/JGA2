#include "stdafx.h"
#include "Mimikku.h"
#include "../Game/Player/Player.h"

Mimikku::Mimikku()
{
}

Mimikku::~Mimikku()
{
}

void Mimikku::Death(Player *player)
{
	Item::Death(player);
	player->Eaten();
}