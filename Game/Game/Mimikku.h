#pragma once
#include "../Game/Item/Item.h"
class Mimikku : public Item
{
public:
	Mimikku();
	~Mimikku()override;

	void Init(CVector3 position, CQuaternion rotation, CSkinModelData* skinModelData, CAnimation* animation)override;
private:
	void Death(Player *player)override;

};