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

class Global : public Singleton<Global>{
public:
    Global();
    ~Global();

    //注册主角类，根据交互层信息进行更新
    Hero* hero;

    NPC* npc;

    Vector<Enemy*> enemies;

    //注册地图管理层，根据主角位置进行更新
    MapLayer* mapLayer;

    //进入场景
    void EnterScene(int scene_number);

    //地图坐标转换瓦块坐标函数，用于碰撞检测
    Point tileCoordForPosition(const Point &position);

    //碰撞检测函数
   void CheckCollision(const Point &last_position, const Point &new_position, const Size &size, Point &final_position, int &dropping);

    //创建对话层
    void createTalkingLayer(std::string conversation);

    void setTalking(bool talking){
        m_bTalking = talking;
    }

    bool IsTalking(){
        return m_bTalking;
    }

private:
    bool m_bTalking;
};

//定义调用该类唯一实例的宏
#define global Global::instance()
#endif