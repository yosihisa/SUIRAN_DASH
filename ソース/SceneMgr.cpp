#include "DxLib.h"
#include "score.h"
#include "Game.h"
#include "Menu.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr() : 
    mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
    mScene = (BaseScene*) new Menu(this);
}

//������
void SceneMgr::Initialize(){
    mScene->Initialize();
}

//�I������
void SceneMgr::Finalize(){
    mScene->Finalize();
}

//�X�V
void SceneMgr::Update(){
    if(mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
        mScene->Finalize();//���݂̃V�[���̏I�����������s
        delete mScene;
        switch(mNextScene){       //�V�[���ɂ���ď����𕪊�
        case eScene_Menu:        //���̉�ʂ����j���[�Ȃ�
            mScene = (BaseScene*) new Menu(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
            break;//�ȉ���
        case eScene_Game:
            mScene = (BaseScene*) new Game(this);
            break;
		case eScene_score:
			mScene = (BaseScene*) new score(this);
            break;
        }
        mNextScene = eScene_None;    //���̃V�[�������N���A
        mScene->Initialize();    //�V�[����������
    }

    mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMgr::Draw(){
    mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(eScene NextScene){
    mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}
