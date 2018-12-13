#define GLOBAL_INSTANCE 
#include "GV.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	int usb_f;

	SetMainWindowText("翠巒ダッシュ");

    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

    SceneMgr sceneMgr;
    sceneMgr.Initialize();

	load();
	usb_f = key_ini();

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){//画面更新 & メッセージ処理 & 画面消去

		GetHitKeyStateAll_2(usb_f);
        sceneMgr.Update();  //更新
        sceneMgr.Draw();    //描画

    }

	
    sceneMgr.Finalize();

	if (usb_f==0)key_end();

    DxLib_End(); // DXライブラリ終了処理
    return 0;
}