/*
    Global�ࣺ�̳���Singleton��
    ȫ�ֵ���������ע������й������࣬ʹ������໥ͨ�ţ����ṩһЩ��Ҫ�ĸ�������
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

    //ע�������࣬���ݽ�������Ϣ���и���
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

    //�����Ի���
    //void createTalkingLayer(std::string conversation);

    CC_SYNTHESIZE(bool, m_bTalking, Talking);
    CC_SYNTHESIZE(bool, m_bGamePause, GamePause);
    CC_SYNTHESIZE(bool, m_bMusicPause, MusicPause);
    CC_SYNTHESIZE(int, m_nSceneIndex, SceneIndex);
};

//������ø���Ψһʵ���ĺ�
#define global Global::instance()
#endif