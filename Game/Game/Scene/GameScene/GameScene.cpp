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
	//BGM��~
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
	//m_bgm->Play(true);

	int l_half_w = Engine().GetScreenWidth() / 2;
	int l_half_h = Engine().GetScreenHeight() / 2;
	g_gameCamera[0]->SetViewPort({ 0, 0, l_half_w, l_half_h }, m_map->GetPlayer(0));
	g_gameCamera[1]->SetViewPort({ l_half_w, 0, l_half_w, l_half_h }, m_map->GetPlayer(1));
	g_gameCamera[2]->SetViewPort({ 0, l_half_h, l_half_w, l_half_h }, m_map->GetPlayer(2));
	g_gameCamera[3]->SetViewPort({ l_half_w, l_half_h, l_half_w, l_half_h }, m_map->GetPlayer(3));
	GetViewSprit().Start();
	Sky().SetSceneLight(m_light);
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
*@brief	��ʑJ�ڊ֐��B
*/
void GameScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		//�t�F�[�h�C��
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		//���쒆
		SetActiveFlags(true);
		//�X�^�[�g�{�^������
		//if (Pad(0).IsTrigger(enButtonStart))
		//{
		//	//���j���[�֑J��
		//	m_scenedata = enMenu;

		//	m_runstat = enFadeOut;

		//	SetActiveFlags(false);
		//	return;
		//}
		if (m_time->IsFinish()/* || Pad(0).IsTrigger(enButtonStart)*/)
		{
			//���U���g�֑J��
			m_scenedata = enResult;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			//��ʐ���
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
			
			//���j���[��ʂւ̑J�ڂłȂ�
			if (m_scenedata != enMenu)
			{
				//�������폜�B
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

