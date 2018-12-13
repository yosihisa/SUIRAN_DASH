#include "GV.h"
#include "score.h"
#include <time.h>

char String[256];
int InputHandle;
static int score_num;
static int rank[16] = { 0 };
static int num[SCORE_MAX][2];
static int warn = 0;//�����͏I���x��
int img_s;
int hiscore;


score::score(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void score::Initialize(){
	warn = 0;
	img_s = LoadGraph("dat/score.png");    //�摜�̃��[�h
	int n = 0;
	
	char line[300] = { 0 };
	char *p, *find;
	char *ary[5];
	FILE *fp;

	if (fopen_s(&fp, "Score.dat", "rb") != 0){
		hiscore = 0;
		for (n = 0; n < SCORE_MAX; n++) {
			score_r[n][0] = -1;
			score_r[n][1] = -1;
			sprintf_s(score_name[n], "-1\n");
		}
	}
	else{
		/*�t�@�C���̏I���܂ŌJ��Ԃ��ǂݍ���*/
		while (fgets(line, 300, fp) != NULL){
			if (n==SCORE_MAX)break;

			ary[0] = strtok_s(line, ",", &p);
			ary[1] = strtok_s(NULL, ",", &p);
			if (n==0){
				hiscore = atoi(ary[0]);
			}
			else{
				score_r[n][0] = atoi(ary[0]);
				score_r[n][1] = atoi(ary[1]);
				sprintf_s(score_name[n], "%s", strtok_s(NULL, ",", &p));

			}
			n++;
		}
		fclose(fp);
	}

	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);

	// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	SetActiveKeyInput(InputHandle);
	SetKeyInputStringColor(color[1], color[6],
		color[5], color[6],
		color[1], color[6],
		color[3], color[0],
		color[6], color[0],
		color[0], color[5],
		color[6], color[0],
		color[0], color[1],
		color[0]
		);

	for (int i = 1; i<SCORE_MAX; i++){
		if (score_r[i][1]==-1){
			score_num = i;
			break;
		}
	}
}

//�I������
void score::Finalize(){
	FILE *fp;
	int	i;

	if (ch.x>hiscore)hiscore = ch.x;
	// �t�@�C���̃I�[�v��
	if (fopen_s(&fp, "Score.dat", "wb") !=0) return;
	// �w�b�_�s���o�͂���
	fprintf(fp, "%d,\n",hiscore);
	// �e�f�[�^���J���}��؂�ŏo�͂���
	for (i = 1; i < SCORE_MAX; i++) {
		fprintf(fp, "%d,%d,%s", score_r[i][0], score_r[i][1], score_name[i]);
	}
	fclose(fp);
}

//�X�V
void score::Update(){
	if (CheckStateKey(KEY_INPUT_ESCAPE)==1||CheckStateKey(257)==1){ //Esc�L�[��������Ă�����
		if (warn==1 || CheckKeyInput(InputHandle) != 0)mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
		if (warn==0)warn = 1;
    }
	for (int i = 0; i<258; i++)
	{
		if (i != (0x01) && i != 257){
			if (CheckStateKey(i)!=0)warn = 0;
		}
	}
	int Y, M, D, h, min;
	int t;
	//char str[13];
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	Y = pnow->tm_year+1900-2000;
	M = pnow->tm_mon+1;
	D = pnow->tm_mday;
	h = pnow->tm_hour;
	min = pnow->tm_min;
	if (CheckKeyInput(InputHandle) != 0){
		t = 100000000*Y + 1000000*M + 10000*D + 100*h + min;
		score_r[score_num][0] =  t;
		score_r[score_num][1] = ch.x;
		sprintf_s(score_name[score_num], "%s\n", String);

	}
	int tmp, i, p, q;
	for (i = 1; i<SCORE_MAX; i++){
		num[i][0] = i;
		num[i][1] = score_r[i][1];
	}
	for (p = 1; p < SCORE_MAX+1; p++){
		for (q = p + 1; q < SCORE_MAX; q++){
			if (num[p][1] < num[q][1]){
				tmp = num[p][1];
				num[p][1] = num[q][1];
				num[q][1] = tmp;

				tmp = num[p][0];
				num[p][0] = num[q][0];
				num[q][0] = tmp;
			}
		}
	}
	i++;
}

//�`��
void score::Draw(){

	char str[400], name[300];
	char *find;
	int t, Y, M, D, h, min;
	DrawGraph(0, 0, img_s, FALSE);
	// �L�[���͏I���҂����[�v
	if (CheckKeyInput(InputHandle) == 0){

		// ���̓��[�h��`��
		DrawKeyInputModeString(640, 480);

		// ���͓r���̕������`��
		DrawKeyInputString(400, 25, InputHandle);
		sprintf_s(str, "%.1f��", 1.0*ch.x/PX_M);
	}
	else{
		// ���͂��ꂽ��������擾
		GetKeyInputString(String, InputHandle);

		// �p�ς݂̃C���v�b�g�n���h�����폜����
		DeleteKeyInput(InputHandle);

		// ���͂��ꂽ���������ʂɕ\������
		DrawString(400, 25, String, GetColor(0, 0, 255));
		for (int i = 1; i<SCORE_MAX; i++){
			if (score_num==num[i][0])sprintf_s(str, "%.1f�� %d��", 1.0*ch.x/PX_M,i);
		}

	}
	
	if (warn==1 && CheckKeyInput(InputHandle) == 0)DrawStringToHandle(200, 90, "�����͂ł��I�i�߂�ꍇ�͂�����x�u�߂�iESC�j�v�������j", color[2], font[0], color[5]);
	DrawStringToHandle(400, 55, str, color[4], font[0], color[0]);
	for (int i = 1; i<21; i++){
		if (score_r[num[i][0]][1]!=-1){
			t = score_r[num[i][0]][0];
			min = t%100, t /= 100;
			h = t%100, t /= 100;
			D = t%100, t /= 100;
			M = t%100, t /= 100;
			Y = t%100, t /= 100;
			sprintf_s(name, "%s", score_name[num[i][0]]);
			if ((find = strchr(name, '\n')) != NULL){
				*find = '\0';
			}
			sprintf_s(str, "%02d�� 20%02d�N%02d��%02d���@%02d�F%02d %.1f�� %s", i,Y, M, D, h, min, 1.0*score_r[num[i][0]][1]/PX_M,name);
			if (score_num==num[i][0])DrawStringToHandle(100, 95+i*18, str, color[2], font[0], color[5]);
			else DrawStringToHandle(100, 95+i*18, str, color[4], font[0], color[0]);
		}
	}

	if (CheckKeyInput(InputHandle) == 0){

		// ���̓��[�h��`��
		DrawKeyInputModeString(640, 480);

		// ���͓r���̕������`��
		DrawKeyInputString(400, 25, InputHandle);
		sprintf_s(str, "%.1f��", 1.0*ch.x/PX_M);
	}

}
