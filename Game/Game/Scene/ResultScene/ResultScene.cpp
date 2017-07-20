#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../ResultScene/ResultScene.h"
#include "../TitleScene/TitleScene.h"
#include "../../Player/Player.h"
#include"../GameScene/GameScene.h"

ResultScene::ResultScene()
{
	m_widthInterval = 90.0f;
	float l_heightInterval = 130.0f;
	m_rcount = 0;
	m_intervalTime = 1.0f;
	m_positionLimit = 0.0f;
	CTexture *l_backTexture = TextureResources().Load("Assets/sprite/result.png");
	m_backGround.Init(l_backTexture);
	m_backGround.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
	CVector2 l_position = { 710.0f, 123.0f };
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		char l_filePath[60];
		sprintf(l_filePath, "Assets/sprite/raking/%d.png", i);
		CTexture *l_rankTexture = TextureResources().Load(l_filePath);
		m_rankSprite[i].Init(l_rankTexture);
		CVector2 l_size = { 100.0f, 100.0f };
		m_rankSprite[i].SetPivot({ 0.0f, 0.0f });
		m_rankSprite[i].SetSize(l_size);
		m_rankSprite[i].SetPosition(l_position);
		l_position.y -= l_heightInterval;
	}

	m_state = 3;
	m_spritePosition = 0.0f;
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

	CTexture* l_numTexture[DECI];
	for (int i = 0; i < DECI; i++)
	{
		char l_filePath[60];
		sprintf(l_filePath, "Assets/sprite/KillScoreNum/%d.png", i);
		l_numTexture[i] = TextureResources().LoadEx(l_filePath);
	}
	CVector2 l_playerSize = { 420.0f, 140.0f };
	float l_heightInterval = 35.0f;
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		char l_filePath[60];
		sprintf(l_filePath, "Assets/sprite//playerlist/0%d.png", pNum[i]);
		CTexture *l_playerTexture = TextureResources().Load(l_filePath);
		m_playerSprite[i].Init(l_playerTexture);
		CVector2 l_playerPos = m_rankSprite[i].GetPosition();
		l_playerPos.y -= l_heightInterval;
		l_heightInterval *= 0.8f;
		l_playerPos.x += 120.0f;
		m_playerSprite[i].SetPivot({ 0.0f, 0.0f });
		m_playerSprite[i].SetPosition(l_playerPos);
		m_playerSprite[i].SetSize(l_playerSize);
		l_playerSize.Scale(0.85f);
		int l_killScore[KILLCOUNT_DIGIT];
		l_killScore[0] = pKill[pNum[i]] / 10 % 10;
		l_killScore[1] = pKill[pNum[i]] % 10;
		CVector2 l_killScorePos = l_playerPos;
		l_killScorePos.x += l_playerSize.x + 30.0f;
		l_killScorePos.y += 13.0f;
		for (int j = 0; j < 2; j++)
		{
			m_killScore[i][j].Init(l_numTexture[l_killScore[j]]);
			m_killScore[i][j].SetPivot({ 0.0f, 0.0f });
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
	case 2:
	case 1:
	case 0:
		for (int i = 0; i < 2; i++)
		{
			_x = m_killScore[m_state][i].GetPosition().x - l_moveSpeed;
			m_killScore[m_state][i].SetPosition({ _x, m_killScore[m_state][i].GetPosition().y });
		}
		_x = m_playerSprite[m_state].GetPosition().x - l_moveSpeed;
		m_playerSprite[m_state].SetPosition({ _x, m_playerSprite[m_state].GetPosition().y });
		_x = m_rankSprite[m_state].GetPosition().x - l_moveSpeed;
		m_rankSprite[m_state].SetPosition({ _x, m_rankSprite[m_state].GetPosition().y });
		break;
	default:
		break;
	}
	m_positionLimit = m_playerSprite[m_state].GetSize().x;
	if (m_positionLimit + 530.0f <= m_spritePosition)
	{
		if (0 <= m_state)
		{
			l_moveSpeed = m_positionLimit + 430.0f - m_spritePosition;
			for (int i = 0; i < 2; i++)
			{
				_x = m_killScore[m_state][i].GetPosition().x - l_moveSpeed;
				m_killScore[m_state][i].SetPosition({ _x, m_killScore[m_state][i].GetPosition().y });
			}
			_x = m_playerSprite[m_state].GetPosition().x - l_moveSpeed;
			m_playerSprite[m_state].SetPosition({ _x, m_playerSprite[m_state].GetPosition().y });
			_x = m_rankSprite[m_state].GetPosition().x - l_moveSpeed;
			m_rankSprite[m_state].SetPosition({ _x, m_rankSprite[m_state].GetPosition().y });
			m_state--;
			m_spritePosition = 0.0f;
			m_intervalTime = 2.0f;
		}
	}
	else
	{
		m_spritePosition += l_moveSpeed;
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
	m_backGround.Draw(renderContext);
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_rankSprite[i].Draw(renderContext);
		m_playerSprite[i].Draw(renderContext);
		for (int j = 0; j < KILLCOUNT_DIGIT; j++)
		{
			m_killScore[i][j].Draw(renderContext);
		}
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
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			if (Pad(i).IsTrigger(enButtonStart) && m_state < 0)
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