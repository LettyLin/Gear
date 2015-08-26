#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"

Scene* GameScene::createScene(int which_scene){
    //��������
    Scene* scene = Scene::create();

    //�����Ϸ��
    GameLayer * gameLayer = GameLayer::create(which_scene);
    scene->addChild(gameLayer, 0);

    //��Ӳ�����
    OperateLayer* operateLayer = OperateLayer::create();
    scene->addChild(operateLayer, 10);

    //Add UiLayer here

    return scene;
}