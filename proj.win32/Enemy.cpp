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

    m_maxHp = 20;
    m_currentHp = 20;

    m_bodyBox = createBoundingBox(Vec2(0, 0), getContentSize());
    m_eyesightBox = createBoundingBox(Vec2(32, 64), Size(600, 600));

    m_bSeeHero = false;

    m_nIndex = sm_nIndex;
    ++sm_nIndex;

    return true;
}

void Enemy::onStand(){
    setVelocity(Vec2::ZERO);
    runStandAction();
}

void Enemy::onWalk(){
    setVelocity(Vec2(3, 0));
    runWalkAction();
}

void Enemy::onJump(){
    if (!m_dropping){
        m_dropping = true;
        setVelocity(Vec2(m_velocity.x, 30));
    }
    runJumpAction();
}
void Enemy::onAttack(){}

void Enemy::onHurt(int hurt){
    m_currentHp -= hurt;
    if (m_currentHp <= 0){
        die();
    }
}

void Enemy::die(){
    getParent()->removeChild(this, true);
    global->enemies.erase(m_nIndex);
}

void Enemy::decide(){
    bool lastSeeHero = m_bSeeHero;
    int decide;

    m_bSeeHero = m_eyesightBox.actual.intersectsRect(global->hero->getBodyBox().actual);

    if (m_bSeeHero){
        Point heroPosition = global->hero->getPosition();
        Point enemyPosition = getPosition();
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
    updateBox(m_eyesightBox);
}