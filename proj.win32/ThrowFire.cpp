#include "ThrowFire.h"
#include "Global.h"
#include "Fire.h"
#include "Hero.h"
#include "GameUtile.h"

ThrowFire::ThrowFire(){}
ThrowFire::~ThrowFire(){}

bool ThrowFire::init(){
    if (!Sprite::init()){
        return false;
    }

    m_skillId = SKILL_THROW_FIRE;
    m_skillType = SKILL_TYPE_ATTACK;
    m_skillValue = 400;
    m_mpConsume = 20;

    Animation* throwFireAction = GameUtile::createNormalAction("hero_throwfire%02d.png", 7, 20);
    Animation* throwFireEndAction = GameUtile::createNormalAction("hero_throwfire_end%02d.png", 6, 20);
    setSkillAction(Sequence::create(Animate::create(throwFireAction),
        CallFuncN::create(CC_CALLBACK_0(ThrowFire::createFire, this)),
        Animate::create(throwFireEndAction),
        CallFuncN::create(CC_CALLBACK_0(ThrowFire::EndSkill, this)),
        NULL));
}

void ThrowFire::use(){
    Hero *hero = global->hero;
    hero->setMoveable(false);
    hero->setVelocity(Vec2::ZERO);
    hero->setState(ROLE_STATE_ATTACK);
    hero->setCurrentMp(hero->getCurrentMp() - m_mpConsume);
    hero->stopAllActions();
    hero->runAction(getSkillAction());
}

void ThrowFire::createFire(){
    Fire* fire = Fire::create(m_skillValue);
    global->hero->getParent()->addChild(fire);
    if (global->hero->getDirection() == ROLE_DIRECTION_RIGHT){
        fire->setPosition(global->hero->getBodyBox().actual.origin +Vec2(85, 50));
    }
    else{
        fire->setPosition(global->hero->getBodyBox().actual.origin + Vec2(5, 50));
    }
    fire->runAction(fire->getFlyAction());
}

void ThrowFire::EndSkill(){
    global->hero->setMoveable(true);
    global->hero->CheckKeyState();
}