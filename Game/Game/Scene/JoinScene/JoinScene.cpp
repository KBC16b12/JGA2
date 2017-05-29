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
	//BGM��~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool JoinScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Join.wav");
	m_bgm->Play(true);

	return true;
}

void JoinScene::Init(CharData character)
{
	m_char = character;
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

void JoinScene::PostRender(CRenderContext& renderContext, int cameraNum)
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

			m_isHost = true;
			return;
		}
		if (Pad(0).IsTrigger(enButtonB))
		{
			m_scenedata = enWait;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();

			m_isHost = false;
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enTitle:
				NewGO<TitleScene>(PRIORITY1);
				break;
			case enWait:
				NewGO<WaitScene>(PRIORITY1)->Init(m_isHost, m_char);
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