#include "Hero.h"
#include "Global.h"
#include "NPC.h"
#include "Enemy.h"

Hero::Hero(){
    //��heroע�ᵽglobal��
    if (NULL == global->hero){
        ;
    }
}
Hero::~Hero(){
    //global->hero = NULL;
}

//��ʼ�����Ǹ������Ķ���
bool Hero::init(){
    if (!Sprite::init()){
        return false;
    }
    
    //�������������ж���֡�ĺ�ͼ���뵽֡�������
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist", "hero.png");
    //�������ǳ�ʼ֡
    this->initWithSpriteFrameName("hero_normal.png");

    //����վ��������֡��1��֡��10
    Animation* standAnimation = createNormalAction("hero_normal.png", 1, 10);
    this->setStandAction(RepeatForever::create(Animate::create(standAnimation)));

    //�������߶�����֡��4��֡��20
    Animation* walkAnimation = createNormalAction("hero_walk_%02d.png", 4, 20);
    this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

    Animation* jumpAnimation = createNormalAction("hero_normal.png", 1, 10);
    this->setJumpAction(RepeatForever::create(Animate::create(jumpAnimation)));

    //Add other actions here

    m_bodyBox = createBoundingBox(Vec2(0, 0), getContentSize());
    m_attackBox = createBoundingBox(Vec2(getContentSize().width / 2, -50), Size(200, getContentSize().height + 100));
    m_talkingBox = createBoundingBox(Vec2(-400, -50), Size(800, getContentSize().height + 100));

    //���ó�ʼ�ٶ�
    this->setVelocity(Vec2(0, 0));

    //set other properties here

    return true;
}

void Hero::update(){
    Role::update();
    updateBox(m_attackBox);
    updateBox(m_talkingBox);
}

//����վ������
void Hero::onStand(){
    setVelocity(Vec2::ZERO);
    runStandAction();
}

//�������߶���
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