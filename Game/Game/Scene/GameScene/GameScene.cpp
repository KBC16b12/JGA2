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
const PlayerMeshState g_playerMeshState[PLAYERMESHNUM] =
{
	{"Head", 1.6f},
	{"Hat" , 0.2f},
	{"Body", 1.6f},
	{"RightHand", 0.4f},
	{"LeftHand", 0.4f}
};
std::vector<CSkinModelData*> g_playerMeshModel;

GameScene::GameScene()
{
	m_map = NewGO<Map>(PRIORITY1);
	m_time = NewGO<TimeSprite>(PRIORITY1);

	m_end_timer = 0.0f;

	m_TimerOverTex = TextureResources().LoadEx("Assets/sprite/TIME UP.png");
	m_TimerOver.Init(m_TimerOverTex);
	m_TimerOver.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
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
		g_gameCamera[i]->Reset();
	}
	Sky().SetDisable();

	delete g_randomPosManager;
	g_randomPosManager = nullptr;

}

bool GameScene::Start()
{

	TextureResources().Load("Assets/particle/snowman.png");
	TextureResources().Load("Assets/particle/Explosion5.png");
	TextureResources().Load("Assets/particle/Explosion1.png");
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init(m_bgm_path);
	m_bgm->SetVolume(0.33f);
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
	if (g_playerMeshModel.empty())
	{
		for (int i = 0; i < PLAYERMESHNUM; i++)
		{
			char l_modelName[60];
			sprintf(l_modelName, "Assets/modelData/snowman_%s.X", g_playerMeshState[i].name);
			CSkinModelData* l_modelData = new CSkinModelData;
			l_modelData->LoadModelData(l_modelName, NULL);
			l_modelData->SetTechnique(enTecShaderHandle_Toon);
			g_playerMeshModel.push_back(l_modelData);
		}
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
		if (m_time->IsFinish() ||
			Pad(0).IsPress(enButtonStart) ||
			Pad(1).IsPress(enButtonStart) ||
			Pad(2).IsPress(enButtonStart) ||
			Pad(3).IsPress(enButtonStart))
		{
			m_end_timer += GameTime().GetFrameDeltaTime();
		}

		if (END_TIMER <= m_end_timer)
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

void GameScene::PostRender(CRenderContext& renderContext)
{
	if (!IsTimeOver())
	{
		return;
	}

	m_TimerOver.Draw(renderContext);
}

void GameScene::PostRender(CRenderContext& renderContext, int cameraNum)
{
	if (!IsTimeOver())
	{
		return;
	}

	m_TimerOver.Draw(renderContext);
}