//	  USB-IO2(AKI)���R���g���[
//
//    2013/08/04
//
//	  �R���p�C������ɂ�WDK7���C���X�g�[������C���N���[�h�t�@�C���y��
//  ���C�u�����t�@�C���̃p�X���ݒ肳��Ă���K�v��������
//	  �C���N���[�h�t�@�C���̃p�X�ݒ�́AWDK7�̂ݐݒ肷��ƃC���N���[�h
//   �t�@�C���̌Ăэ��ݗD�揇�ʂ�WDK7��Visual C++�W���p�X�ƂȂ�WDK7��
//   �w�b�_�[�t�@�C������Â��w�b�_�t�@�C�����C���N���[�h����G���[��
//   �����������邽�߁A�D�揇�ʂ�Visual C++�W���p�X��WDK7�ƂȂ�悤�ɂ���
//   �C���N���[�h�p�X�̐ݒ��
//     �ǉ��̃C���N���[�h�f�B���N�g�� $(VCInstallDir)include;C:\WinDDK\7600.16385.1\inc\api 

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


const short unsigned  MyVendorID=0x1352; // �x���_�[ID Km2Net
const short unsigned  MyProductID=0x120; // �v���_�N�gID USB-IO2.0
const short unsigned  MyProductID2=0x121; // �v���_�N�gID USB-IO2.0(AKI)

struct USBIO2_DEV{
	USBIO2_DEV* next;
	TCHAR* name;
	USBIO2_DEV(){
		next=0;
		name=0;
	}
};


//	�f�o�C�X�ꗗ���Ǘ�����N���X

class USBIO2_DEV_LIST{
	USBIO2_DEV* top;
	USBIO2_DEV* end;
public:
	USBIO2_DEV_LIST(){
		top=0;
		end=0;
	}
	int DevEnum(void);	//	USB-IO2(AKI)�f�o�C�X�ꗗ�擾 �ڑ�����Ă������Ԃ�
	USBIO2_DEV* FirstDev(void){	//	1�ڂ̃f�o�C�X�𓾂�
		return top;
	}
	USBIO2_DEV* NextDev(USBIO2_DEV* p){	//	���̃f�o�C�X�𓾂�
		return p->next;
	}
	~USBIO2_DEV_LIST(){	//	�f�o�C�X�ꗗ���J������
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

//	USB-IO2(AKI)���Ǘ�����N���X

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
	HANDLE open(TCHAR *name);	//	�f�o�C�X���J��
	bool InOut(unsigned j1o,unsigned j2o,unsigned* j1,unsigned* j2); // �o�͌���͏�Ԃ��擾
	bool SendRecv(BYTE* send,BYTE* recv);	//	USB-IO2(AKI�j�ƒʐM����N���X
	bool ConfigIn(unsigned* j1io,unsigned* j2io,unsigned* j2pu); // ���o�͐ݒ��ǂݍ���
	bool ConfigSet(unsigned j1io,unsigned j2io,unsigned j2pu); // ���o�͐ݒ����������
	void close(void);	//	�f�o�C�X�����
	~USBIO2(){
		if(hDev)
			close();
	}
};

#endif
