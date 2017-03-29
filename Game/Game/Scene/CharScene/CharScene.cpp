#include "stdafx.h"
#include "../CharScene/CharScene.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../SoloScene/SoloScene.h"
#include "../JoinScene/JoinScene.h"
#include "../TitleScene/TitleScene.h"

namespace
{
	std::vector<SMapInfo> n_solo_map_dat =
	{
#include "../../Map/MapData/Sample.h"
	};
}

CharScene::CharScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Char.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

CharScene::~CharScene()
{
	//BGM停止
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

void CharScene::Init(bool isMulti)
{
	m_isMulti = isMulti;
}

bool CharScene::Start()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/Wait.wav");
	m_bgm->Play(true);
	return true;
}

void CharScene::Update()
{
	SceneChange();
}

void CharScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void CharScene::SceneChange()
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
			m_scenedata = (m_isMulti ? enTitle : enSolo);

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = (m_isMulti ? enJoin : enGame);

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
				g_gameScene = NewGO<GameScene>(0);
				g_gameScene->Init(n_solo_map_dat);
				break;
			case enJoin:
				NewGO<JoinScene>(0);
				break;
			case enTitle:
				NewGO<TitleScene>(0);
				break;
			case enSolo:
				NewGO<SoloScene>(0);
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