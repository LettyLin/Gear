/*
    Hero类，继承自Role类
    用于处理主角的交互
*/
#ifndef _H_HERO_
#define _H_HERO_

#include "Role.h"
#include "Tool.h"
#include "Skill.h"

class Backpack;

class Hero : public Role{
public:
    Hero();
    virtual ~Hero();
    virtual bool init();
    CREATE_FUNC(Hero);

    void Inherit(Hero* hero);

    CC_SYNTHESIZE(BoundingBox, m_attackBox, AttackBox);
    CC_SYNTHESIZE(BoundingBox, m_talkingBox, TalkingBox);

    virtual void onWalk();
    virtual void onStand();
    virtual void onJump();
    virtual void onDrop();
    virtual void onCrouch();
    virtual void onStandup();
    virtual void onAttack();
    virtual void onWalkAttack();
    virtual void onJumpAttack();
    virtual void onHurt(int hurt);
    virtual void onDie();
    virtual void onTalk();
    //Add other actions here

    virtual void die();

    void AddHp(int dirta_hp);

    void GetTool(int tool_id);
    void UseTool(int tool_id);

    void GetSkill(int skill_id);
    void UseSkill(int skill_id);

    void ShowProperties();
    void ShowBackpack();
    void ShowSkillList();

    void CheckAttack(int base_hurt);
    void CheckKeyState();

    virtual void EnableMoveable();

    virtual void updateAllBox();

    CC_SYNTHESIZE(Vector<Tool*>, m_tools, Tools);
    CC_SYNTHESIZE(Vector<Skill*>, m_skills, Skills);

    Backpack* backpack;
};

#endif