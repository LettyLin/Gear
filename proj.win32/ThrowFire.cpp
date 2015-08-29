#include "ThrowFire.h"
#include "Global.h"
#include "GameUtile.h"

ThrowFire::ThrowFire(){}
ThrowFire::~ThrowFire(){}

bool ThrowFire::init(){
    if (!Sprite::init()){
        return false;
    }

    m_skillType = SKILL_TYPE_ATTACK;
    m_skillValue = 20;

    Animation* throwFireAction = GameUtile::createNormalAction("hero_specialattack%02d.png", 13, 20);
    setSkillAction(Sequence::create(Animate::create(throwFireAction),
        CallFuncN::create(CC_CALLBACK_0(ThrowFire::createFire, this, m_skillValue)),
        CallFuncN::create(CC_CALLBACK_0(ThrowFire::EndSkill, this)),
        NULL));
}

void ThrowFire::createFire(int base_hurt){

}