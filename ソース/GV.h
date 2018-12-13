#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif
#include "DxLib.h"
#include "math.h"


//----------------------------------�萔��`------------------------------------------
#define PI 3.14152653589793238462
#define PI2 PI*2
#define CH_Y_H 35//���@�̉摜�̍�����2
#define CH_X_H 35
#define CH_X 100 //�`��ʒu x���W
#define MAX_SUIRAN 300 //���ۂ̐�
#define TIME 45 //�������ԁis�j
#define SCORE_MAX 2000
#define PX_M 4.89 //px��m�ϊ��萔
//----------------------------------�֐���`------------------------------------------
//game.cpp
void game();

//key.cpp
int GetHitKeyStateAll_2(int f);
int CheckStateKey(unsigned int Handle);
int key_ini();
void key_end();

//load.cpp
void load();


//----------------------------------�\���̒�`----------------------------------------
typedef struct{
	double  y,ang,v,xv,yv,v_MAX;
	int x,run;
}ch_t;
GLOBAL ch_t ch;

typedef struct{
	int x, y, v;		//���W
}back_t;
GLOBAL back_t back;

typedef struct{
	int x[MAX_SUIRAN], y[MAX_SUIRAN], r[MAX_SUIRAN], col[MAX_SUIRAN];
}suiran_t;
GLOBAL suiran_t suiran;

//----------------------------------�ϐ���`------------------------------------------
GLOBAL int img[20];
GLOBAL int img_run[6];
GLOBAL int count;
GLOBAL int color[20];
GLOBAL int font[6];
GLOBAL int timer;
GLOBAL int score_r[SCORE_MAX][2];//�L�^�p
GLOBAL char score_name[SCORE_MAX][300];//�L�^�p
