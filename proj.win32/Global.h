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
class Keyboard;
class Role;
class Hero;
class NPC;
class Enemy;

class Global : public Singleton<Global>{
public:
    Global();
    ~Global();

    //ע�������࣬���ݽ�������Ϣ���и���
    Hero* hero;
    NPC* npc;
    Vector<Enemy*> enemies;
    MapLayer* mapLayer;
    Keyboard* keyLayer;


    //���볡��
    void EnterScene(int scene_number);

    //��ͼ����ת���߿����꺯����������ײ���
    Point tileCoordForPosition(const Point &position);

    //��ײ��⺯��
    void CheckCollision(Role* role, const Point &expect_position, Point &final_position, int &dropping);

    //�����Ի���
    void createTalkingLayer(std::string conversation);

    void setTalking(bool talking){
        m_bTalking = talking;
    }

    bool IsTalking(){
        return m_bTalking;
    }

    void setSceneIndex(int which_scene){
        m_nSceneIndex = which_scene;
    }

    int getSceneIndex(){
        return m_nSceneIndex;
    }

private:
    bool m_bTalking;
    int m_nSceneIndex;
};

//������ø���Ψһʵ���ĺ�
#define global Global::instance()
#endif