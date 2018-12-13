#include "usbio2.h"

//	USB-IO2(AKI)デバイス一覧取得 接続されている個数を返す

int USBIO2_DEV_LIST::DevEnum(void){
	GUID hidGuid;
	HDEVINFO hDevInfo;
	DWORD MemberIndex=0;
	SP_DEVICE_INTERFACE_DATA Data;
	DWORD DetailDataSize;
	DWORD RequiredSize;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DetailData;
	HIDD_ATTRIBUTES Attributes;
	HANDLE hDev;

	int max=0;
	HidD_GetHidGuid(&hidGuid);	//HIDデバイスの識別子の取得
	hDevInfo=SetupDiGetClassDevs(&hidGuid,0,0,DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	// デバイス情報セットを取得
	if(hDevInfo==0)	//	デバイス情報セットが取得できなかった場合
		return 0;
	Data.cbSize=sizeof(Data);

	while( SetupDiEnumDeviceInterfaces(hDevInfo,0,&hidGuid,MemberIndex,&Data)){	// デバイスインターフェイスの取得
		SetupDiGetDeviceInterfaceDetail(hDevInfo,&Data, 0 ,0,&DetailDataSize , 0); // デバイスインターフェイスに関する詳細情報のバッファサイズの取得
		DetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)new BYTE[DetailDataSize ]; //　詳細情報のバッファを確保
		DetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		RequiredSize=0;
		if( SetupDiGetInterfaceDeviceDetail( hDevInfo, &Data, DetailData,DetailDataSize,&RequiredSize,0)){  // デバイスインターフェイスに関する詳細情報の取得
			//	デバイスを開きハンドルの取得
			hDev=CreateFile( DetailData->DevicePath , GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL );
			if(hDev != INVALID_HANDLE_VALUE){
				Attributes.Size=sizeof(Attributes);	//	ベンダーID　プロダクトID バージョン番号の取得
				if(HidD_GetAttributes(hDev,&Attributes)){
					if(Attributes.VendorID==MyVendorID && (Attributes.ProductID==MyProductID || Attributes.ProductID==MyProductID2)){	// USB-IOが見つかった場合
						USBIO2_DEV* p=new USBIO2_DEV;
						p->name=_tcsdup(DetailData->DevicePath);
						CloseHandle( hDev);	//	デバイスを閉じる
						++max;
						if(top){
							end->next=p;
							end=p;
						}else
							top=end=p;
					}else
						hDev=0;
				}else{
					CloseHandle( hDev);	//	デバイスを閉じる
					hDev=0;
				}
			}else
				hDev=0;
		}else
			hDev=0;
		delete [] DetailData; //　詳細情報のバッファを解放
		MemberIndex++;
		Data.cbSize=sizeof(Data);
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);	//	デバイス情報セットを解放
	return max;
}

//	USB-IO2(AKI）と通信するクラス

bool USBIO2::SendRecv(BYTE* send,BYTE* recv){
	int i;
	DWORD writeN,readN;

	
	writeBuf[0]=0;

	for(i=0;i<64;i++){
		writeBuf[i+1]=send[i];
	}
	WriteFile(hDev,writeBuf,Capabilities.OutputReportByteLength,&writeN,0);
	if(writeN != Capabilities.OutputReportByteLength){
		return false;
	}
	do{
		ReadFile(hDev,readBuf,Capabilities.InputReportByteLength,&readN,0);
	}while(writeBuf[64]!=readBuf[64]);
	if(readN != Capabilities.InputReportByteLength){
		return false;
	}

	for(i=0;i<64;i++){
		recv[i]=readBuf[i+1];
	}
	return true;
}

// 出力後入力状態を取得

bool USBIO2::InOut(unsigned j1o,unsigned j2o,unsigned* j1in,unsigned* j2in){
	BYTE send[64];
	BYTE recv[64];

	send[0]=0x20;
	send[1]=1;
	send[2]=j1o;
	send[3]=2;
	send[4]=j2o;
	send[63]=0;
	bool f=SendRecv(send,recv);
	*j1in=recv[1];
	*j2in=recv[2];
	return f;
}

//  入出力設定を読み込む

bool USBIO2::ConfigIn(unsigned* j1io,unsigned* j2io,unsigned* j2pu){
	BYTE send[64];
	BYTE recv[64];

	send[0]=0xf8;
	send[63]=0;
	bool f=SendRecv(send,recv);
	*j1io=recv[5];
	*j2io=recv[6];
	*j2pu=recv[2];
	return f;
}

// 入出力設定を書き込む

bool USBIO2::ConfigSet(unsigned j1io,unsigned j2io,unsigned j2pu){
	BYTE send[64];
	BYTE recv[64];

	send[0]=0xf9;
	send[1]=0;
	send[2]=j2pu;
	send[3]=0;
	send[4]=0;
	send[5]=j1io;
	send[6]=j2io;
	send[63]=0;

	bool f=SendRecv(send,recv);
	close();
	return f;
}

//	デバイスを開く
//	開けない場合は0を返す

HANDLE USBIO2::open(TCHAR* name){
	//	デバイスを開きハンドルの取得
	hDev=CreateFile( name , GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL );
	if(hDev != INVALID_HANDLE_VALUE){
		HidD_GetPreparsedData(hDev, &PreparsedData);
		HidP_GetCaps(PreparsedData, &Capabilities);
		writeBuf=new BYTE[Capabilities.OutputReportByteLength];	//	ライトバッファの確保
		readBuf=new BYTE[Capabilities.InputReportByteLength];	//	リードバッファの確保
		return hDev;
	}
	return hDev=0;
}

//	デバイスを閉じる

void USBIO2::close(void){
	if(hDev){
		CloseHandle(hDev);
		delete [] writeBuf;
		delete [] readBuf;
		hDev=0;
	}
}
