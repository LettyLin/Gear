#include "GameLayer.h"
#include "Global.h"
#include "MapLayer.h"
#include "hero.h"
#include "NPC.h"
#include "Enemy.h"

GameLayer::GameLayer(){}
GameLayer::~GameLayer(){}

bool GameLayer::init(int which_scene){
    if (!Layer::init()){
        return false;
    }

    //根据场景名创建相应地图层
    const char* pcMapName = String::createWithFormat("map_scene%d.tmx", which_scene)->getCString();
    MapLayer* mapLayer = MapLayer::create(pcMapName);
    m_pMapLayer = mapLayer;
    mapLayer->LoadMapFromFile(pcMapName);
    mapLayer->setAnchorPoint(Vec2::ZERO);
    mapLayer->setPosition(Vec2::ZERO);
    addChild(mapLayer, 0);
    mapLayer->addFrontSprite("scene0_map_front.png", 120);
    mapLayer->addScrollSprite("scene0_map_scroll.png", 128, 0);

    //判断主角是否已存在，若不存在则创建主角
    if (NULL == global->hero){
        Hero* hero = Hero::create();
        m_pHero = hero;
        global->hero = hero;
        hero->setAnchorPoint(Vec2::ZERO);
        hero->setPosition(Vec2(200.0f, 600.0f));
        addChild(hero, 10);
    }

    NPC* npc = NPC::create();
    m_pNpc = npc;
    npc->setAnchorPoint(Vec2::ZERO);
    npc->setPosition(Vec2(800.0f, 250.0f));
    addChild(npc, 8);

    Enemy* enemy = Enemy::create();
    global->enemies.insert(0, enemy);
    enemy->setAnchorPoint(Vec2::ZERO);
    enemy->setPosition(1022.0f, 700.0f);
    addChild(enemy, 5);

    //启用cocos2d自带的更新函数
    this->scheduleUpdate();

    return true;
}

GameLayer* GameLayer::create(int which_scene){
    GameLayer* gameLayer = new GameLayer;
    if (gameLayer != NULL && gameLayer->init(which_scene)){
        gameLayer->autorelease();
    }
    else{
        delete gameLayer;
        gameLayer = NULL;
    }

    return gameLayer;
}

void GameLayer::update(float dt){
    //更新主角状态
    m_pHero->update();
    
    if (global->npc != NULL){
        m_pNpc->update();
    }

    if (!global->enemies.empty()){
        (*global->enemies.begin())->update();
    }

    //更新地图状态
    m_pMapLayer->update();

    //Add other update here

}