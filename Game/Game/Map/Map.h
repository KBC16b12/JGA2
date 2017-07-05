#pragma once

#include "MapChip.h"
class Player;

struct MapChipInfo
{
	std::vector<SMapInfo> *map_data;
	int hash;
};

class Map : public IGameObject
{
public:
	/*!
	*@brief	コンストラクタ。
	*/
	Map();
	
	/*!
	*@brief	デストラクタ。
	*/
	~Map();
	
	/*!
	*@brief 初期化関数
	*@details 
	*/
	void Init(std::vector<SMapInfo> map_dat);

	/*!
	*@brief	開始関数。
	*@details
	* 初期化などをこの関数に実装してください。</br>
	* この関数がtrueを返すと本館数は以降のフレームでは呼ばれなくなります。</br>
	* そしてゲームオブジェクトの状態が初期化完了になりUpdate関数が呼ばれるようになります。</br>
	*@return	trueが帰ってきたら初期化完了。
	*/
	bool Start() override;
	
	/*!
	*@brief	更新関数。
	*/
	void Update() override;

	Player* GetPlayer(int playerNum)
	{
		return m_player[playerNum];
	}

	const std::vector<MapChip*>& GetMap()
	{
		return m_mapchip;
	}

private:
	bool						m_isLoad;
	Player*						m_player[PLAYER_NUM];
	std::vector<MapChip*>		m_mapchip;			//マップチップリスト
	std::vector<MapChipInfo>	m_mapInfo;
	bool						m_isInstancing;
};

