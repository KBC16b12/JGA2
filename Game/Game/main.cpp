#include "stdafx.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/Fade/Fade.h"
#include "Camera/GameCamera.h"

CLight	g_defaultLight;	//デフォルトライト。

CRandom g_random;
/*!
 * @brief	tkEngineの初期化。
 */
void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;
	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.Init();
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfig.shadowRenderConfig.numShadowMap = 3;
	
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = false;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	//DOF
	initParam.graphicsConfig.dofConfig.isEnable = false;
	//AA
	initParam.graphicsConfig.aaConfig.isEnable = false;
	//乱数初期化。
	g_random.Init((unsigned long)time(NULL));

	//デフォルトライトの初期化。
	g_defaultLight.SetDiffuseLightDirection(0, { 0.707f, 0.0f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(1, { -0.707f, 0.0f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(2, { 0.0f, 0.707f, -0.707f });
	g_defaultLight.SetDiffuseLightDirection(3, { 0.0f, -0.707f, -0.707f });

	g_defaultLight.SetDiffuseLightColor(0, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(1, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(2, { 0.3f, 0.3f, 0.3f, 1.0f });
	g_defaultLight.SetDiffuseLightColor(3, { 0.2f, 0.2f, 0.2f, 1.0f });
	g_defaultLight.SetAmbinetLight({ 0.3f, 0.3f, 0.3f });

	Engine().Init(initParam);	//初期化。
	
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(40.0f);
	
}

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
)
{
	//tkEngineの初期化。
	InitTkEngine(hInst);

	//g_Fade = NewGO<Fade>(1);

	//g_gameCamera = NewGO<GameCamera>(0);

	//タイトルシーンの作成。
	//NewGO<TitleScene>(0)->Init(enRun);
	
	Engine().RunGameLoop();		//ゲームループを実行。

	return 0;
}