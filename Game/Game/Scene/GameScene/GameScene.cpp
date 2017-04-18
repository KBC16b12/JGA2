#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameScene/GameScene.h"
#include "../MenuScene/MenuScene.h"
#include "../ResultScene/ResultScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"
#include "../../Map/Map.h"
#include "../../Camera/GameCamera.h"

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
	m_map = NewGO<Map>(PRIORITY1);
}

void GameScene::Init(std::vector<SMapInfo> map_data, char* bgm_path)
{
	m_map->Init(map_data);
	m_bgm_path = bgm_path;
}

GameScene::~GameScene()
{
	//BGM停止
	m_bgm->Stop();
	DeleteGO(m_bgm);
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		DeleteGO(m_player[i]);
	}
	DeleteGO(m_map);
	g_gameScene = nullptr;
}

bool GameScene::Start()
{
	int l_half_w = Engine().GetScreenWidth() / 2;
	int l_half_h = Engine().GetScreenHeight() / 2;
	g_gameCamera[0]->SetViewPort(0, 0, l_half_w, l_half_h, 0);
	g_gameCamera[1]->SetViewPort(l_half_w, 0, l_half_w, l_half_h, 1);
	g_gameCamera[2]->SetViewPort(0, l_half_h, l_half_w, l_half_h, 2);
	g_gameCamera[3]->SetViewPort(l_half_w, l_half_h, l_half_w, l_half_h, 3);

	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i] = NewGO<Player>(PRIORITY1);
		m_player[i]->SetPlayerNum(g_gameCamera[i]->GetCameraNum());
	}

	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init(m_bgm_path);
	//m_bgm->Play(true);

	//ライトを初期化。
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

	l_n100 = m_time / 100;			//3桁目の数字
	l_n10 = (m_time % 100) / 10;	//2桁目の数字
	l_n1 = m_time % 10;			    //1桁目の数字

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
*@brief	描画関数。
*/
void GameScene::Render(CRenderContext& renderContext)
{
}

/*!
*@brief	描画関数。
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
*@brief	画面遷移関数。
*/
void GameScene::SceneChange()
{
	switch (m_runstat)
	{
	case enFadeIn:
		//フェードイン
		if (!g_Fade->IsExecute())
		{
			g_Fade->StartFadeIn();
			m_runstat = enRun;
		}
		break;
	case enRun:
		//動作中
		SetActiveFlags(true);
		//スタートボタン押下
		if (Pad(0).IsTrigger(enButtonStart))
		{
			//メニューへ遷移
			m_scenedata = enMenu;

			m_runstat = enFadeOut;

			SetActiveFlags(false);
			return;
		}
		if (Pad(0).IsTrigger(enButtonA))
		{
			//リザルトへ遷移
			m_scenedata = enResult;

			m_runstat = enFadeOut;

			g_Fade->StartFadeOut();
			return;
		}
		break;
	case enFadeOut:
		if (!g_Fade->IsExecute())
		{
			//画面生成
			switch (m_scenedata)
			{
			case enMenu:
				NewGO<MenuScene>(PRIORITY1);
				break;
			case enResult:
				NewGO<ResultScene>(PRIORITY1);
			default:
				break;
			}
			m_runstat = enRun;
			g_gameScene->SetActiveFlag(false);
			
			//メニュー画面への遷移でない
			if (m_scenedata != enMenu)
			{
				//自分を削除。
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
	//ここで生成したオブジェクトの動作変更
	for (int i = 0;i < PLAYER_NUM;i++)
	{
		m_player[i]->SetActiveFlag(flag);
	}
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