#pragma once
struct ItemPosData
{
	SMapInfo	m_mapDat;
	bool		m_isUse;
};

struct PlayerPosData
{
	SMapInfo	m_mapDat;
	bool		m_isUse;
};

class RandomPosManager
{
public:
	RandomPosManager();

	~RandomPosManager();

	void AddPlayerData(SMapInfo mapDat)
	{
		m_playerData.push_back({ mapDat, false });
	}

	void AddItemData(SMapInfo mapDat)
	{
		m_itemData.push_back({mapDat, false});
	}

	SMapInfo GetPlayerRespawnPos(int playerNum);

	SMapInfo GetPlayerStartPos();

	SMapInfo GetItemData();

private:
	std::vector<PlayerPosData> m_playerData;
	std::vector<ItemPosData> m_itemData;
};

extern RandomPosManager *g_randomPosManager;