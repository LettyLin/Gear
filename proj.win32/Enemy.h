#ifndef _H_ENEMY_
#define _H_ENEMY_

#include "Role.h"
class Enemy : public Role{
public:
    Enemy();
    ~Enemy();
    virtual bool init();
    CREATE_FUNC(Enemy);
    
    CC_SYNTHESIZE(BoundingBox, m_eyesightBox, EyesightBox);
    CC_SYNTHESIZE(BoundingBox, m_attackBox, AttackBox);

    virtual void onStand();
    virtual void onWalk();
    virtual void onJump();
    virtual void onAttack();
    virtual void onHurt(int hurt);
    virtual void onDie();

    virtual void update();
    virtual void updateAllBox();

    virtual void die();

    virtual void decide();

    virtual void reverseDisition();

private:
    bool m_bSeeHero;
    int m_nIndex;

    static int sm_nIndex;
};

#endif