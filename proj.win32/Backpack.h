#pragma once

#ifndef _BACK_PACK_H_
#define _BACK_PACK_H_
#include "Global.h"
#include "Tool.h"
#include "cocos2d.h"
USING_NS_CC;
class Backpack :public Sprite
{
public:
    Backpack();
    ~Backpack();
    virtual bool init();
    CREATE_FUNC(Backpack);

    void addItem(Tool* sprite);
    int getTag(Point point);

    void ResetPosition();

    Vec2 m_Point[9];
private:
    int m_nTimer;

};

#endif