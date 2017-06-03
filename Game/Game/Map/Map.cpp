#include "stdafx.h"
#include "Map.h"
#include "../MapObject.h"
#include "../Camera/GameCamera.h"
#include "../Item/Item.h"
#include "../Trap.h"
#include "../Item/ItemMaker.h"
#include "../Player/Player.h"

Map::Map()
{
	m_isLoad = false;
}

Map::~Map()
{
	//マップチップのデータ削除
	for each(MapChip* l_map_dat in m_mapchip)
	{
		l_map_dat->SetActiveFlag(false);
		DeleteGO(l_map_dat);
	}
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		DeleteGO(m_player[i]);
	}
}

void Map::Init(std::vector<SMapInfo> map_dat)
{
	int l_playerNum = 0;
	//マップチップの作成
	for each(SMapInfo l_map_dat in map_dat)
	{
		MapChip *l_mapChip = nullptr;
		if (!strcmp("itembox1-1", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<ItemMaker>(PRIORITY1);
		}
		else if (!strcmp("snowman1-3", l_map_dat.s_modelName))
		{
			m_player[l_playerNum] = NewGO<Player>(PRIORITY0);
			m_player[l_playerNum]->SetPlayerNum(l_playerNum);
			m_player[l_playerNum]->Init(l_map_dat.s_position, l_map_dat.s_rotation);
			l_playerNum++;
		}
		else if (!strcmp("torabasami", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<TrapA>(PRIORITY1);
		}
		else
		{
			l_mapChip = NewGO<MapObject>(PRIORITY1);
		}
		if (l_mapChip != nullptr)
		{
			m_mapchip.push_back(l_mapChip);
			m_mapchip.back()->Init(l_map_dat);
		}
	}
}

bool Map::Start()
{
	m_isLoad = true;
	return true;

}

void Map::Update()
{

}
