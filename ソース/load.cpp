#include "GV.h"

void fast_ini(){
	
}
void load(){
	img[0] = LoadGraph("dat/��b.png");
	LoadDivGraph("dat/run.png", 6, 6, 1, 80, 80, img_run);
	img[1] = LoadGraph("dat/back0.png");
	img[2] = LoadGraph("dat/back1.png");

	color[0] = GetColor(255, 255, 255);//��
	color[1] = GetColor(0, 0, 0);//��
	color[2] = GetColor(255, 0, 0);//��
	color[3] = GetColor(0, 255, 0);//��
	color[4] = GetColor(0, 0, 255);//��
	color[5] = GetColor(255, 255, 0);//���F
	color[6] = GetColor(0, 255, 255);//��
	color[7] = GetColor(255, 0, 255);//��
	color[8] = GetColor(1, 50, 36);//���F
	color[9] = GetColor(62, 179, 112);//��
	color[10] = GetColor(56, 180, 139);//�Ő�

	font[0] = CreateFontToHandle("HGP�޼��E", 15, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[1] = CreateFontToHandle("HGP�޼��E", 40, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[2] = CreateFontToHandle("HGP�޼��E", 150, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[3] = CreateFontToHandle("HGP�޼��E", 80, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[4] = CreateFontToHandle("HGP�޼��E", 28, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	fast_ini();
}