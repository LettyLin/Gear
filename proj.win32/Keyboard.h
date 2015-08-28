/*
    Keyboard类，继承自Layer类
    用于键盘事件的处理
*/
#ifndef _H_KEYBOARD_
#define _H_KEYBOARD_

#include <cocos2d.h>
USING_NS_CC;

enum eKeyState{
    KEY_STATE_LEFT_ARROW,
    KEY_STATE_RIGHT_ARROW,
};

class Keyboard : public Layer{
public:
    Keyboard();
    ~Keyboard();
    virtual bool init();
    CREATE_FUNC(Keyboard);

    //按键事件
    void onKeyPress(EventKeyboard::KeyCode keycode, Event* event);
    //释放按键事件
    void onKeyRelease(EventKeyboard::KeyCode keycode, Event* event);
};

#endif