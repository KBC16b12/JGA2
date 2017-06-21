#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "../../HUD/Bar.h"
#include "Player/Player.h"
#include "../../HUD/TimeSprite.h"
#include "../../Camera/GameCamera.h"
#include "RandomPosManager.h"

GameScene* g_gameScene = nullptr;
CSkinModelData* g_bulletModel = nullptr;

GameScene::GameScene()
{
	m_map = NewGO<Map>(PRIORITY1);
	m_time = NewGO<TimeSprite>(PRIORITY1);
}


void GameScene::Init(std::vector<SMapInfo> map_data, char* bgm_path)
{
	if (g_randomPosManager == nullptr)
	{
		g_randomPosManager = new RandomPosManager;
	}
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

	delete g_randomPosManager;
	g_randomPosManager = nullptr;

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
	Sky().SetSceneLight(g_defaultLight);
	Sky().SetLuminance({ 2.5f, 2.5f, 2.5f });
	Sky().SetNightAmbientLight({ 0.05f, 0.05f, 0.05f });

	Sky().SetDayAmbientLight({ 0.3f, 0.3f, 0.3f });

	Sky().SetEnable(&g_gameCamera[0]->GetCamera(), &g_defaultLight);

	std::vector<CCamera*> l_cameraVector;
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		l_cameraVector.push_back(&g_gameCamera[i]->GetCamera());
	}
	Sky().ViewPortSetCamera(l_cameraVector);
	if (g_bulletModel == nullptr)
	{
		g_bulletModel = new CSkinModelData;
		g_bulletModel->LoadModelData("Assets/modelData/Bullet.X", NULL);
	}
	return true;
}

void GameScene::Update()
{
	SceneChange();
	CVector3 l_lightPos = Sky().GetSunPosition();
	l_lightPos.Normalize();
	l_lightPos.Scale(30.0f);
	ShadowMap().SetLightPosition(l_lightPos);
	ShadowMap().SetLightTarget(CVector3::Zero);
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
		//if (Pad(0).IsTrigger(enButtonStart))
		//{
		//	//メニューへ遷移
		//	m_scenedata = enMenu;

		//	m_runstat = enFadeOut;

		//	SetActiveFlags(false);
		//	return;
		//}
		if (m_time->IsFinish() || Pad(0).IsTrigger(enButtonStart))
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
				ResultScene *result = NewGO<ResultScene>(PRIORITY1);
				int pKill[4];
				for (int i = 0; i < 4; i++)
				{
					pKill[i] = GetPlayer(i)->GetKillCount();
				}
				result->SetPlayerKillScore(pKill);
			//default:
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
		//m_bgm->Play(true);
	}
	else
	{
		m_bgm->Stop();
	}
	m_map->SetActiveFlag(flag);
}

