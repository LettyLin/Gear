#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "UILayer.h"
#include "Global.h"

Scene* GameScene::createScene(int which_scene){
    //��������
    Scene* scene = Scene::create();

    //�����Ϸ��
    GameLayer * gameLayer = GameLayer::create(which_scene);
    scene->addChild(gameLayer, 0);


    UiLayer* uiLayer = UiLayer::create();
    scene->addChild(uiLayer, 120);
    global->uiLayer = uiLayer;

    //��Ӳ�����
    OperateLayer* operateLayer = OperateLayer::create();
    scene->addChild(operateLayer, 10);
    global->operateLayer = operateLayer;

    return scene;
}

Scene* GameScene::createSceneWithFile(int which_scene, const char* file_name){
    //��������
    Scene* scene = Scene::create();

    //�����Ϸ��
    GameLayer * gameLayer = GameLayer::createWithFile(which_scene, file_name);
    scene->addChild(gameLayer, 0);

    //��Ӳ�����
    OperateLayer* operateLayer = OperateLayer::create();
    scene->addChild(operateLayer, 10);

    UiLayer* uiLayer = UiLayer::create();
    scene->addChild(uiLayer);

    return scene;
}