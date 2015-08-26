#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"

Scene* GameScene::createScene(int which_scene){
    //创建场景
    Scene* scene = Scene::create();

    //添加游戏层
    GameLayer * gameLayer = GameLayer::create(which_scene);
    scene->addChild(gameLayer, 0);

    //添加操作层
    OperateLayer* operateLayer = OperateLayer::create();
    scene->addChild(operateLayer, 10);

    //Add UiLayer here

    return scene;
}