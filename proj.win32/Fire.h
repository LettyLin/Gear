#ifndef _H_FIRE_
#define _H_FIRE_

#include <cocos2d.h>
#include "GameUtile.h"
USING_NS_CC;

class Fire : public Sprite{
public:
    Fire();
    ~Fire();
    virtual bool init(int base_hurt);
    static Fire* create(int base_hurt);

    virtual void update(float dt);
    void updateBodyBox();
    void checkEnemy();
    void EndFire();

    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
    CC_SYNTHESIZE(Vec2, m_velocity, Velocity);
    
private:
    int m_baseHurt;
};

#endif
