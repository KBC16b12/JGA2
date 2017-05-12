#pragma once

class Player;
class TimeSprite;
#include "../../Map/Map.h"

#define PARTICLE_NUM 20

/*!
 *@brief	ゲームシーン。
 */
class GameScene : public IGameObject
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	GameScene();

	/*!
	 *@brief	デストラクタ。
	 */
	~GameScene();

	/*!
	*@brief 初期化関数
	*/
	void Init(std::vector<SMapInfo> map_data, char* bgm_path);

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

	Player* const GetPlayer(int playernum)
	{
		return m_map->GetPlayer(playernum);
	}

	void SetActiveFlags(bool flag);

	void OnDestroy();

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	bool						m_isLoad;
	char*						m_bgm_path;						//BGMのファイルパス
	CSoundSource*				m_bgm;							//BGMソース。
	Map*						m_map;							//マップ
	CLight						m_light;								//!<ライト。
	RunStat						m_runstat = enFadeIn;			//フェードステータス
	SceneData					m_scenedata;					//画面遷移データ
	TimeSprite*					m_time;
};

extern GameScene* g_gameScene;
