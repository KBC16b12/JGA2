#pragma once 
#include "Item.h"

class ItemBox : public Item
{
public:
	ItemBox();

	~ItemBox();


private:

	void Deth(Player *player)override;
};