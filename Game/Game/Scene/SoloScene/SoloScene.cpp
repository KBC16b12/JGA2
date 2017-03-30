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
	//BGM��~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool SoloScene::Start()
{
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/Solo.wav");
	m_bgm->Play(true);

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

/*!
*@brief	��ʑJ�ڊ֐��B
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
			m_scenedata = enChar;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
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
				NewGO<CharScene>(0)->Init(false);
				break;
			case enRanking:
				NewGO<RankingScene>(0);
				break;
			case enTitle:
				NewGO<TitleScene>(0);
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