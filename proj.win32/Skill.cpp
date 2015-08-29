#include "Skill.h"

Skill::Skill(){}
Skill::~Skill(){}

Skill* Skill::create(int skill_id){
    switch (skill_id){
    case SKILL_THROW_FIRE:
        Skill* skill = 
    }
}

void Skill::use(){
    switch(m_skillType){
    case SKILL_TYPE_ATTACK:
        runAction(m_skillAction);
        break;
    }
}