#ifndef _H_PROPERTY_
#define _H_PROPERTY_

#include <cocos2d.h>
USING_NS_CC;

class Property : public Sprite{
public:
    Property();
    ~Property();
    virtual bool init();
    CREATE_FUNC(Property);

    void addItem(Label* label);

    void ResetPosition();

    Vec2 m_Point[5];

private:
    int m_nTimer;
};

#endif