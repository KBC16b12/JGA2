#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "../../HUD/Bar.h"
#include "Player/Player.h"
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
	m_map->Init(map_data);
	m_bgm_path = bgm_path;
}

GameScene::~GameScene()
{
	//BGM停止
	m_bgm->Stop();
	DeleteGO(m_bgm);
	DeleteGO(m_map);
	DeleteGO(m_time);
	g_gameScene = nullptr;
	GetViewSprit().Finish();
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		g_gameCamera[i]->FinishViewPort();
	}
	Sky().SetDisable();
}

bool GameScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init(m_bgm_path);
	m_bgm->Play(true);

	int l_half_w = Engine().GetScreenWidth() / 2;
	int l_half_h = Engine().GetScreenHeight() / 2;
	g_gameCamera[0]->SetViewPort({ 0, 0, l_half_w, l_half_h }, m_map->GetPlayer(0));
	g_gameCamera[1]->SetViewPort({ l_half_w, 0, l_half_w, l_half_h }, m_map->GetPlayer(1));
	g_gameCamera[2]->SetViewPort({ 0, l_half_h, l_half_w, l_half_h }, m_map->GetPlayer(2));
	g_gameCamera[3]->SetViewPort({ l_half_w, l_half_h, l_half_w, l_half_h }, m_map->GetPlayer(3));
	GetViewSprit().Start();
	//m_light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	//m_light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	//m_light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, 0.707f));
	//m_light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, 0.0f));
	//m_light.SetDiffuseLightColor(0, CVector4(2.0f, 2.0f, 2.0f, 10.0f));
	//m_light.SetDiffuseLightColor(1, CVector4(0.8f, 0.8f, 0.8f, 1.0f));
	//m_light.SetDiffuseLightColor(2, CVector4(0.8f, 0.8f, 0.8f, 1.0f));
	//m_light.SetDiffuseLightColor(3, CVector4(0.8f, 0.8f, 0.8f, 1.0f));
	//m_light.SetLimLightColor(CVector4(2.0f, 2.0f, 2.0f, 1.0f));
	//m_light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));
	//Sky().SetSceneLight(m_light);
	//Sky().SetLuminance({ 10.5f, 10.5f, 10.5f });
	//Sky().SetNightAmbientLight({ 0.05f, 0.05f, 0.05f });
	//Sky().SetDayAmbientLight({ 0.7f, 0.7f, 0.7f });
	//Sky().SetEnable(&g_gameCamera[0]->GetCamera(), &m_light);
	//std::vector<CCamera*> l_cameraVector;
	//for (int i = 0;i < PLAYER_NUM;i++)
	//{
	//	l_cameraVector.push_back(&g_gameCamera[i]->GetCamera());
	//}
	//Sky().ViewPortSetCamera(l_cameraVector);
	return true;
}

void GameScene::Update()
{
	SceneChange();
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
		if (m_time->IsFinish())
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

void GameScene::OnDestroy()
{

}