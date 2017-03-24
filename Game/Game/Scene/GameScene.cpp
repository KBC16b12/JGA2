#include "stdafx.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Bar/Bar.h"
#include "Player/Player.h"

GameScene* g_gameScene = NULL;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	DeleteGO(m_bgm);
	DeleteGO(m_player);
}

bool GameScene::Start()
{
	m_player = NewGO<Player>(0);

	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init("Assets/sound/GameBGM.wav");
	m_bgm->Play(true);

	//�J�������������B
	m_camera.SetPosition({ 0.0f, 0.0f, -700.0f });
	m_camera.SetNear(400.0f);
	m_camera.SetFar(1000.0f);
	m_camera.Update();

	//�^�C�}�[
	m_texture = TextureResources().LoadEx("Assets/sprite/NewNumber/9.png", 0);
	m_sprite.Init(m_texture);
	m_sprite.SetPosition({ 5.0f,0.0f,0.0f });
	
	//���C�g���������B
	m_light.SetAmbinetLight(CVector3::One);

	return true;
}

void GameScene::Update()
{
	SceneChange();
}

/*!
*@brief	�`��֐��B
*/
void GameScene::Render(CRenderContext& renderContext)
{
	m_sprite.Draw(renderContext);
}

/*!
*@brief	��ʑJ�ڊ֐��B
*/
void GameScene::SceneChange()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		//�^�C�g����ʂɑJ�ڂ���B
		NewGO<TitleScene>(0);
		DeleteGO(this);
		return;
	}
}
