#pragma once
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include <cocos2d.h>
USING_NS_CC;

class Tool;
class Mouse :public Layer
{
public:
    Mouse();
    ~Mouse();
    virtual bool init();
    CREATE_FUNC(Mouse);

    void onMouseDown(Event* event);
    void onMouseMove(Event* event);
    void onMouseUp(Event* event);

    void dragMouseDown(Event* event);
    void dragMouseMove(Event* event);
    void dragMouseUp(Event* event);

    void setMenuBright(Event* event);

private:

    int m_nMenuUpBounce;

    int m_nPropertyLeftBounce;
    int m_nBackpackLeftBounce;

    bool m_bOnBackpack;
    bool m_bOnProperty;

    Tool* m_currentTool;
    Point m_lastPoint;
};

#endif