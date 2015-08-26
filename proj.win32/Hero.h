/*
    Hero类，继承自Role类
    用于处理主角的交互
*/
#ifndef _H_HERO_
#define _H_HERO_

#include "Role.h"

class Hero : public Role{
public:
    Hero();
    virtual ~Hero();
    virtual bool init();
    CREATE_FUNC(Hero);

    CC_SYNTHESIZE(BoundingBox, m_attackBox, AttackBox);
    CC_SYNTHESIZE(BoundingBox, m_talkingBox, TalkingBox);

    virtual void update();

    //调用行走动作
    void onWalk();
    //调用站立动作
    void onStand();
    //调用跳跃动画
    void onJump();

    void onAttack();
    
    void onTalk();
    //Add other actions here
};

#endif