/*
    Hero类，继承自Role类
    用于处理主角的交互
*/
#ifndef _H_HERO_
#define _H_HERO_

#include "Role.h"

class Tool;

class Hero : public Role{
public:
    Hero();
    virtual ~Hero();
    virtual bool init();
    CREATE_FUNC(Hero);

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

    void AddHp(int dirta_hp);

    void GetTool(int tool_id);
    void UseTool(int tool_id);

    void ShowProperties();
    void ShowBackpack();
    void ShowSkillList();

    void CheckAttack(int base_hurt);
    void CheckKeyState();

    virtual void EnableMoveable();

    virtual void updateAllBox();

private:
    Vector<Tool*> m_tools;
};

#endif