#include "Skill.h"
#include "ThrowFire.h"

Skill::Skill() : m_skillAction(NULL)
{}

Skill::~Skill(){
    CC_SAFE_RELEASE_NULL(m_skillAction);
}

Skill* Skill::create(int skill_id){
    switch (skill_id){
    case SKILL_THROW_FIRE:
        Skill* skill = ThrowFire::create();
        skill->retain();
        return skill;
    }

    return NULL;
}

void Skill::use(){
}