#ifndef _H_SKILL_
#define _H_SKILL_

#include <cocos2d.h>
USING_NS_CC;

enum eSkillId{
    SKILL_THROW_FIRE
};

enum eSkillType{
    SKILL_TYPE_ATTACK
};

class Skill : public Sprite{
public:
    Skill();
    ~Skill();

    static Skill* create(int skill_id);
    virtual void use();

    CC_SYNTHESIZE(eSkillId, m_skillId, SkillId);
    CC_SYNTHESIZE(eSkillType, m_skillType, SkillType);
    CC_SYNTHESIZE(int, m_skillValue, SkillValue);
    CC_SYNTHESIZE(int, m_mpConsume, MpConsume);
    CC_SYNTHESIZE_RETAIN(Action*, m_skillAction, SkillAction);
};

#endif