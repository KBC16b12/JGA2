#include "stdafx.h"
#include "Map.h"
#include "../MapObject.h"
#include "../Camera/GameCamera.h"
#include "../Item/Item.h"
#include "../Trap.h"

Map::Map()
{
}

Map::~Map()
{
	//�}�b�v�`�b�v�̃f�[�^�폜
	for each(MapChip* l_map_dat in m_mapchip)
	{
		l_map_dat->SetActiveFlag(false);
		DeleteGO(l_map_dat);
	}
}

void Map::Init(std::vector<SMapInfo> map_dat)
{
	//�}�b�v�`�b�v�̍쐬
	for each(SMapInfo l_map_dat in map_dat)
	{
		MapChip *l_mapChip;
		if (!strcmp("Itembox", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<Item>(PRIORITY1);
		}
		else if (!strcmp("torabasami", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<TrapA>(PRIORITY1);
		}
		else
		{
			l_mapChip = NewGO<MapObject>(PRIORITY1);
		}
		m_mapchip.push_back(l_mapChip);
		m_mapchip.back()->Init(l_map_dat);

		/*MapChip *l_mapChip2;
		if (!strcmp("torabasami", l_map_dat.s_modelName))
		{
			l_mapChip2 = NewGO<TrapA>(PRIORITY1);
		}
		else
		{
			l_mapChip2 = NewGO<MapObject>(PRIORITY1);
		}
		m_mapchip.push_back(l_mapChip2);
		m_mapchip.back()->Init(l_map_dat);*/
	}
}

bool Map::Start()
{
	return true;
}

void Map::Update()
{

}

void Map::Render(CRenderContext& renderContext, int playernum)
{
	for (MapChip* chip : m_mapchip)
	{
		chip->Render(renderContext, playernum);
	}
}

void Map::PostRender(CRenderContext& renderContext, int playernum)
{

}