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

    void onStand();
    void onWalk();
    void onJump();
    void onHurt(int hurt);
    void onAttack();

    void die();

    void decide();

    void reverseDisition();

    virtual void update();

private:
    bool m_bSeeHero;
    int m_nIndex;

    static int sm_nIndex;
};

#endif