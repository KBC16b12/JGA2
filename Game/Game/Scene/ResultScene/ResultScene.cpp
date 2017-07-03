#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../ResultScene/ResultScene.h"
#include "../TitleScene/TitleScene.h"
#include "../../Player/Player.h"
#include"../GameScene/GameScene.h"

ResultScene::ResultScene()
{
	m_rcount = 0;
	m_intervalTime = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		char cp[60];
		sprintf(cp, "Assets/sprite/raking/%d.png", i);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0; i < 10; i++)
	{
		char cp[60];
		sprintf(cp, "Assets/sprite/KillScoreNum/%d.png", i);
		m_numTexture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0; i < 4; i++) {
		m_sprite[i].Init(m_texture[i]);
		m_sprite[i].SetPosition({ -210.0f,173.0f - i * 130});
		m_sprite[i].SetSize({ 100.0f,100.0f });
	}
	//m_SampleTex = TextureResources().LoadEx("Assets/sprite/Result.png");
	m_SampleTex = TextureResources().LoadEx("Assets/sprite/result.png");
	m_Sample.Init(m_SampleTex);
	m_Sample.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	/*CTexture *l_backTexture = TextureResources().Load("Assets/sprite/result.png");
	m_backGround.Init(l_backTexture);
	m_backGround.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	CVector2 l_position = { -210.0f, 173.0f };
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		char l_filePath[60];
		sprintf(l_filePath, "Assets/sprite/raking/%d.png", i);
		CTexture *l_rankTexture = TextureResources().Load(l_filePath);
		m_rankSprite[i].Init(l_rankTexture);
		CVector2 l_size = { 100.0f, 100.0f };
		m_rankSprite[i].SetSize(l_size);
		m_rankSprite[i].SetPosition(l_position);
		l_position.y -= m_heightInterval;

	}*/

	m_state = 3;
	m_positionLimit = 0.0f;
}

ResultScene::~ResultScene()
{
	//BGMí‚é~
	m_bgm->Stop();
	DeleteGO(m_bgm);
}

bool ResultScene::Start()
{
	m_bgm = NewGO<CSoundSource>(PRIORITY1);
	m_bgm->Init("Assets/sound/Result1.wav");
	m_bgm->Play(true);
	Player* playerArray[4];
	for (int i = 0; i < 4; i++)
	{
		pNum[i] = i;
	}

	//ç~èáÇ…ï¿Ç—ë÷Ç¶
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

	/*CTexture* l_numTexture[DECI];
	for (int i = 0; i < DECI; i++)
	{
		char l_filePath[60];
		sprintf(l_filePath, "Assets/sprite/KillScoreNum/%d.png", i);
		l_numTexture[i] = TextureResources().LoadEx(l_filePath);
	}
	CVector2 l_playerSize = { 300.0f, 100.0f };
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		char l_filePath[60];
		sprintf(l_filePath, "Assets/sprite//playerlist/0%d.png", pNum[i]);
		CTexture *l_playerTexture = TextureResources().Load(l_filePath);
		m_playerSprite[i].Init(l_playerTexture);
		float l_height = m_rankSprite[i].GetPosition().y;
		CVector2 l_playerPos = { 0.0f, l_height - 20.0f};
		m_playerSprite[i].SetPosition(l_playerPos);
		m_playerSprite[i].SetSize(l_playerSize);
		int l_killScore[KILLCOUNT_DIGIT];
		l_killScore[0] = pKill[pNum[i]] / 10 % 10;
		l_killScore[1] = pKill[pNum[i]] % 10;
		CVector2 l_killScorePos = { 200.0f, l_height };
		for (int j = 0; j < 2; j++)
		{
			m_killScore[i][j].Init(l_numTexture[l_killScore[j]]);
			m_killScore[i][j].SetPosition(l_killScorePos);
			m_killScore[i][j].SetSize({ 60.0f, 70.0f });
			l_killScorePos.x += 50.0f;
		}
	}*/

	for (int i = 0; i < 4; i++)
	{
		char cp[60];
		sprintf(cp, "Assets/sprite/playerlist/%d.png", pNum[i]);
		m_texture[i] = TextureResources().LoadEx(cp);
	}
	for (int i = 0; i < 4; i++) {
		m_sprite2[i].Init(m_texture[i]);
		m_sprite2[i].SetPosition({ 810.0f,158.0f - i * 130 });
		m_sprite2[i].SetSize({ 300.0f,100.0f });
		int l_killScore[KILLCOUNT_DIGIT];
		l_killScore[0] = pKill[pNum[i]] / 10 % 10;
		l_killScore[1] = pKill[pNum[i]] % 10;
		CVector2 l_killScorePos = { 920.0f, 158.0f - i * 130 };
		for (int j = 0; j < 2; j++)
		{
			m_killScore[i][j].Init(m_numTexture[l_killScore[j]]);
			m_killScore[i][j].SetPosition(l_killScorePos);
			m_killScore[i][j].SetSize({ 60.0f, 70.0f });
			l_killScorePos.x += 50.0f;
		}
	}

	return true;
}

void ResultScene::Update()
{
	if (0.0f < m_intervalTime)
	{
		m_intervalTime -= GameTime().GetFrameDeltaTime();
		return;
	}
	float l_moveSpeed = 35.0f;
	float _x;
	switch (m_state)
	{
	case 3:
		for (int i = 0; i < 2; i++)
		{
			_x = m_killScore[3][i].GetPosition().x - l_moveSpeed;
			m_killScore[3][i].SetPosition({ _x, m_killScore[3][i].GetPosition().y });
		}
		_x = m_sprite2[3].GetPosition().x - l_moveSpeed;
		m_sprite2[3].SetPosition({ _x, m_sprite2[3].GetPosition().y });
		break;
	case 2:
		for (int i = 0; i < 2; i++)
		{
			_x = m_killScore[2][i].GetPosition().x - l_moveSpeed;
			m_killScore[2][i].SetPosition({ _x, m_killScore[2][i].GetPosition().y });
		}
		_x = m_sprite2[2].GetPosition().x - l_moveSpeed;
		m_sprite2[2].SetPosition({ _x, m_sprite2[2].GetPosition().y });
		break;
	case 1:
		for (int i = 0; i < 2; i++)
		{
			_x = m_killScore[1][i].GetPosition().x - l_moveSpeed;
			m_killScore[1][i].SetPosition({ _x, m_killScore[1][i].GetPosition().y });
			_x = m_killScore[0][i].GetPosition().x - l_moveSpeed;
			m_killScore[0][i].SetPosition({ _x, m_killScore[0][i].GetPosition().y });
		}
		_x = m_sprite2[1].GetPosition().x - l_moveSpeed;
		m_sprite2[1].SetPosition({ _x, m_sprite2[1].GetPosition().y });
		_x = m_sprite2[0].GetPosition().x - l_moveSpeed;
		m_sprite2[0].SetPosition({ _x, m_sprite2[0].GetPosition().y });
		break;
	case 0:
		break;
	}
	if (750.0f <= m_positionLimit)
	{
		if (0 < m_state)
		{
			m_state--;
			m_positionLimit = 0.0f;
			m_intervalTime = 2.5f;
		}
	}
	else
	{
		m_positionLimit += l_moveSpeed;
	}
	SceneChange();
}

void ResultScene::PostRender(CRenderContext& renderContext)
{
	Draw(renderContext);
}

void ResultScene::PostRender(CRenderContext& renderContext, int cameraNum)
{
	Draw(renderContext);
}

void ResultScene::Draw(CRenderContext& renderContext)
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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_killScore[i][j].Draw(renderContext);
		}
	}
	/*m_backGround.Draw(renderContext);
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_rankSprite[i].Draw(renderContext);
		m_playerSprite[i].Draw(renderContext);
		for (int j = 0; j < KILLCOUNT_DIGIT; j++)
		{
			m_killScore[i][j].Draw(renderContext);
		}
	}*/
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
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			if (Pad(i).IsTrigger(enButtonStart) && m_state == 0)
			{
				m_scenedata = enTitle;

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
			case enTitle:
				NewGO<TitleScene>(PRIORITY1);
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