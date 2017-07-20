#include "stdafx.h"
#include "Map.h"
#include "MapObject.h"
#include "InvisibleObject.h"
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
	m_mapchip.clear();
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		DeleteGO(m_player[i]);
	}
	if (m_isInstancing)
	{
		m_mapInfo.clear();
		SkinModelDataResources().InstancingRelease();
	}
}

void Map::Init(std::vector<SMapInfo> map_dat)
{
	//マップチップの作成
	for each(SMapInfo l_map_dat in map_dat)
	{
		bool l_isInstancing = false;
		MapChip *l_mapChip = nullptr;
		if (!strcmp(l_map_dat.s_modelName, "X_Roads") ||
			!strcmp(l_map_dat.s_modelName, "L_Roads") ||
			!strcmp(l_map_dat.s_modelName, "T_Roads") ||
			!strcmp(l_map_dat.s_modelName, "Road"))
		{
			l_isInstancing = true;
		}
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
			//multi.SetRotation(CVector3::AxisX, CMath::DegToRad(90));
			//l_map_dat.s_rotation.Multiply(multi);
			multi.SetRotation(CVector3::AxisY, CMath::DegToRad(180));
			l_map_dat.s_rotation.Multiply(multi);
			g_randomPosManager->AddPlayerData(l_map_dat);
		}
		else if (!strcmp("torabasami", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<TrapA>(PRIORITY1);
		}
		else if (!strcmp("InvisibleObject2", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<InvisibleObject>(PRIORITY1);
		}
		else
		{
			if (l_isInstancing)
			{
				int l_hash = CUtil::MakeHash(l_map_dat.s_modelName);
				bool mapchipFlg = true;
				for (const MapChipInfo& mapChipInfo : m_mapInfo)
				{
					if (mapChipInfo.hash == l_hash)
					{
						mapChipInfo.map_data->push_back(l_map_dat);
						mapchipFlg = false;
						break;
					}
				}
				if (mapchipFlg)
				{
					m_mapInfo.push_back({ new std::vector<SMapInfo>, l_hash });
					m_mapInfo.back().map_data->push_back(l_map_dat);
				}
			}
			else
			{
				l_mapChip = NewGO<MapObject>(PRIORITY1);
			}
		}
		if (l_mapChip != nullptr)
		{
			m_mapchip.push_back(l_mapChip);
			m_mapchip.back()->Init(l_map_dat);
		}

	}
	if (!m_mapInfo.empty())
	{
		for (MapChipInfo& mapChipInfo : m_mapInfo)
		{
			MapObject *l_mapObject = NewGO<MapObject>(PRIORITY1);
			l_mapObject->Init(mapChipInfo.map_data);
			m_mapchip.push_back(l_mapObject);
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
