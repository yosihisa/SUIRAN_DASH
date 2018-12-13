#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif
#include "DxLib.h"
#include "math.h"


//----------------------------------定数定義------------------------------------------
#define PI 3.14152653589793238462
#define PI2 PI*2
#define CH_Y_H 35//自機の画像の高さ÷2
#define CH_X_H 35
#define CH_X 100 //描画位置 x座標
#define MAX_SUIRAN 300 //翠巒の数
#define TIME 45 //制限時間（s）
#define SCORE_MAX 2000
#define PX_M 4.89 //px⇒m変換定数
//----------------------------------関数定義------------------------------------------
//game.cpp
void game();

//key.cpp
int GetHitKeyStateAll_2(int f);
int CheckStateKey(unsigned int Handle);
int key_ini();
void key_end();

//load.cpp
void load();


//----------------------------------構造体定義----------------------------------------
typedef struct{
	double  y,ang,v,xv,yv,v_MAX;
	int x,run;
}ch_t;
GLOBAL ch_t ch;

typedef struct{
	int x, y, v;		//座標
}back_t;
GLOBAL back_t back;

typedef struct{
	int x[MAX_SUIRAN], y[MAX_SUIRAN], r[MAX_SUIRAN], col[MAX_SUIRAN];
}suiran_t;
GLOBAL suiran_t suiran;

//----------------------------------変数定義------------------------------------------
GLOBAL int img[20];
GLOBAL int img_run[6];
GLOBAL int count;
GLOBAL int color[20];
GLOBAL int font[6];
GLOBAL int timer;
GLOBAL int score_r[SCORE_MAX][2];//記録用
GLOBAL char score_name[SCORE_MAX][300];//記録用
