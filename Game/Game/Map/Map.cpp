#include "stdafx.h"
#include "Map.h"
#include "../MapObject.h"
#include "../Camera/GameCamera.h"
#include "../Item/Item.h"
#include "../Player/Player.h"

Map::Map()
{
	m_isLoad = false;
}

Map::~Map()
{
	//�}�b�v�`�b�v�̃f�[�^�폜
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
	//�}�b�v�`�b�v�̍쐬
	for each(SMapInfo l_map_dat in map_dat)
	{
		MapChip *l_mapChip = nullptr;
		if (!strcmp("Itembox", l_map_dat.s_modelName))
		{
			l_mapChip = NewGO<Item>(PRIORITY1);
		}
		else if (!strcmp("Player", l_map_dat.s_modelName))
		{
			m_player[l_playerNum] = NewGO<Player>(PRIORITY0);
			m_player[l_playerNum]->SetPlayerNum(l_playerNum);
			m_player[l_playerNum]->SetPosition(l_map_dat.s_position);
			l_playerNum++;
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

void Map::Render(CRenderContext& renderContext, int playernum)
{
	for (MapChip* chip : m_mapchip)
	{
		chip->Render(renderContext, playernum);
	}
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i]->Render(renderContext, playernum);
	}
}

void Map::PostRender(CRenderContext& renderContext, int playernum)
{
	m_player[playernum]->PostRender(renderContext, playernum);
}