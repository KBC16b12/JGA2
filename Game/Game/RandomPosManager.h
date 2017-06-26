#pragma once
//アイテムの配置情報
struct ItemPosData
{
	SMapInfo	m_mapDat;
	bool		m_isUse;	//ゲームがスタートするときに決める配置だけフラグを立ててかぶらないようにする
};

//プレイヤーの配置情報
struct PlayerPosData
{
	SMapInfo	m_mapDat;
	bool		m_isUse;	//ゲームがスタートするときに決める配置だけフラグを立ててかぶらないようにする
};

class RandomPosManager
{
public:
	RandomPosManager();

	~RandomPosManager();


	//プレイヤーのデータを追加
	void AddPlayerData(SMapInfo mapDat)
	{
		m_playerData.push_back({ mapDat, false });
	}

	//アイテムのデータを追加
	void AddItemData(SMapInfo mapDat)
	{
		m_itemData.push_back({mapDat, false});
	}

	//リスポーン時のプレイヤーの配置情報を取得
	SMapInfo GetPlayerRespawnPos(int playerNum);

	//スタート時のプレイヤーの配置情報を取得(配置情報自体はリスポーン時のものと一緒
	SMapInfo GetPlayerStartPos();

	//アイテムの配置情報を取得
	SMapInfo GetItemData();

private:
	std::vector<PlayerPosData> m_playerData;
	std::vector<ItemPosData> m_itemData;
};

extern RandomPosManager *g_randomPosManager;