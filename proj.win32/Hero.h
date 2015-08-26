/*
    Hero�࣬�̳���Role��
    ���ڴ������ǵĽ���
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

    //�������߶���
    void onWalk();
    //����վ������
    void onStand();
    //������Ծ����
    void onJump();

    void onAttack();
    
    void onTalk();
    //Add other actions here
};

#endif