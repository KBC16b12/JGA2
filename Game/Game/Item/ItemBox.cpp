#include "stdafx.h"
#include "ItemBox.h"
#include "../Player/Player.h"

ItemBox::ItemBox()
{

}

ItemBox::~ItemBox()
{

}

void ItemBox::Deth(Player *player)
{
	Item::Deth(player);
	player->SetWeapon();
}