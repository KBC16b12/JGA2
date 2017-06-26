#pragma once

class Player;
class TimeSprite;
#include "../../Map/Map.h"
#include "PlayerMeshCommon.h"

#define END_TIMER 1.0f

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

	Player* g_player;

	bool IsTimeOver()
	{
		return (0.0f < m_end_timer);
	}

	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender(CRenderContext& renderContext) override;

	void PostRender(CRenderContext& renderContext, int cameraNum) override;

private:
	/*!
	*@brief	画面遷移関数。
	*/
	void SceneChange();

	bool						m_isLoad;
	char*						m_bgm_path;						//BGMのファイルパス
	CSoundSource*				m_bgm;							//BGMソース。
	Player*						m_player[PLAYER_NUM];			//プレイヤ
	Map*						m_map;							//マップ
	CCamera						m_camera;						//!<カメラ。
	CLight						m_light;						//!<ライト。
	RunStat						m_runstat = enFadeIn;			//フェードステータス
	SceneData					m_scenedata;					//画面遷移データ
	TimeSprite*					m_time;
	CAnimation					m_playerAnimation;

	float						m_end_timer;

	CTexture*					m_TimerOverTex;						//!<サンプルのテクスチャ。
	CSprite						m_TimerOver;						//!<サンプルのスプライト。
};

extern GameScene* g_gameScene;
//PincerBullet用のモデル
extern CSkinModelData* g_bulletModel;

extern const PlayerMeshState g_playerMeshState[PLAYERMESHNUM];
extern std::vector<CSkinModelData*> g_playerMeshModel;
