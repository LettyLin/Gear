#include "Hero.h"
#include "Global.h"
#include "NPC.h"
#include "Enemy.h"

Hero::Hero(){
    //将hero注册到global中
    if (NULL == global->hero){
        ;
    }
}
Hero::~Hero(){
    //global->hero = NULL;
}

//初始化主角各动作的动画
bool Hero::init(){
    if (!Sprite::init()){
        return false;
    }
    
    //将包含主角所有动作帧的合图载入到帧缓存池中
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist", "hero.png");
    //设置主角初始帧
    this->initWithSpriteFrameName("hero_normal.png");

    //创建站立动画，帧数1，帧率10
    Animation* standAnimation = createNormalAction("hero_normal.png", 1, 10);
    this->setStandAction(RepeatForever::create(Animate::create(standAnimation)));

    //创建行走动画，帧数4，帧率20
    Animation* walkAnimation = createNormalAction("hero_walk_%02d.png", 4, 20);
    this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

    Animation* jumpAnimation = createNormalAction("hero_normal.png", 1, 10);
    this->setJumpAction(RepeatForever::create(Animate::create(jumpAnimation)));

    //Add other actions here

    m_bodyBox = createBoundingBox(Vec2(0, 0), getContentSize());
    m_attackBox = createBoundingBox(Vec2(getContentSize().width / 2, -50), Size(200, getContentSize().height + 100));
    m_talkingBox = createBoundingBox(Vec2(-400, -50), Size(800, getContentSize().height + 100));

    //设置初始速度
    this->setVelocity(Vec2(0, 0));

    //set other properties here

    return true;
}

void Hero::update(){
    Role::update();
    updateBox(m_attackBox);
    updateBox(m_talkingBox);
}

//调用站立动作
void Hero::onStand(){
    setVelocity(Vec2::ZERO);
    runStandAction();
}

//调用行走动作
void Hero::onWalk(){
    setVelocity(Vec2(5, 0));
    runWalkAction();
}

void Hero::onJump(){
    if (!m_dropping){
        m_dropping = true;
        setVelocity(Vec2(m_velocity.x, 30));
    }
    runJumpAction();
}

void Hero::onAttack(){
    Vector<Enemy*> enemies = global->enemies;

    if (enemies.empty()){
        return;
    }

    Vector<Enemy*>::iterator it = enemies.begin();
    for (; it != enemies.end(); ++it){
        Rect enemyBox = (*it)->getBodyBox().actual;
        if (enemyBox.intersectsRect(getAttackBox().actual)){
            (*it)->onHurt(rand() % 20  + 10);
        }
    }
}

void Hero::onTalk(){
    Rect npcBox = global->npc->getBodyBox().actual;
    Rect a = getTalkingBox().actual;
    if (a.intersectsRect(npcBox)){
        global->npc->startTalking();
    }
}