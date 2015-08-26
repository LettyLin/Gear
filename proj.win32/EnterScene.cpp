#include "EnterScene.h"
#include "EnterLayer.h"

Scene* EnterScene::createScene(){
    Scene* scene = Scene::create();
   
    //��ӽ����
    EnterLayer* enterLayer = EnterLayer::create();
    scene->addChild(enterLayer);

    return scene;
}

