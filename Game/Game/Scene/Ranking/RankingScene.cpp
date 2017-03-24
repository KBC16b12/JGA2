#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../Ranking/RankingScene.h"
#include "../SoloScene/SoloScene.h"

RankingScene::RankingScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Ranking.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

RankingScene::~RankingScene()
{
}

bool RankingScene::Start()
{
	return true;
}

void RankingScene::Update()
{
	SceneChange();
}

void RankingScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void RankingScene::SceneChange()
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
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enSolo;

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
			case enSolo:
				NewGO<SoloScene>(0);
				break;
			default:
				break;
			}
			//�������폜�B
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}
