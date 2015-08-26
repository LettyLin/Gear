/*
    GameLayer�࣬�̳���Layer��
    �����ͼ�����ǣ����Boss, NPC, ��������ͼԪ��֮��Ĺ�ϵ
*/
#ifndef _H_GAME_LAYER_
#define _H_GAME_LAYER_

#include <cocos2d.h>
USING_NS_CC;

class MapLayer;
class Hero;
class NPC;
class Enemy;

class GameLayer : public Layer{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init(int which_scene);
    static GameLayer* create(int which_scene);

    //cocos2d�Դ��ĸ��º�����������Ϸ
    virtual void update(float dt);

private:
    MapLayer* m_pMapLayer;
    Hero* m_pHero;
    NPC* m_pNpc;
    Vector<Enemy*>  m_pEnemies;
};

#endif