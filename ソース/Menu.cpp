#include "Menu.h"
#include "GV.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Menu::Initialize(){
    mImageHandle = LoadGraph("dat/menu.png");    //画像のロード
}

//更新
void Menu::Update(){
	if (CheckStateKey(KEY_INPUT_SPACE)==1 || CheckStateKey(256)==1){//Gキーが押されていたら
        mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
    }
}

//描画
void Menu::Draw(){
    BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
}
