/*!
 *@brief	main.cpp
 */
#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver2D.h"
#include "SpaceMap.h"
#include "ClearState.h"
#include "ShipState.h"

 //#define USESPECSETTING 	//``�L���Œ�X�y�b�N�����̃Z�b�e�B���O
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand((unsigned)time(NULL));
#if defined (USESPECSETTING)
	//tkEngine2�̏������p�����[�^��ݒ肷��B
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 640;
	initParam.frameBufferHeight = 360;
	//initParam.screenWidth2D = 1280;
	initParam.screenWidth2D = 640;
	//initParam.screenHeight2D = 640;
	initParam.screenHeight2D = 360;
	//�e�̐ݒ�B
	initParam.graphicsConfing.shadowRenderConfig.isEnable = false;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;
	//�A���`
	initParam.graphicsConfing.aaConfig.isEnable = false;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = false;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
#else
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	//�e�̐ݒ�B
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;
	//�A���`
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
#endif
	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);

	//�G���W�����������B
	if (Engine().Init(initParam) == true) {
		NewGO<Fade>(1, "Fade");
		NewGO<Title>(0,nullptr);
		NewGO<ClearState>(0, "ClearState");
		NewGO<ShipState>(0, "ShipState");
		//�Q�[�����[�v�����s�B
		Engine().RunGameLoop();
	}
	//�G���W���̏I�������B
	Engine().Final();
	return 0;
}

