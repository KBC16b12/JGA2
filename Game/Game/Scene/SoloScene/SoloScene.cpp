#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../CharScene/CharScene.h"
#include "../Ranking/RankingScene.h"
#include "../SoloScene/SoloScene.h"
#include "../TitleScene/TitleScene.h"

SoloScene::SoloScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Solo.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

SoloScene::~SoloScene()
{
	//BGM’â~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool SoloScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Solo.wav");
	//m_bgm->Play(true);

	return true;
}
void SoloScene::Update()
{
	SceneChange();
}

void SoloScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}

void SoloScene::PostRender(CRenderContext& renderContext, int cameraNum)
{
	m_Sample.Draw(renderContext);
}

/*!
*@brief	‰æ–Ê‘JˆÚŠÖ”B
*/
void SoloScene::SceneChange()
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
	case enRun:/*
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = enTitle;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = enChar;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}*/
		if (Pad(0).IsTrigger(enButtonB))
		{
			m_scenedata = enRanking;

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
			case enChar:
				NewGO<CharScene>(PRIORITY1)->Init(false);
				break;
			case enRanking:
				NewGO<RankingScene>(PRIORITY1);
				break;
			case enTitle:
				NewGO<TitleScene>(PRIORITY1);
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