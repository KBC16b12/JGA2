#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "../../HUD/Bar.h"
#include "Player/Player.h"
#include "../../Map/Map.h"
#include "../../HUD/TimeSprite.h"
#include "../../Camera/GameCamera.h"

GameScene* g_gameScene = nullptr;

GameScene::GameScene()
{
	m_map = NewGO<Map>(PRIORITY1);
	m_time = NewGO<TimeSprite>(PRIORITY1);
}

void GameScene::Init(std::vector<SMapInfo> map_data, char* bgm_path)
{
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i] = NewGO<Player>(PRIORITY0);
		m_player[i]->SetPlayerNum(i);
	}

	int l_half_w = Engine().GetScreenWidth() / 2;
	int l_half_h = Engine().GetScreenHeight() / 2;
	g_gameCamera[0]->SetViewPort(0, 0, l_half_w, l_half_h, m_player[0]->GetPlayerNUm());
	g_gameCamera[1]->SetViewPort(l_half_w, 0, l_half_w, l_half_h, m_player[1]->GetPlayerNUm());
	g_gameCamera[2]->SetViewPort(0, l_half_h, l_half_w, l_half_h, m_player[2]->GetPlayerNUm());
	g_gameCamera[3]->SetViewPort(l_half_w, l_half_h, l_half_w, l_half_h, m_player[3]->GetPlayerNUm());
	m_map->Init(map_data);
	m_bgm_path = bgm_path;
}

GameScene::~GameScene()
{
	//BGM停止
	m_bgm->Stop();
	DeleteGO(m_bgm);
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		DeleteGO(m_player[i]);
	}
	DeleteGO(m_map);
	DeleteGO(m_time);
	g_gameScene = nullptr;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		g_gameCamera[i]->FinishViewPort();
	}
}

bool GameScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init(m_bgm_path);
	//m_bgm->Play(true);

	//ライトを初期化。
	m_light.SetAmbinetLight(CVector3::One);


	return true;
}

void GameScene::Update()
{
	SceneChange();
}

/*!
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext, int playernum)
{
	m_map->Render(renderContext, playernum);
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i]->Render(renderContext, playernum);
	}
}

/*!
*@brief	描画関数。
*/
void GameScene::PostRender(CRenderContext& renderContext, int playernum)
{
	m_time->PostRender(renderContext, playernum);

	m_player[playernum]->PostRender(renderContext, playernum);
}

/*!
*@brief	画面遷移関数。
*/
void GameScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		//フェードイン
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		//動作中
		SetActiveFlags(true);
		//スタートボタン押下
		if (Pad(0).IsTrigger(enButtonStart))
		{
			//メニューへ遷移
			m_scenedata = enMenu;

			m_runstat = enFadeOut;

			SetActiveFlags(false);
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			//リザルトへ遷移
			m_scenedata = enResult;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			//画面生成
			switch (m_scenedata)
			{
			case enMenu:
				NewGO<MenuScene>(PRIORITY1);
				break;
			case enResult:
				NewGO<ResultScene>(PRIORITY1);
			default:
				break;
			}
			m_runstat = enRun;
			g_gameScene->SetActiveFlag(false);
			
			//メニュー画面への遷移でない
			if (m_scenedata != enMenu)
			{
				//自分を削除。
				DeleteGO(this);
			}
			return;
		}
		break;
	default:
		break;
	}
}

void GameScene::SetActiveFlags(bool flag)
{
	//ここで生成したオブジェクトの動作変更
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i]->SetActiveFlag(flag);
	}
	if (flag)
	{
		m_bgm->Play(true);
	}
	else
	{
		m_bgm->Stop();
	}
	m_map->SetActiveFlag(flag);
}