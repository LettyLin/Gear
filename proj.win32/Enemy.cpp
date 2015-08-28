#include "Enemy.h"
#include "Global.h"
#include "Hero.h"

int Enemy::sm_nIndex = 0;

Enemy::Enemy(){}
Enemy::~Enemy(){}

bool Enemy::init(){
    if (!Sprite::init()){
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy.plist", "enemy.png");

    initWithSpriteFrameName("enemy_normal.png");

    Animation* stand = createNormalAction("enemy_normal.png", 1, 10);
    setStandAction(RepeatForever::create(Animate::create(stand)));

    setJumpAction(RepeatForever::create(Animate::create(stand)));

    Animation* walk = createNormalAction("enemy_walk_%02d.png", 4, 10);
    setWalkAction(RepeatForever::create(Animate::create(walk)));

    Animation* attackAnimation = createNormalAction("npc_normal.png", 1, 10);
    this->setAttackAction(RepeatForever::create(Animate::create(attackAnimation)));

    Animation* hurtAnimation = createNormalAction("npc_normal.png", 1, 5);
    this->setHurtAction(Sequence::create(Animate::create(hurtAnimation),
        CallFuncN::create(CC_CALLBACK_0(Role::EndHurt, this)),
        NULL));

    Animation* dieAnimation = createNormalAction("npc_normal.png", 1, 10);
    this->setDieAction(Animate::create(attackAnimation));

    m_maxHp = 20;
    m_currentHp = 20;
    m_maxMp = 20;
    m_currentMp = 20;
    m_strenth = 10;
    m_defence = 10;

    m_bodyBox = createBoundingBox(Vec2(0, 0), getContentSize());
    m_eyesightBox = createBoundingBox(Vec2(32, 64), Size(600, 600));

    m_bSeeHero = false;

    m_nIndex = sm_nIndex;
    ++sm_nIndex;

    return true;
}

void Enemy::onStand(){
    if (!m_moveable){
        return;
    }

    setVelocity(Vec2::ZERO);
    Role::onStand();
}

void Enemy::onWalk(){
    if (!m_moveable){
        return;
    }

    setVelocity(Vec2(4, 0));
    Role::onWalk();
}

void Enemy::onJump(){
    if (!m_moveable){
        return;
    }

    if (!m_dropping){
        m_dropping = true;
        setVelocity(Vec2(m_velocity.x, 9));
    }
    Role::onJump();
}

void Enemy::onAttack(){
    if (!m_moveable){
        return;
    }

    Hero* hero = global->hero;
    Rect heroBox = hero->getBodyBox().actual;
    if (m_attackBox.actual.intersectsRect(heroBox)){
        int hurt = m_strenth + rand() % 20 - 10;
        if (rand() % 100 < 5){
            hurt *= 2;
        }
        hero->onHurt(hurt);
    }

    Role::onAttack();
}

void Enemy::onHurt(int hurt){
    if (!m_moveable){
        return;
    }

    int actual_hurt = hurt - (m_defence + rand() % 20 - 10);
    m_currentHp -= actual_hurt;
    Role::onHurt(actual_hurt);

    m_moveable = false;
}

void Enemy::onDie(){
    Role::onDie();
}

void Enemy::die(){
    getParent()->removeChild(this, true);
    global->enemies.eraseObject(this, true);
}

void Enemy::decide(){
    bool lastSeeHero = m_bSeeHero;
    int decide;

    m_bSeeHero = m_eyesightBox.actual.intersectsRect(global->hero->getBodyBox().actual);

    if (m_bSeeHero){
        Point heroPosition = global->hero->getBodyBox().actual.origin;
        Point enemyPosition = getBodyBox().actual.origin;
        if (m_lastCollisionState == ROLE_COLLISION_CORNER){
            decide = rand() % 100;
            if (decide < 90){
                onWalk();
                onJump();
            }
            else if (decide < 95){
                onStand();
            }
            else{
                reverseDisition();
                onWalk();
            }
        }
        if (heroPosition.x - enemyPosition.x > 80){
            decide = rand() % 100;
            if (decide < 97){
                onWalk();
            }
            else{
                onJump();
            }
        }
        else if (heroPosition.x - enemyPosition.x < -80){
            decide = rand() % 100;
            if (decide < 97){
                onWalk();
            }
            else{
                onJump();
            }
        }
        else{
            onStand();
        }
    }

    else if (!m_bSeeHero && lastSeeHero){
        if (getDirection() == ROLE_DIRECTION_LEFT){
            setDirection(ROLE_DIRECTION_RIGHT);
        }
        else{
            setDirection(ROLE_DIRECTION_LEFT);
        }
    }

    else{
        if (m_lastCollisionState & ROLE_COLLISION_BOUNCE){
            reverseDisition();
            onWalk();
        }
        else if (m_lastCollisionState == ROLE_COLLISION_CORNER){
            decide = rand() % 100;
            if (decide < 80){
                onWalk();
                onJump();
            }
            else if (decide < 97){
                reverseDisition();
                onWalk();
            }
            else{
                onStand();
            }
        }

        else{
            decide = rand() % 100;
            if (decide < 90){
                onWalk();
            }
            else if (decide < 95){
                onStand();
            }
            else{
                onJump();
            }
        }
    }

}

void Enemy::reverseDisition(){
    if (getDirection() == ROLE_DIRECTION_LEFT){
        setDirection(ROLE_DIRECTION_RIGHT);
    }
    else{
        setDirection(ROLE_DIRECTION_LEFT);
    }
}

void Enemy::update(){
    if (!m_dropping){
        decide();
    }
    Role::update();
}

void Enemy::updateAllBox(){
    updateBox(m_bodyBox);
    updateBox(m_eyesightBox);
    updateBox(m_attackBox);
}