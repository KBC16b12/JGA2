#pragma once
#include "../Game/Item/Item.h"
class Mimikku : public Item
{
public:
	Mimikku();
	~Mimikku();
private:
	void Deth(Player *player)override;
};