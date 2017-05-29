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
	//BGM’â~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool RankingScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Ranking.wav");
	m_bgm->Play(true);

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

void RankingScene::PostRender(CRenderContext& renderContext, int cameraNum)
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
				NewGO<SoloScene>(PRIORITY1);
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
