#include "stdafx.h"
#include "../CharScene/CharScene.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../SoloScene/SoloScene.h"
#include "../JoinScene/JoinScene.h"
#include "../TitleScene/TitleScene.h"

//namespace
//{
//	std::vector<SMapInfo> n_solo_map_dat =
//	{
//#include "../../Map/MapData/Sample.h"
//	};
//}

CharScene::CharScene()
{
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/Char.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

CharScene::~CharScene()
{
	//BGM��~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

void CharScene::Init(bool isMulti)
{
	m_isMulti = isMulti;
}

bool CharScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Wait.wav");
	m_bgm->Play(true);
	return true;
}

void CharScene::Update()
{
	SceneChange();
}

void CharScene::PostRender(CRenderContext& renderContext)
{
	m_Sample.Draw(renderContext);
}


void CharScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		if (!g_Fade->IsExecute())
		{
			//�t�F�[�h���łȂ�
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		if (Pad(0).IsTrigger(enButtonStart))
		{
			m_scenedata = (m_isMulti ? enTitle : enSolo);

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			m_scenedata = (m_isMulti ? enJoin : enGame);

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();

			m_char = enChar001;
			return;
		}
		if (Pad(0).IsTrigger(enButtonB))
		{
			m_scenedata = (m_isMulti ? enJoin : enGame);

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();

			m_char = enChar002;
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			switch (m_scenedata)
			{
			case enGame:
				//g_gameScene = NewGO<GameScene>(PRIORITY1);
				//g_gameScene->Init(n_solo_map_dat, "Assets/sound/GameBGM2.wav");
				break;
			case enJoin:
				NewGO<JoinScene>(PRIORITY1)->Init(m_char);
				break;
			case enTitle:
				NewGO<TitleScene>(PRIORITY1);
				break;
			case enSolo:
				NewGO<SoloScene>(PRIORITY1);
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