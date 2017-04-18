#pragma once

class Player;
class KillCount;
class Time;
#include"../../Map/Map.h"

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

	/*!
	*@brief	描画関数。
	*/
	void Render(CRenderContext& renderContext);

	Player* const GetPlayer(int playernum)
	{
		return m_player[playernum];
	}
	
	const std::vector<MapChip*>&  GetMap()
	{
		return m_map->GetMap();
	}

	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender(CRenderContext& renderContext) override;

	void SetActiveFlags(bool flag);

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();


	char*						m_bgm_path;						//BGMのファイルパス
	CSoundSource*				m_bgm;							//BGMソース。
	Player*						m_player[PLAYER_NUM];						//プレイヤ
	Map*						m_map;							//マップ
	CCamera						m_camera;								//!<カメラ。
	CLight						m_light;								//!<ライト。
	RunStat						m_runstat = enFadeIn;			//フェードステータス
	SceneData					m_scenedata;					//画面遷移データ
	KillCount*					m_killcount;					//キル数のスプライト
	Time*						m_time;
};

extern GameScene* g_gameScene;
