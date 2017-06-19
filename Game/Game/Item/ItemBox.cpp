#include "stdafx.h"
#include "ItemBox.h"
#include "../Player/Player.h"

ItemBox::ItemBox()
{

}

ItemBox::~ItemBox()
{

}

void ItemBox::Death(Player *player)
{
	Item::Death(player);
	player->SetWeapon();
}