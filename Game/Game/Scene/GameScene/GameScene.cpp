#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"
#include "../../Map/Map.h"

GameScene* g_gameScene = nullptr;

GameScene::GameScene()
{
	m_killcount = 0;
	m_time = 999;
	
	for (int i = 0;i < 10;i++) {
		char cp[60];
		sprintf(cp, "Assets/sprite/NewNumber/%d.png", i);
		m_texture[i]= TextureResources().LoadEx(cp);
	}
	for (int i = 0;i < 3;i++) {
		m_timesprite[i].Init(m_texture[9]);
		m_timesprite[i].SetPosition({ -50.0f + i * 50,320.0f });
		m_timesprite[i].SetSize({ 50.0f,50.0f });
	}
	for (int i = 0;i < 2;i++) {
		m_killsprite[i].Init(m_texture[2]);
		m_killsprite[i].SetPosition({ 400.0f + i * 50,320.0f });
		m_killsprite[i].SetSize({ 50.0f,50.0f });
	}
	m_map = NewGO<Map>(0);
}

void GameScene::Init(std::vector<SMapInfo> map_data, char* bgm_path)
{
	m_map->Init(map_data);
	m_bgm_path = bgm_path;
}

GameScene::~GameScene()
{
	//BGM��~
	m_bgm->Stop();
	DeleteGO(m_bgm);
	DeleteGO(m_player);
	DeleteGO(m_map);
	g_gameScene = nullptr;
}

bool GameScene::Start()
{
	m_player = NewGO<Player>(0);

	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init(m_bgm_path);
	m_bgm->Play(true);

	//���C�g���������B
	m_light.SetAmbinetLight(CVector3::One);

	return true;
}

void GameScene::Update()
{
	SceneChange();

	if (m_time > 0) {
		m_time--;
	}

	int l_n1 = 0, l_n10 = 0, l_n100 = 0;

	l_n100 = m_time / 100;			//3���ڂ̐���
	l_n10 = (m_time % 100) / 10;	//2���ڂ̐���
	l_n1 = m_time % 10;			    //1���ڂ̐���

	m_timesprite[0].SetTexture(m_texture[l_n100]);
	m_timesprite[1].SetTexture(m_texture[l_n10]);
	m_timesprite[2].SetTexture(m_texture[l_n1]);

	if (GetAsyncKeyState('2') & 0x8000) {
		if (m_killcount < 99) {
			m_killcount++;
		}
	}

	int l_num1 = 0, l_num10 = 0;
	
	l_num10 = (m_killcount % 100) / 10;
	l_num1 = m_killcount % 10;
	
	m_killsprite[0].SetTexture(m_texture[l_num10]);
	m_killsprite[1].SetTexture(m_texture[l_num1]);
}

/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{
}

/*!
*@brief	�`��֐��B
*/
void GameScene::PostRender(CRenderContext& renderContext)
{
	for (int i = 0;i < 3;i++) {
		m_timesprite[i].Draw(renderContext);
	}
	for (int i = 0;i < 2;i++) {
		m_killsprite[i].Draw(renderContext);
	}
}

/*!
*@brief	��ʑJ�ڊ֐��B
*/
void GameScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		//�t�F�[�h�C��
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		//���쒆
		SetActiveFlags(true);
		//�X�^�[�g�{�^������
		if (Pad(0).IsTrigger(enButtonStart))
		{
			//���j���[�֑J��
			m_scenedata = enMenu;

			m_runstat = enFadeOut;

			SetActiveFlags(false);
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			//���U���g�֑J��
			m_scenedata = enResult;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			//��ʐ���
			switch (m_scenedata)
			{
			case enMenu:
				NewGO<MenuScene>(0);
				break;
			case enResult:
				NewGO<ResultScene>(0);
			default:
				break;
			}
			m_runstat = enRun;
			g_gameScene->SetActiveFlag(false);
			
			//���j���[��ʂւ̑J�ڂłȂ�
			if (m_scenedata != enMenu)
			{
				//�������폜�B
				DeleteGO(this);
			}
			return;
		}
		break;
	default:
		break;
	}
}

void GameScene::SetActiveFlags(bool flag)
{
	//�����Ő��������I�u�W�F�N�g�̓���ύX
	m_player->SetActiveFlag(flag);
	if (flag)
	{
		m_bgm->Play(true);
	}
	else
	{
		m_bgm->Stop();
	}
	m_map->SetActiveFlag(flag);
}