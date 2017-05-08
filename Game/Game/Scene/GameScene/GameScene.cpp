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
	m_isLoad = false;
	for (int i = 0;i < PARTICLE_NUM;i++)
	{
		m_particle[i] = nullptr;
	}
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
	int l_half_w = Engine().GetScreenWidth() / 2;
	int l_half_h = Engine().GetScreenHeight() / 2;
	g_gameCamera[0]->SetPlayer(m_map->GetPlayer(0));
	//g_gameCamera[0]->SetViewPort(0, 0, l_half_w, l_half_h, m_map->GetPlayer(0)->GetPlayerNum());
	//g_gameCamera[1]->SetViewPort(l_half_w, 0, l_half_w, l_half_h, m_map->GetPlayer(1)->GetPlayerNum());
	//g_gameCamera[2]->SetViewPort(0, l_half_h, l_half_w, l_half_h, m_map->GetPlayer(2)->GetPlayerNum());
	//g_gameCamera[3]->SetViewPort(l_half_w, l_half_h, l_half_w, l_half_h, m_map->GetPlayer(3)->GetPlayerNum());

	return true;
}

void GameScene::Update()
{
	SceneChange();
	for (int i = 0;i < PARTICLE_NUM;i++)
	{
		if (m_particle[i] != nullptr && m_particle[i]->IsDelete())
		{
			DeleteGO(m_particle[i]);
			m_particle[i] = nullptr;
		}
	}
}

/*!
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext, int playernum)
{
	m_map->Render(renderContext, playernum);
	for (int i = 0;i < PARTICLE_NUM;i++)
	{
		if (m_particle[i] != nullptr)
		{
			m_particle[i]->Render(renderContext, playernum);
		}
	}
}

/*!
*@brief	描画関数。
*/
void GameScene::PostRender(CRenderContext& renderContext, int playernum)
{
	m_time->PostRender(renderContext, playernum);
	m_map->PostRender(renderContext, playernum);
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
void GameScene::ParticleEmit(CRandom& random, const CCamera& camera, const SParicleEmitParameter& param, const CVector3& emitPosition)
{
	int i;
	for (i = 0;i < PARTICLE_NUM;i++)
	{
		if (m_particle[i] == nullptr)
		{
			break;
		}
	}
	m_particle[i] = NewGO<CParticleEmitter>(PRIORITY0);
	m_particle[i]->Init(random, camera, param, emitPosition);
	for (int j = 0;j < PLAYER_NUM;j++)
	{
		m_particle[i]->SetCamera(g_gameCamera[j]->GetCamera(), j);
	}
}