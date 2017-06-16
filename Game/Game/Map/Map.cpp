#include "stdafx.h"
#include "Map.h"
#include "../MapObject.h"
#include "../Camera/GameCamera.h"
#include "../Item/Item.h"
#include "../Trap.h"
#include "../Item/ItemMaker.h"
#include "../Player/Player.h"
#include "RandomPosManager.h"

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
	//マップチップの作成
	for each(SMapInfo l_map_dat in map_dat)
	{
		MapChip *l_mapChip = nullptr;
		if (!strcmp("itembox1-1", l_map_dat.s_modelName))
		{
			CQuaternion multi;
			multi.SetRotation(CVector3::AxisX, CMath::DegToRad(-90));
			l_map_dat.s_rotation.Multiply(multi);
			g_randomPosManager->AddItemData(l_map_dat);
		}
		else if (!strcmp("snowman1-3", l_map_dat.s_modelName))
		{
			CQuaternion multi;
			multi.SetRotation(CVector3::AxisX, CMath::DegToRad(90));
			l_map_dat.s_rotation.Multiply(multi);
			multi.SetRotation(CVector3::AxisY, CMath::DegToRad(180));
			l_map_dat.s_rotation.Multiply(multi);
			g_randomPosManager->AddPlayerData(l_map_dat);
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
	for (int i = 0; i < ITEM_NUM; i++)
	{
		SMapInfo l_map_dat = g_randomPosManager->GetItemData();
		MapChip *l_mapChip = NewGO<ItemMaker>(PRIORITY1);
		m_mapchip.push_back(l_mapChip);
		m_mapchip.back()->Init(l_map_dat);
	}
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		SMapInfo l_map_dat = g_randomPosManager->GetPlayerStartPos();
		m_player[i] = NewGO<Player>(PRIORITY0);
		m_player[i]->Init(l_map_dat.s_position, l_map_dat.s_rotation, i);
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
