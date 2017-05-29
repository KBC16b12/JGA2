#include "stdafx.h"
#include "Mimikku.h"
#include "../Game/Player/Player.h"

Mimikku::Mimikku()
{
}

Mimikku::~Mimikku()
{
}

void Mimikku::Deth(Player *player)
{
	Item::Deth(player);
	player->Eaten();
}