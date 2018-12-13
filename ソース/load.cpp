#include "GV.h"

void fast_ini(){
	
}
void load(){
	img[0] = LoadGraph("dat/栰廱.png");
	LoadDivGraph("dat/run.png", 6, 6, 1, 80, 80, img_run);
	img[1] = LoadGraph("dat/back0.png");
	img[2] = LoadGraph("dat/back1.png");

	color[0] = GetColor(255, 255, 255);//敀
	color[1] = GetColor(0, 0, 0);//崟
	color[2] = GetColor(255, 0, 0);//愒
	color[3] = GetColor(0, 255, 0);//椢
	color[4] = GetColor(0, 0, 255);//惵
	color[5] = GetColor(255, 255, 0);//墿怓
	color[6] = GetColor(0, 255, 255);//惵椢
	color[7] = GetColor(255, 0, 255);//巼
	color[8] = GetColor(1, 50, 36);//悏怓
	color[9] = GetColor(62, 179, 112);//悏
	color[10] = GetColor(56, 180, 139);//闩悏

	font[0] = CreateFontToHandle("HGP恨集窫", 15, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[1] = CreateFontToHandle("HGP恨集窫", 40, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[2] = CreateFontToHandle("HGP恨集窫", 150, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[3] = CreateFontToHandle("HGP恨集窫", 80, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	font[4] = CreateFontToHandle("HGP恨集窫", 28, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	fast_ini();
}