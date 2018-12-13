#include "GV.h"
#include <windows.h>
#include <locale.h>
#include <string.h>
#include <tchar.h>
#include "usbio2.h"

USBIO2_DEV_LIST list;
USBIO2_DEV* p;
USBIO2 usb;
int max;
static unsigned USB_j1, USB_j2;

int wait = 0;
int n;
//int jn = 0;
static unsigned out[2];

int key_ini(/*int argc, TCHAR** argv*/){

	max = list.DevEnum();
	if (max==0){
		return 1;
	}
	p = list.FirstDev();
	if (usb.open(p->name)==0){
		return 1;
	}
	return 0;
	
}

void key_end(){
	usb.close();
}


unsigned int stateKey[258];

int GetHitKeyStateAll_2(int f){
    char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
	for (int i = 0; i<256; i++){
		if (GetHitKeyStateAll_Key[i]==1)stateKey[i]++;
		else                            stateKey[i] = 0;
	}
	if (f==0){
		if (USB_j2!=15)out[0] = 1;
		else out[0] = 0;
		usb.InOut(out[0], out[1], &USB_j1, &USB_j2);
		if (USB_j2==11||USB_j2==3)stateKey[257]++;
		else stateKey[257] = 0;
		if (USB_j2==7)stateKey[256]++;
		else stateKey[256] = 0;
	}
    return 0;
}

int CheckStateKey(unsigned int Handle){
	return stateKey[Handle];
}
