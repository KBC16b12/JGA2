#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../ResultScene/ResultScene.h"
#include "../TitleScene/TitleScene.h"
#include "../../Player/Player.h"
#include"../GameScene/GameScene.h"

ResultScene::ResultScene()
{
	m_rcount = 0;

	for (int i = 0; i < 4; i++)
	{
		char cp[60];
		sprintf(cp, "Assets/sprite/raking/%d.jpg", i);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0; i < 4; i++) {
		m_sprite[i].Init(m_texture[i]);
		m_sprite[i].SetPosition({ -200.0f,250.0f - i * 150});
		m_sprite[i].SetSize({ 100.0f,100.0f });
	}
	//m_SampleTex = TextureResources().LoadEx("Assets/sprite/Result.png");
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/raking_back.jpg");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

ResultScene::~ResultScene()
{
	//BGM’â~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool ResultScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Result1.wav");
	m_bgm->Play(true);

	return true;
}

void ResultScene::Update()
{
	Player* playerArray[4];
	for (int i = 0; i < 4; i++)
	{
		pNum[i] = i;
	}

	//~‡‚É•À‚Ñ‘Ö‚¦
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (pKill[pNum[j]] > pKill[pNum[i]])
			{
				tmp = pNum[i];
				pNum[i] = pNum[j];
				pNum[j] = tmp;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		char cp[60];
		sprintf(cp, "Assets/sprite/playerlist/%d.jpg", pNum[i]);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0; i < 4; i++) {
		m_sprite2[i].Init(m_texture[i]);
		m_sprite2[i].SetPosition({ 100.0f,250.0f - i * 150 });
		m_sprite2[i].SetSize({ 300.0f,100.0f });
	}

	SceneChange();
}

void ResultScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);

	for (int i = 0; i < 4; i++)
	{
		m_sprite[i].Draw(renderContext);
	}

	for (int i = 0; i < 4; i++)
	{
		m_sprite2[i].Draw(renderContext);
	}
}

void ResultScene::PostRender(CRenderContext& renderContext, int cameraNum)
{
	m_Sample.Draw(renderContext);

	for (int i = 0; i < 4; i++)
	{
		m_sprite[i].Draw(renderContext);
	}

	for (int i = 0; i < 4; i++)
	{
		m_sprite2[i].Draw(renderContext);
	}
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