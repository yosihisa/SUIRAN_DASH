#define GLOBAL_INSTANCE 
#include "GV.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	int usb_f;

	SetMainWindowText("���ۃ_�b�V��");

    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

    SceneMgr sceneMgr;
    sceneMgr.Initialize();

	load();
	usb_f = key_ini();

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		GetHitKeyStateAll_2(usb_f);
        sceneMgr.Update();  //�X�V
        sceneMgr.Draw();    //�`��

    }

	
    sceneMgr.Finalize();

	if (usb_f==0)key_end();

    DxLib_End(); // DX���C�u�����I������
    return 0;
}