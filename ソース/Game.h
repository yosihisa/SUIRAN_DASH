#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"

//�Q�[����ʃN���X
class Game : public BaseScene {

public :
    Game::Game(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    //void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};
