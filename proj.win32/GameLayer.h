/*
    GameLayer类，继承自Layer类
    处理地图，主角，怪物，Boss, NPC, 及其它地图元素之间的关系
*/
#ifndef _H_GAME_LAYER_
#define _H_GAME_LAYER_

#include <vector>
#include <cocos2d.h>
USING_NS_CC;

struct EnemyInfo{
    std::string name;
    int number;
};

struct SceneInfo{
    bool is_scroll_front;
    int npc_number;
    std::string* npcs;
    int enemy_number;
    EnemyInfo* enemies;
    int boss_number;
    EnemyInfo* bosses;

    Point enter_point;
    std::vector<Point> m_NPCPoints;
    std::vector<Point> m_EnemyPoints;
    std::vector<Point> m_BossPoints;
};

class MapLayer;
class Hero;
class NPC;
class Enemy;

class GameLayer : public Layer{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init(int which_scene);
    virtual bool init(int which_scene, const char* file_name);
    static GameLayer* create(int which_scene);
    static GameLayer* createWithFile(int which_scene, const char* file_name);

    void InitSceneInfo();

    void LoadSceneInfo(int which_scene);
    void ReleaseSceneInfo();

    void addMap(int which_scene);
    void addRole();
    void addRoleWithFile(const char* file_name);

    //cocos2d自带的更新函数，更新游戏
    virtual void update(float dt);

private:
    SceneInfo* m_pSceneInfo;

    int m_nSceneIndex;

    MapLayer* m_pMapLayer;
    Hero* m_pHero;
    NPC* m_pNpc;
    Vector<Enemy*>  m_pEnemies;
};

#endif