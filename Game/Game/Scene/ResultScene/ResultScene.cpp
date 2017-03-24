#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../ResultScene/ResultScene.h"
#include "../TitleScene/TitleScene.h"

ResultScene::ResultScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Result.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

ResultScene::~ResultScene()
{
}

bool ResultScene::Start()
{
	return true;
}

void ResultScene::Update()
{
	SceneChange();
}

void ResultScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void ResultScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
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
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enTitle:
				NewGO<TitleScene>(0);
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