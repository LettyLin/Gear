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
    this->initWithSpriteFrameName("hero_stand00.png");

    Animation* idleAnimation = createNormalAction("hero_stand00.png", 1, 1);

    //创建站立动画，帧数8，帧率10
    Animation* standAnimation = createNormalAction("hero_stand%02d.png", 8, 10);
    this->setStandAction(RepeatForever::create(Animate::create(standAnimation)));

    //创建行走动画，帧数8，帧率20
    Animation* walkAnimation = createNormalAction("hero_walk%02d.png", 8, 14);
    this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

    Animation* jumpAnimation = createNormalAction("hero_jump%02d.png", 9, 20);
    this->setJumpAction(Sequence::create(Animate::create(jumpAnimation), 
        RepeatForever::create(Animate::create(idleAnimation)), 
        NULL));

    Animation* attackAnimation = createNormalAction("hero_attack%02d.png", 12, 20);
    this->setAttackAction(Sequence::create(Animate::create(attackAnimation),
        CallFuncN::create(CC_CALLBACK_0(Role::EndAttack, this)), 
        NULL));

    Animation* walkAttackAnimation = createNormalAction("hero_walkattack%02d.png", 14, 30);
    this->setWalkAttackAction(Sequence::create(Animate::create(walkAttackAnimation),
        CallFuncN::create(CC_CALLBACK_0(Role::EndAttack, this)),
        NULL));

    Animation* hurtAnimation = createNormalAction("hero_stand00.png", 1, 10);
    this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), 
        CallFuncN::create(CC_CALLBACK_0(Role::EndHurt, this)), 
        NULL));

    Animation* dieAnimation = createNormalAction("hero_stand00.png", 1, 10);

    //Add other actions here

    m_currentHp = 100;
    m_maxHp = 100;
    m_currentMp = 100;
    m_maxMp = 100;
    m_strenth = 20;
    m_defence = 20;

    m_bodyBox = createBoundingBox(Vec2(32, 16), getContentSize() - Size(64, 28));
    m_attackBox = createBoundingBox(Vec2(getContentSize().width / 2, -50), Size(200, getContentSize().height + 100));
    m_talkingBox = createBoundingBox(Vec2(-400, -50), Size(800, getContentSize().height + 100));

    //设置初始速度
    this->setVelocity(Vec2(0, 0));

    //set other properties here

    return true;
}

//调用站立动作
void Hero::onStand(){
    if (!m_moveable){
        return;
    }

    setVelocity(Vec2::ZERO);
    Role::onStand();
}

//调用行走动作
void Hero::onWalk(){
    if (!m_moveable){
        return;
    }

    setVelocity(Vec2(5, 0));
    Role::onWalk();
}

void Hero::onJump(){
    if (!m_moveable){
        return;
    }

    if (!m_dropping){
        m_dropping = true;
        setVelocity(Vec2(3, 8));
    }
    Role::onJump();
}

void Hero::onHurt(int hurt){
    if (!m_moveable){
        return;
    }

    int actual_hurt = hurt - (m_defence + rand() % 20 - 10);
    m_currentHp -= actual_hurt;
    Role::onHurt(actual_hurt);
    m_moveable = false;
}

void Hero::onDie(){
    setVelocity(Vec2::ZERO);
    Role::onDie();
}

void Hero::onAttack(){
    if (!m_moveable){
        return;
    }
    Role::onAttack();

    Vector<Enemy*> enemies = global->enemies;

    if (enemies.empty()){
        m_moveable = false;
        return;
    }

    Vector<Enemy*>::iterator it = enemies.begin();
    for (; it != enemies.end(); ++it){
        Rect enemyBox = (*it)->getBodyBox().actual;
        if (enemyBox.intersectsRect(getAttackBox().actual)){
            int hurt = m_strenth + rand() % 20 - 10;
            if (rand() % 100 < 5){
                hurt *= 2;
            }
            (*it)->onHurt(hurt);
        }
    }
    m_moveable = false;
}

void Hero::onWalkAttack(){
    if (!m_moveable){
        return;
    }
    Role::onWalkAttack();

    Vector<Enemy*> enemies = global->enemies;

    if (enemies.empty()){
        m_moveable = false;
        return;
    }

    Vector<Enemy*>::iterator it = enemies.begin();
    for (; it != enemies.end(); ++it){
        Rect enemyBox = (*it)->getBodyBox().actual;
        if (enemyBox.intersectsRect(getAttackBox().actual)){
            int hurt = m_strenth + rand() % 20 - 10;
            if (rand() % 100 < 5){
                hurt *= 2;
            }
            (*it)->onHurt(hurt);
        }
    }
    m_moveable = false;
}

void Hero::onTalk(){
    Rect npcBox = global->npc->getBodyBox().actual;
    Rect a = getTalkingBox().actual;
    if (a.intersectsRect(npcBox)){
        global->npc->startTalking();
    }
}

void Hero::updateAllBox(){
    updateBox(m_bodyBox);
    updateBox(m_attackBox);
    updateBox(m_talkingBox);
}