#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../CharScene/CharScene.h"
#include "../SoloScene/SoloScene.h"
#include "../TitleScene/TitleScene.h"
#include "Scene/GameScene/GameScene.h"


namespace
{
	std::vector<SMapInfo> n_solo_map_dat =
	{
#include "../../Map/MapData/locationInfo2.h"
	};
}

TitleScene::TitleScene()
{
	m_TitleTex = TextureResources().Load("Assets/sprite/Title.png");
	m_Title.Init(m_TitleTex);
	m_Title.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	m_StartTex = TextureResources().Load("Assets/sprite/Title_start.png");
	m_Start.Init(m_StartTex);
	m_Start.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	m_alpha = 1.0f;
	m_Start.SetAlpha(m_alpha);
	m_isAlpha = true;
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
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/TitleBGM.wav");
	m_bgm->Play(true);
	return true;
}
void TitleScene::Update()
{
	float l_alphaSpeed = 0.05f;
	if (m_isAlpha)
	{
		m_alpha -= l_alphaSpeed;
		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
			m_isAlpha = !m_isAlpha;
		}
	}
	else
	{
		m_alpha += l_alphaSpeed;
		if (1.0f <= m_alpha)
		{
			m_alpha = 1.0f;
			m_isAlpha = !m_isAlpha;
		}
	}
	m_Start.SetAlpha(m_alpha);
	SceneChange();
}

void TitleScene::Render(CRenderContext& renderContext)
{
	//Draw(renderContext);
}

void TitleScene::Render(CRenderContext& renderContext, int cameraNum)
{
	//Draw(renderContext);
}

void TitleScene::PostRender(CRenderContext& renderContext)
{
	Draw(renderContext);
}

void TitleScene::PostRender(CRenderContext& renderContext, int cameraNum)
{
	Draw(renderContext);
}

void TitleScene::Draw(CRenderContext& renderContext)
{
	m_Title.Draw(renderContext);
	m_Start.Draw(renderContext);
}

/*!
*@brief	âÊñ ëJà⁄ä÷êîÅB
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
	case enRun:/*
		if (Pad(0).IsTrigger(enButtonB))
		{
			m_scenedata = enSolo;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}*/
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			if (Pad(i).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonStart))
			{
				m_scenedata = enChar;

				m_runstat = enFadeOut;

				g_Fade->StartFadeOut();
				return;
			}
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enChar:
				//NewGO<CharScene>(PRIORITY1)->Init(true);
				g_gameScene = NewGO<GameScene>(PRIORITY1);
				g_gameScene->Init(n_solo_map_dat, "Assets/sound/BattleScene.wav");
				break;
			case enSolo:
				NewGO<SoloScene>(PRIORITY1);
				break;
			default:
				break;
			}
			//é©ï™ÇçÌèúÅB
			DeleteGO(this);
			return;
		}
		break;
	default:
		break;
	}
}