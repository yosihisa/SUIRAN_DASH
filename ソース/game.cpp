#include "GV.h"
#include "Game.h"

static int pause = 0;

double rang(double ang){
	return (-ang + ang*2 * GetRand(10000)/10000.0);
}

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Game::Initialize(){
	count = 0;
	ch.x = 0;
	ch.y = 420;
	ch.ang = 0.0;
	ch.xv = 5.0;
	ch.yv = 0.0;
	ch.run = 0;
	back.v = 5.0;
	SRand(114514);
	pause = 0;
	if (CheckStateKey(KEY_INPUT_B)!=0&&CheckStateKey(256)!=0)ch.v_MAX = 40.0;
	else ch.v_MAX = 20.0;
	for (int i=0; i<MAX_SUIRAN; i++){
		suiran.x[i] = GetRand(100000);
		suiran.y[i] = 480+GetRand(100);
		suiran.r[i] = 100+GetRand(150);
		suiran.col[i] = color[8+GetRand(2)];
	}
	timer = 60*TIME+3*60;
}

//更新
void Game::Update(){
	if (pause == 0){
		if (CheckStateKey(KEY_INPUT_ESCAPE)==2 ||CheckStateKey(257)==2 || timer<=-60*3){
			pause = 1;
			if (timer<0)mSceneChanger->ChangeScene(eScene_score);
		}
		if (timer<=60*TIME && timer>=0){

			if (ch.y<430){
				ch.yv += 0.8;
			}
			if (count%5==0 && ch.yv>=0)ch.run++;
			ch.run = ch.run%6;

			if (ch.y==420 && ch.xv<=ch.v_MAX)ch.xv += 0.5;
			if (ch.xv>=ch.v_MAX)ch.xv = ch.v_MAX;
			if (ch.y>=420)ch.yv = 0;


			if (ch.y>420)ch.y = 420;

			if (CheckStateKey(KEY_INPUT_SPACE)==1 || CheckStateKey(256)==1){
				ch.yv = -20.0, ch.xv -= 2.0;
				if (ch.xv<=8.0)ch.xv = 8.0;
				ch.run = 0;
			}
			ch.y += ch.yv;
			for (int i = 0; i<MAX_SUIRAN; i++){
				if (pow((ch.x+CH_X)-suiran.x[i], 2.0) + pow((ch.y+CH_Y_H)-suiran.y[i], 2.0) <= pow(suiran.r[i], 2.0)){
					while (pow((ch.x+CH_X)-suiran.x[i], 2.0) + pow((ch.y+CH_Y_H)-suiran.y[i], 2.0) < pow(suiran.r[i], 2.0)){
						ch.y -= 1.0;
					}
				}
				if (pow((ch.x+CH_X_H)-suiran.x[i], 2.0) + pow((ch.y+CH_Y_H)-suiran.y[i], 2.0) <= pow(suiran.r[i]+2, 2.0)){
					ch.xv -= 0.8;
					if (ch.xv<=4.0)ch.xv = 4.0;
				}
			}
			for (int i = 0; i<MAX_SUIRAN; i++){

			}
			ch.x += ch.xv;
		}
		timer--;
		count++;
	}else{
		if (CheckStateKey(KEY_INPUT_ESCAPE)==2	|| CheckStateKey(257)==2 )	pause = 0;
		if (CheckStateKey(KEY_INPUT_SPACE)==1	|| CheckStateKey(256)==1)	mSceneChanger->ChangeScene(eScene_score);
	}
}

//描画
void Game::Draw(){
    BaseScene::Draw();//親クラスの描画メソッドを呼ぶ

	char str[256];
	double t, m;
	DrawGraph(-1*(int)ch.x%960, 0, img[1], TRUE);
	DrawGraph(-1*(int)ch.x%960+960, 0, img[1], TRUE);
	DrawRotaGraph(CH_X, ch.y, 1.0, 0.0, img_run[ch.run], TRUE, FALSE);

	//翠巒描画
	for (int i=0; i<MAX_SUIRAN; i++){
		if (ch.x-(suiran.x[i]+suiran.r[i])<100&&ch.x-(suiran.x[i]-suiran.r[i])>-640){
			DrawCircle(suiran.x[i]-ch.x, suiran.y[i], suiran.r[i], suiran.col[i], TRUE);
		}
	}
	
	DrawGraph(-1*(int)ch.x%960, 450, img[2], TRUE);
	DrawGraph(-1*(int)ch.x%960+960, 450, img[2], TRUE);


	//デバック支援
#ifdef _DEBUG
	sprintf_s(str, "Y軸速度%.3fpx/f X軸速度%.3fpx/f　距離%7d px", ch.yv, ch.xv, ch.x);
	DrawStringToHandle(0, 460, str, color[6], font[0], color[4]);
#endif
	//開始前
	if (timer>60*TIME){
		t = TIME;
		m = 0.0;
		sprintf_s(str, "%d", (timer-(TIME-1)*60)/60);
		if(pause==0)DrawStringToHandle(270, 150, str, color[5], font[2], color[2]);
	}

	//ゲーム中
	if (timer<=60*TIME && timer>=0){
		t = 1.0*timer/60;
		m = 1.0*ch.x/PX_M;
	}

	//終了
	if (timer<0 && pause==0){
		t = 0.0;
		m = 1.0*ch.x/PX_M;
		DrawStringToHandle(35, 150, "そこまで", color[5], font[2], color[2]);
	}

	//終了確認
	if (pause == 1 && timer>=0){
		DrawStringToHandle(80, 150, "終了するの？", color[6], font[3], color[4]);
		DrawStringToHandle(80, 240, "いいえ（ESC）", color[0], font[4], color[1]);
		DrawStringToHandle(360, 240, "はい（SPACE）", color[0], font[4], color[1]);

	}
	//残り時間　距離
	sprintf_s(str, "残り%.1f秒 距離%.1fｍ", t, m);
	if (pause == 0 && timer>=0)DrawStringToHandle(150, 0, str, color[0], font[1], color[1]);
}
