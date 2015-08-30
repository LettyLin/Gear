#include "Enemy.h"
#include "GameUtile.h"
#include "Global.h"
#include "Hero.h"

int Enemy::sm_nIndex = 0;

Enemy::Enemy(){}
Enemy::~Enemy(){}

bool Enemy::init(){
    if (!Sprite::init()){
        return false;
    }

    initWithSpriteFrameName("enemy_stand00.png");

    Animation* stand = GameUtile::createNormalAction("enemy_stand%02d.png", 6, 10);
    setStandAction(RepeatForever::create(Animate::create(stand)));

    Animation* jumpOrWalk = GameUtile::createNormalAction("enemy_walk%02d.png", 7, 10);
    setWalkAction(RepeatForever::create(Animate::create(jumpOrWalk)));
    setJumpAction(Sequence::create(Animate::create(jumpOrWalk),
        CallFuncN::create(CC_CALLBACK_0(Enemy::EnableMoveable, this)),
        NULL));


    //setDropAction(RepeatForever::create(Animate::create(stand)));

    Animation* attackAnimation = GameUtile::createNormalAction("enemy_attack%02d.png", 10, 10);
    this->setAttackAction(Sequence::create(Animate::create(attackAnimation), 
       CallFuncN::create(CC_CALLBACK_0(Enemy::EnableMoveable, this)),
       NULL));

    Animation* hurtAnimation = GameUtile::createNormalAction("enemy_die%02d.png", 5, 20);
    this->setHurtAction(Sequence::create(Animate::create(hurtAnimation),
        CallFuncN::create(CC_CALLBACK_0(Role::EnableMoveable, this)),
        NULL));

    Animation* standupAnimation = GameUtile::createNormalAction("enemy_standup%02d.png", 10, 10);
    this->setStandupAction(Sequence::create(Animate::create(attackAnimation),
        CallFuncN::create(CC_CALLBACK_0(Enemy::EnableMoveable, this)),
        NULL));

    Animation* dieAnimation = GameUtile::createNormalAction("enemy_die%02d.png", 7, 20);
    this->setDieAction(Animate::create(dieAnimation));

    m_maxHp = 20;
    m_currentHp = 20;
    m_maxMp = 20;
    m_currentMp = 20;
    m_strenth = 10;
    m_defence = 10;
    m_moveVelocity = 4;

    m_bodyBox = GameUtile::createBoundingBox(Vec2(0, 0), getContentSize());
    m_eyesightBox = GameUtile::createBoundingBox(Vec2(32, 64), Size(600, 600));
    m_attackBox = GameUtile::createBoundingBox(Vec2(getContentSize().width / 2, -50), Size(200, getContentSize().height + 100));

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

    setVelocity(Vec2(m_moveVelocity, 0));
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
        int hurt = m_strenth + rand() % 200 - 10;
        if (rand() % 100 < 5){
            hurt *= 2;
        }
        hero->onHurt(hurt);
    }

    Role::onAttack();
}

void Enemy::onHurt(int hurt){
    int actual_hurt = hurt - (m_defence + rand() % 20 - 10);
    m_currentHp -= actual_hurt;
    Role::onHurt(actual_hurt);
}

void Enemy::onDie(){
    //runDieAction();
    Role::onDie();
}

void Enemy::die(){
    m_moveable = false;

    /*getParent()->removeChild(this, true);
    global->enemies.eraseObject(this, true);*/
}

void Enemy::decide(){
    if (!m_moveable){
        return;
    }

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