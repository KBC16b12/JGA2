#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../JoinScene/JoinScene.h"
#include "../WaitScene/WaitScene.h"
#include "../../Network/Network.h"

namespace
{
	std::vector<SMapInfo> n_multi_map_dat =
	{
#include "../../Map/MapData/Sample.h"
	};
}

WaitScene::WaitScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Wait.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

WaitScene::~WaitScene()
{
	//BGM停止
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

void WaitScene::Init(bool isHost, CharData character)
{
	m_isHost = isHost;
	m_char = character;
}

bool WaitScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Wait.wav");
	m_bgm->Play(true);
	return true;
}

void WaitScene::Update()
{
	SceneChange();

	m_isHost ? Host() : Join();
}

void WaitScene::Host()
{
}

void WaitScene::Join()
{
}

void WaitScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void WaitScene::PostRender(CRenderContext& renderContext, int cameraNum)
{
	m_Sample.Draw(renderContext);
}

void WaitScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		if (!g_Fade->IsExecute())
		{
			//フェード中でない
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		if (Pad(0).IsTrigger(enButtonStart))
		{
			//Joinへ遷移
			m_scenedata = enJoin;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enGame;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enGame:
				g_gameScene = NewGO<GameScene>(PRIORITY1);
				g_gameScene->Init(n_multi_map_dat, "Assets/sound/GameBGM.wav");
				break;
			case enJoin:
				NewGO<JoinScene>(PRIORITY1);
				break;
			default:
				break;
			}
			//自分を削除。
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}