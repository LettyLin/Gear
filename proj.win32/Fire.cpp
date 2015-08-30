#include "Fire.h"
#include "Hero.h"
#include "Enemy.h"
#include "Global.h"

Fire::Fire() : 
m_flyAction(NULL),
m_endAction(NULL)
{}

Fire::~Fire(){
    CC_SAFE_RELEASE_NULL(m_flyAction);
    CC_SAFE_RELEASE_NULL(m_endAction);
}

bool Fire::init(int base_hurt){
    if (!Sprite::init()){
        return false;
    }


    initWithSpriteFrameName("fire00.png");

    Animation* fly = GameUtile::createNormalAction("fire%02d.png", 10, 30);
    setFlyAction(Animate::create(fly));
    Animation* end = GameUtile::createNormalAction("fire_end%02d.png", 4, 20);
    setEndAction(Sequence::create(Animate::create(end),
        CallFuncN::create(CC_CALLBACK_0(Fire::EndFire, this)),
        NULL));

    m_baseHurt = base_hurt;
    m_bodyBox = GameUtile::createBoundingBox(Vec2(0, 0), getContentSize());
    m_velocity = Vec2(10, 0);
    setFlippedX(global->hero->getDirection() == ROLE_DIRECTION_RIGHT);

    m_nTimer = 0;

    scheduleUpdate();

    return true;
}

Fire* Fire::create(int base_hurt){
    Fire* fire = new Fire;
    if (fire != NULL && fire->init(base_hurt)){
        fire->autorelease();
    }
    else{
        delete fire;
        fire = NULL;
    }

    return fire;
}

void Fire::update(float dt){
    if (m_velocity.x == 0){
        return;
    }

    if (isFlippedX()){
        setPosition(getPosition() + m_velocity);
    }
    else{
        setPosition(getPosition() - m_velocity);
    }
    updateBodyBox();
    checkEnemy();

    ++m_nTimer;
    if (m_nTimer > 30){
        runAction(m_endAction);
    }
}

void Fire::updateBodyBox(){
    Vec2 origin = m_bodyBox.origin.origin;
    Size size = m_bodyBox.origin.size;
    if (isFlippedX()){
        m_bodyBox.actual = Rect(origin.x + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    }
    else{
        m_bodyBox.actual = Rect(getContentSize().width - origin.x - size.width + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    }
}

void Fire::checkEnemy(){
    Vector<Enemy*> enemies = global->enemies;

    if (enemies.empty()){
        return;
    }

    Vector<Enemy*>::iterator it = enemies.begin();
    for (; it != enemies.end(); ++it){
        if ((*it)->getState() == ROLE_STATE_DIE){
            continue;
        }
        Rect enemyBox = (*it)->getBodyBox().actual;
        if (enemyBox.intersectsRect(getBodyBox().actual)){
            setVelocity(Vec2(0, 0));
            stopAllActions();
            runAction(m_endAction);
            int hurt = m_baseHurt + rand() % 20 - 10;
            (*it)->onHurt(hurt);
        }
    }
}

void Fire::EndFire(){
    getParent()->removeChild(this);
}