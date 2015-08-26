#include "EnterScene.h"
#include "EnterLayer.h"

Scene* EnterScene::createScene(){
    Scene* scene = Scene::create();
   
    //Ìí¼Ó½øÈë²ã
    EnterLayer* enterLayer = EnterLayer::create();
    scene->addChild(enterLayer);

    return scene;
}

