//	  USB-IO2(AKI)をコントロー
//
//    2013/08/04
//
//	  コンパイルするにはWDK7がインストールされインクルードファイル及び
//  ライブラリファイルのパスが設定されている必要性があり
//	  インクルードファイルのパス設定は、WDK7のみ設定するとインクルード
//   ファイルの呼び込み優先順位がWDK7→Visual C++標準パスとなりWDK7の
//   ヘッダーファイルから古いヘッダファイルがインクルードされエラーが
//   多数発生するため、優先順位をVisual C++標準パス→WDK7となるようにする
//   インクルードパスの設定例
//     追加のインクルードディレクトリ $(VCInstallDir)include;C:\WinDDK\7600.16385.1\inc\api 

#ifndef USBIO2_H

#define USBIO2_H

#include <windows.h>
#include <setupapi.h>
#include <stdio.h>
#include <tchar.h>

extern "C" {
	#include "hidsdi.h"
}

#pragma comment(lib,"hid.lib")
#pragma comment(lib,"setupapi.lib")


const short unsigned  MyVendorID=0x1352; // ベンダーID Km2Net
const short unsigned  MyProductID=0x120; // プロダクトID USB-IO2.0
const short unsigned  MyProductID2=0x121; // プロダクトID USB-IO2.0(AKI)

struct USBIO2_DEV{
	USBIO2_DEV* next;
	TCHAR* name;
	USBIO2_DEV(){
		next=0;
		name=0;
	}
};


//	デバイス一覧を管理するクラス

class USBIO2_DEV_LIST{
	USBIO2_DEV* top;
	USBIO2_DEV* end;
public:
	USBIO2_DEV_LIST(){
		top=0;
		end=0;
	}
	int DevEnum(void);	//	USB-IO2(AKI)デバイス一覧取得 接続されている個数を返す
	USBIO2_DEV* FirstDev(void){	//	1個目のデバイスを得る
		return top;
	}
	USBIO2_DEV* NextDev(USBIO2_DEV* p){	//	次のデバイスを得る
		return p->next;
	}
	~USBIO2_DEV_LIST(){	//	デバイス一覧を開放する
		USBIO2_DEV* p=top;
		USBIO2_DEV* t;
		while(p){
			t=p;
			delete [] p->name;
			p=p->next;
			delete t;
		}

	}
};

//	USB-IO2(AKI)を管理するクラス

class USBIO2{
	HANDLE hDev;
	PHIDP_PREPARSED_DATA PreparsedData;
	HIDP_CAPS Capabilities;
	BYTE* writeBuf;
	BYTE* readBuf;
public:
	USBIO2(){
		hDev=0;
	}
	HANDLE open(TCHAR *name);	//	デバイスを開く
	bool InOut(unsigned j1o,unsigned j2o,unsigned* j1,unsigned* j2); // 出力後入力状態を取得
	bool SendRecv(BYTE* send,BYTE* recv);	//	USB-IO2(AKI）と通信するクラス
	bool ConfigIn(unsigned* j1io,unsigned* j2io,unsigned* j2pu); // 入出力設定を読み込む
	bool ConfigSet(unsigned j1io,unsigned j2io,unsigned j2pu); // 入出力設定を書き込む
	void close(void);	//	デバイスを閉じる
	~USBIO2(){
		if(hDev)
			close();
	}
};

#endif
