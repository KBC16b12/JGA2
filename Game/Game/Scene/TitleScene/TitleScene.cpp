#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../CharScene/CharScene.h"
#include "../SoloScene/SoloScene.h"
#include "../TitleScene/TitleScene.h"

TitleScene::TitleScene()
{
	
}

TitleScene::~TitleScene()
{
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

void TitleScene::Init(RunStat stat)
{
	m_runstat = stat;
}

bool TitleScene::Start()
{
	m_TitleTex = TextureResources().LoadEx("Assets/sprite/Title.png");
	m_Title.Init(m_TitleTex);
	m_Title.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/TitleBGM.wav");
	m_bgm->Play(true);

	return true;
}
void TitleScene::Update()
{
	SceneChange();
}

void TitleScene::PostRender(CRenderContext& renderContext)
{
	m_Title.Draw(renderContext);
}

/*!
*@brief	‰æ–Ê‘JˆÚŠÖ”B
*/
void TitleScene::SceneChange()
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
		if (Pad(0).IsTrigger(enButtonB))
		{
			m_scenedata = enChar;

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
				NewGO<CharScene>(0)->Init(true);
				break;
			case enSolo:
				NewGO<SoloScene>(0);
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