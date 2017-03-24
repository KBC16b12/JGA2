#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../JoinScene/JoinScene.h"
#include "../TitleScene/TitleScene.h"
#include "../WaitScene/WaitScene.h"

JoinScene::JoinScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Join.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

JoinScene::~JoinScene()
{
}

bool JoinScene::Start()
{
	return true;
}

void JoinScene::Update()
{
	SceneChange();
}

void JoinScene::Render(CRenderContext& renderContext)
{
}

void JoinScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void JoinScene::SceneChange()
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
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enWait;

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
			case enWait:
				NewGO<WaitScene>(0);
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