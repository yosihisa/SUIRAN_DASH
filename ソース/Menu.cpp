#include "Menu.h"
#include "GV.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void Menu::Initialize(){
    mImageHandle = LoadGraph("dat/menu.png");    //�摜�̃��[�h
}

//�X�V
void Menu::Update(){
	if (CheckStateKey(KEY_INPUT_SPACE)==1 || CheckStateKey(256)==1){//G�L�[��������Ă�����
        mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
    }
}

//�`��
void Menu::Draw(){
    BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
}
