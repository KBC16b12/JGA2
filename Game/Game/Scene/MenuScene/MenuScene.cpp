#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../TitleScene/TitleScene.h"

MenuScene::MenuScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Menu.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

MenuScene::~MenuScene()
{
	//BGM’â~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool MenuScene::Start()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/Menu.wav");
	m_bgm->Play(true);

	return true;
}

void MenuScene::Update()
{
	SceneChange();
}

void MenuScene::Render(CRenderContext& renderContext)
{
}

/*!
*@brief	•`‰æŠÖ”B
*/
void MenuScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void MenuScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		if (!g_Fade->IsExecute())
		{
			m_runstat = enRun;
		}
		break;
	case enRun:
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = enTitle;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enGame;

			m_runstat = enFadeOut;
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enGame:
				g_gameScene->SetActiveFlag(true);
				break;
			case enTitle:
				NewGO<TitleScene>(0);
				if (g_gameScene != nullptr)
				{
					DeleteGO(g_gameScene);
				}
				break;
			default:
				break;
			}
			//©•ª‚ğíœB
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}