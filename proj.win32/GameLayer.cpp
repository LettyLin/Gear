#include "GameLayer.h"
#include "Global.h"
#include "MapLayer.h"
#include "hero.h"
#include "NPC.h"
#include "Enemy.h"
#include <fstream>
#include "Formater.h"

#define MAX_SCENE 2

GameLayer::GameLayer(){}
GameLayer::~GameLayer(){}

bool GameLayer::init(int which_scene){
    if (!Layer::init()){
        return false;
    }

    m_nSceneIndex = which_scene;

    InitSceneInfo();

    LoadSceneInfo(which_scene);
    addMap(which_scene);

    addRole();
    ReleaseSceneInfo();


    //����cocos2d�Դ��ĸ��º���
    this->scheduleUpdate();

    return true;
}

bool GameLayer::init(int which_scene, const char* file_name){
    if (!Layer::init()){
        return false;
    }

    m_nSceneIndex = which_scene;

    InitSceneInfo();

    LoadSceneInfo(which_scene);
    addMap(which_scene);

    addRoleWithFile(file_name);
    ReleaseSceneInfo();


    //����cocos2d�Դ��ĸ��º���
    this->scheduleUpdate();

    return true;
}

void GameLayer::InitSceneInfo(){
    m_pSceneInfo = new SceneInfo;

    m_pSceneInfo->is_scroll_front = false;
    m_pSceneInfo->npc_number = 0;
    m_pSceneInfo->npcs = NULL;
    m_pSceneInfo->enemy_number = 0;
    m_pSceneInfo->enemies = NULL;
    m_pSceneInfo->boss_number = 0;
    m_pSceneInfo->bosses = NULL;

    Point enter_point = Point(300, 300);
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

GameLayer* GameLayer::createWithFile(int which_scene, const char* file_name){
    GameLayer* gameLayer = new GameLayer;
    if (gameLayer != NULL && gameLayer->init(which_scene, file_name)){
        gameLayer->autorelease();
    }
    else{
        delete gameLayer;
        gameLayer = NULL;
    }

    return gameLayer;
}

void GameLayer::LoadSceneInfo(int which_scene){
    const char* fileName = String::createWithFormat("scene%d_setting.txt", which_scene)->getCString();
    std::ifstream FileReader(fileName);

    CC_ASSERT(FileReader.is_open());
    std::string buffer;
    std::string discard;

    for (; !FileReader.eof();){
        FileReader >> buffer;
        FileReader >> discard;
        if (buffer == "nHasScrollFront"){
            FileReader >> buffer;
            m_pSceneInfo->is_scroll_front = Formater::getBool(buffer);
            continue;
        }
        else if (buffer == "NPCNumber"){
            FileReader >> buffer;
            m_pSceneInfo->npc_number = Formater::getInt(buffer);
            if (m_pSceneInfo->npc_number == 0){
                continue;
            }
            m_pSceneInfo->npcs = new std::string[m_pSceneInfo->npc_number];
            for (int i = 0; i < m_pSceneInfo->npc_number; ++i){
                FileReader >> buffer;
                FileReader >> discard;
                FileReader >> buffer;
                m_pSceneInfo->npcs[i] = Formater::getString(buffer);
            }
            continue;
        }
        else if (buffer == "EnemyTypeNumber"){
            FileReader >> buffer;
            m_pSceneInfo->enemy_number = Formater::getInt(buffer);
            if (m_pSceneInfo->enemy_number == 0){
                continue;
            }
            m_pSceneInfo->enemies = new EnemyInfo[m_pSceneInfo->enemy_number];
            for (int i = 0; i < m_pSceneInfo->enemy_number; ++i){
                FileReader >> buffer;
                FileReader >> discard;
                FileReader >> buffer;
                m_pSceneInfo->enemies[i].name = Formater::getString(buffer);
                FileReader >> buffer;
                FileReader >> discard;
                FileReader >> buffer;
                m_pSceneInfo->enemies[i].number = Formater::getInt(buffer);
            }
            continue;
        }
        else if(buffer == "BossTypeNumber"){
            FileReader >> buffer;
            m_pSceneInfo->boss_number = Formater::getInt(buffer);
            if (m_pSceneInfo->boss_number == 0){
                continue;
            }
            m_pSceneInfo->bosses = new EnemyInfo[m_pSceneInfo->boss_number];
            for (int i = 0; i < m_pSceneInfo->boss_number; ++i){
                FileReader >> buffer;
                FileReader >> discard;
                FileReader >> buffer;
                m_pSceneInfo->bosses[i].name = Formater::getString(buffer);
                FileReader >> buffer;
                FileReader >> discard;
                FileReader >> buffer;
                m_pSceneInfo->bosses[i].number = Formater::getInt(buffer);
            }
            continue;
        }
        else if (buffer == "EnterPoint"){
            FileReader >> buffer;
            m_pSceneInfo->enter_point = Formater::getPoint(buffer);
            continue;
        }
        else if (buffer == "NPCPoint"){
            FileReader >> buffer;
            Point npcPoint = Formater::getPoint(buffer);
            m_pSceneInfo->m_NPCPoints.push_back(npcPoint);
            continue;
        }
        else if (buffer == "EnemyPoint"){
            FileReader >> buffer;
            Point enemyPoint = Formater::getPoint(buffer);
            m_pSceneInfo->m_EnemyPoints.push_back(enemyPoint);
            continue;
        }
        else if (buffer == "BossPoint"){
            FileReader >> buffer;
            Point bossPoint = Formater::getPoint(buffer);
            m_pSceneInfo->m_BossPoints.push_back(bossPoint);
            continue;
        }
    }
    
    return;
}

void GameLayer::ReleaseSceneInfo(){
    if (m_pSceneInfo != NULL){
        if (m_pSceneInfo->bosses != NULL){
            delete[] m_pSceneInfo->bosses;
            m_pSceneInfo->bosses = NULL;
        }
        if (m_pSceneInfo->enemies != NULL){
            delete[] m_pSceneInfo->enemies;
            m_pSceneInfo->enemies = NULL;
        }
        if (m_pSceneInfo->npcs != NULL){
            delete[] m_pSceneInfo->npcs;
            m_pSceneInfo->npcs = NULL;
        }

        delete m_pSceneInfo;
        m_pSceneInfo = NULL;
    }
}

void GameLayer::addMap(int which_scene){
    const char* pcMapName = String::createWithFormat("map_scene%d.tmx", which_scene)->getCString();
    MapLayer* mapLayer = MapLayer::create(pcMapName);
    m_pMapLayer = mapLayer;
    mapLayer->LoadMapFromFile(pcMapName);
    mapLayer->setAnchorPoint(Vec2::ZERO);
    mapLayer->setPosition(Vec2::ZERO);
    addChild(mapLayer, 0);

    const char* pcMapFrontName = String::createWithFormat("scene%d_map_front.png", which_scene)->getCString();
    mapLayer->addFrontSprite(pcMapFrontName, 120);

    if (m_pSceneInfo->is_scroll_front){
        const char* pcMapScrollFrontName = String::createWithFormat("scene%d_map_scroll.png", which_scene)->getCString();
        mapLayer->addScrollSprite(pcMapScrollFrontName, 120, 0);
    }
}

void GameLayer::addRole(){
    Hero* hero;
    if (global->hero == NULL){
        global->hero = Hero::create();
        global->hero->retain();
        hero = global->hero;
    }
    else{
        hero = Hero::create();
        hero->Inherit(global->hero);
        global->hero = hero;
    }

   
    hero->setAnchorPoint(Vec2::ZERO);
    hero->setPosition(m_pSceneInfo->enter_point);
    hero->updateAllBox();
    hero->onStand();
    addChild(hero, 10);

    for (int i = 0; i < m_pSceneInfo->npc_number; ++i){
        NPC* npc = NPC::create(m_pSceneInfo->npcs[i].c_str());
        global->npc = npc;
        npc->setAnchorPoint(Vec2::ZERO);
        npc->setPosition(m_pSceneInfo->m_NPCPoints.at(i));
        npc->updateAllBox();
        addChild(npc, 8);
    }

    for (int i = 0; i < m_pSceneInfo->enemy_number; ++i){
        for (int j = 0; j < m_pSceneInfo->enemies[i].number; ++j){
            Enemy* enemy = Enemy::create();
            global->enemies.insert(i, enemy);
            enemy->setAnchorPoint(Vec2::ZERO);
            int random = rand() % m_pSceneInfo->m_EnemyPoints.size();
            enemy->setPosition(m_pSceneInfo->m_EnemyPoints.at(random));
            enemy->updateAllBox();
            addChild(enemy, 9);        
        }
    }
}

void GameLayer::addRoleWithFile(const char* file_name){    
    Hero* hero;
    global->hero = Hero::create();
    global->hero->retain();
    hero = global->hero;

    hero->setAnchorPoint(Vec2::ZERO);


    NPC* npc = NPC::create("npc");
    global->npc = npc;
    npc->setAnchorPoint(Vec2::ZERO);
    npc->setPosition(m_pSceneInfo->m_NPCPoints.at(0));
    npc->updateAllBox();
    addChild(npc, 8);

    std::ifstream Reader(file_name);
    CC_ASSERT(Reader.is_open());
    std::string buffer;
    std::string discard;
    for (; !Reader.eof();){
        Reader >> buffer;
        Reader >> discard;
        if (buffer == "Scene"){
            Reader >> discard;
            continue;
        }
        else if (buffer == "Point"){
            Reader >> buffer;
            hero->setPosition(Formater::getPoint(buffer));
            continue;
        }
        else if (buffer == "TalkingTimes"){
            Reader >> buffer;
            npc->setTalkingTimes(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "CurrentHp"){
            Reader >> buffer;
            hero->setCurrentHp(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "MaxHp"){
            Reader >> buffer;
            hero->setMaxHp(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "CurrentMp"){
            Reader >> buffer;
            hero->setCurrentMp(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "MaxMp"){
            Reader >> buffer;
            hero->setMaxMp(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "Strenth"){
            Reader >> buffer;
            hero->setStrenth(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "Defence"){
            Reader >> buffer;
            hero->setDefence(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "Velocity"){
            Reader >> buffer;
            hero->setMoveVelocity(Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "Direction"){
            Reader >> buffer;
            hero->setDirection((eRoleDirection)Formater::getInt(buffer));
            continue;
        }
        else if (buffer == "Tools"){
            Reader >> discard;
            for (;;){
                Reader >> buffer;
                if (buffer == "id"){
                    Reader >> discard;
                    Reader >> buffer;
                    hero->GetTool(Formater::getInt(buffer));
                    continue;
                }
                else if (buffer == "}"){
                    break;
                }
            }
        }
        else if (buffer == "Skills"){
            Reader >> discard;
            for (;;){
                Reader >> buffer;
                if (buffer == "id"){
                    Reader >> discard;
                    Reader >> buffer;
                    hero->GetSkill(Formater::getInt(buffer));
                    continue;
                }
                else if (buffer == "}"){
                    break;
                }
            }
        }
    }

    hero->updateAllBox();
    hero->onStand();
    addChild(hero, 10);

    for (int i = 0; i < m_pSceneInfo->enemy_number; ++i){
        for (int j = 0; j < m_pSceneInfo->enemies[i].number; ++j){
            Enemy* enemy = Enemy::create();
            global->enemies.insert(i, enemy);
            enemy->setAnchorPoint(Vec2::ZERO);
            int random = rand() % m_pSceneInfo->m_EnemyPoints.size();
            enemy->setPosition(m_pSceneInfo->m_EnemyPoints.at(random));
            enemy->updateAllBox();
            addChild(enemy, 9);
        }
    }
}

void GameLayer::update(float dt){
    if (global->getGamePause()){
        return;
    }
    //��������״̬
    Hero* hero = global->hero;
    hero->update();
    if (hero->getBodyBox().actual.origin.x + hero->getBodyBox().origin.size.width == m_pMapLayer->getMap()->getContentSize().width
        && m_nSceneIndex != MAX_SCENE){
        GameUtile::EnterScene(m_nSceneIndex + 1);
    }

    if (global->npc != NULL){
        global->npc->update();
    }

    Vector<Enemy*> enemies = global->enemies;
    if (!enemies.empty()){
        for (Vector<Enemy*>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
        (*enemy)->update();
    }

    //���µ�ͼ״̬
    m_pMapLayer->update();

    //Add other update here
}