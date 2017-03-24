#include "stdafx.h"
#include "Map.h"
#include "MapChip.h"

Map::Map()
{
}

Map::~Map()
{
	//マップチップのデータ削除
	for each(MapChip* l_map_dat in m_mapchip)
	{
		l_map_dat->SetActiveFlag(false);
		DeleteGO(l_map_dat);
	}
}

void Map::Init(std::vector<SMapInfo> map_dat)
{
	//マップチップの作成
	for each(SMapInfo l_map_dat in map_dat)
	{
		m_mapchip.push_back(NewGO<MapChip>(0));
		m_mapchip.back()->Init(l_map_dat);
	}
}

bool Map::Start()
{
	return true;
}

void Map::Update()
{

}

void Map::PostRender(CRenderContext& renderContext)
{

}