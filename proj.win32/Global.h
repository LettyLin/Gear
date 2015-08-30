/*
    Global类：继承自Singleton类
    全局单例，用于注册各个有关联的类，使其可以相互通信，并提供一些重要的辅助函数
*/
#ifndef _H_GLOBAL_
#define _H_GLOBAL_

#include "Singleton.h"
#include <cocos2d.h>
USING_NS_CC;

class MapLayer;
class Hero;
class NPC;
class Enemy;
class Backpack;
class Property;

class ButtonLayer;

class GameLayer;
class OperateLayer;
class UiLayer;

class Global : public Singleton<Global>{
public:
    Global();
    ~Global();

    //注册主角类，根据交互层信息进行更新
    Hero* hero;
    NPC* npc;
    Vector<Enemy*> enemies;
    MapLayer* mapLayer;

    Backpack* backpack;
    Property* property;

    ButtonLayer* buttonLayer;

    GameLayer* gameLayer;
    OperateLayer* operateLayer;
    UiLayer* uiLayer;

    //创建对话层
    //void createTalkingLayer(std::string conversation);

    CC_SYNTHESIZE(bool, m_bTalking, Talking);
    CC_SYNTHESIZE(bool, m_bGamePause, GamePause);
    CC_SYNTHESIZE(bool, m_bMusicPause, MusicPause);
    CC_SYNTHESIZE(int, m_nSceneIndex, SceneIndex);
};

//定义调用该类唯一实例的宏
#define global Global::instance()
#endif