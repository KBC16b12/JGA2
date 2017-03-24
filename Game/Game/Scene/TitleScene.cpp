#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "JoinScene.h"
//#include "Scene/RankingScene.h"

TitleScene::TitleScene()
{
	//�o�[�̏�����
	m_TitleTex = TextureResources().LoadEx("Assets/sprite/Title.png");
	m_Title.Init(m_TitleTex);
	m_Title.SetSize({ (float)Engine().GetScreenWidth(),(float)Engine().GetScreenHeight() });
}

TitleScene::~TitleScene()
{
	DeleteGO(m_bgm);
}

bool TitleScene::Start()
{
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
*@brief	��ʑJ�ڊ֐��B
*/
void TitleScene::SceneChange()
{
	if (Pad(0).IsPress(enButtonA)) {
		//�Q�[����ʂɑJ�ڂ���B
		g_gameScene = NewGO<GameScene>(0);
		DeleteGO(this);
		return;
	}
	if (Pad(0).IsPress(enButtonB)) {
		//�ΐ푊���W��ʂɑJ�ڂ���B
		NewGO<JoinScene>(0);
		DeleteGO(this);
		return;
	}
	if (Pad(0).IsPress(enButtonX)) {
		//�����L���O��ʂɑJ�ڂ���B
		//NewGO<RankingScene>(0);
		DeleteGO(this);
		return;
	}
}