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

class Global : public Singleton<Global>{
public:
    Global();
    ~Global();

    //ע�������࣬���ݽ�������Ϣ���и���
    Hero* hero;

    NPC* npc;

    Vector<Enemy*> enemies;

    //ע���ͼ����㣬��������λ�ý��и���
    MapLayer* mapLayer;

    //���볡��
    void EnterScene(int scene_number);

    //��ͼ����ת���߿����꺯����������ײ���
    Point tileCoordForPosition(const Point &position);

    //��ײ��⺯��
   void CheckCollision(const Point &last_position, const Point &new_position, const Size &size, Point &final_position, int &dropping);

    //�����Ի���
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

//������ø���Ψһʵ���ĺ�
#define global Global::instance()
#endif