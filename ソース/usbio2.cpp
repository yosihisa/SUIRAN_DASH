#include "usbio2.h"

//	USB-IO2(AKI)�f�o�C�X�ꗗ�擾 �ڑ�����Ă������Ԃ�

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
	HidD_GetHidGuid(&hidGuid);	//HID�f�o�C�X�̎��ʎq�̎擾
	hDevInfo=SetupDiGetClassDevs(&hidGuid,0,0,DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	// �f�o�C�X���Z�b�g���擾
	if(hDevInfo==0)	//	�f�o�C�X���Z�b�g���擾�ł��Ȃ������ꍇ
		return 0;
	Data.cbSize=sizeof(Data);

	while( SetupDiEnumDeviceInterfaces(hDevInfo,0,&hidGuid,MemberIndex,&Data)){	// �f�o�C�X�C���^�[�t�F�C�X�̎擾
		SetupDiGetDeviceInterfaceDetail(hDevInfo,&Data, 0 ,0,&DetailDataSize , 0); // �f�o�C�X�C���^�[�t�F�C�X�Ɋւ���ڍ׏��̃o�b�t�@�T�C�Y�̎擾
		DetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)new BYTE[DetailDataSize ]; //�@�ڍ׏��̃o�b�t�@���m��
		DetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
		RequiredSize=0;
		if( SetupDiGetInterfaceDeviceDetail( hDevInfo, &Data, DetailData,DetailDataSize,&RequiredSize,0)){  // �f�o�C�X�C���^�[�t�F�C�X�Ɋւ���ڍ׏��̎擾
			//	�f�o�C�X���J���n���h���̎擾
			hDev=CreateFile( DetailData->DevicePath , GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL );
			if(hDev != INVALID_HANDLE_VALUE){
				Attributes.Size=sizeof(Attributes);	//	�x���_�[ID�@�v���_�N�gID �o�[�W�����ԍ��̎擾
				if(HidD_GetAttributes(hDev,&Attributes)){
					if(Attributes.VendorID==MyVendorID && (Attributes.ProductID==MyProductID || Attributes.ProductID==MyProductID2)){	// USB-IO�����������ꍇ
						USBIO2_DEV* p=new USBIO2_DEV;
						p->name=_tcsdup(DetailData->DevicePath);
						CloseHandle( hDev);	//	�f�o�C�X�����
						++max;
						if(top){
							end->next=p;
							end=p;
						}else
							top=end=p;
					}else
						hDev=0;
				}else{
					CloseHandle( hDev);	//	�f�o�C�X�����
					hDev=0;
				}
			}else
				hDev=0;
		}else
			hDev=0;
		delete [] DetailData; //�@�ڍ׏��̃o�b�t�@�����
		MemberIndex++;
		Data.cbSize=sizeof(Data);
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);	//	�f�o�C�X���Z�b�g�����
	return max;
}

//	USB-IO2(AKI�j�ƒʐM����N���X

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

// �o�͌���͏�Ԃ��擾

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

//  ���o�͐ݒ��ǂݍ���

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

// ���o�͐ݒ����������

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

//	�f�o�C�X���J��
//	�J���Ȃ��ꍇ��0��Ԃ�

HANDLE USBIO2::open(TCHAR* name){
	//	�f�o�C�X���J���n���h���̎擾
	hDev=CreateFile( name , GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,OPEN_EXISTING, 0, NULL );
	if(hDev != INVALID_HANDLE_VALUE){
		HidD_GetPreparsedData(hDev, &PreparsedData);
		HidP_GetCaps(PreparsedData, &Capabilities);
		writeBuf=new BYTE[Capabilities.OutputReportByteLength];	//	���C�g�o�b�t�@�̊m��
		readBuf=new BYTE[Capabilities.InputReportByteLength];	//	���[�h�o�b�t�@�̊m��
		return hDev;
	}
	return hDev=0;
}

//	�f�o�C�X�����

void USBIO2::close(void){
	if(hDev){
		CloseHandle(hDev);
		delete [] writeBuf;
		delete [] readBuf;
		hDev=0;
	}
}
