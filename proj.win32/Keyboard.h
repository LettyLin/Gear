/*
    Keyboard�࣬�̳���Layer��
    ���ڼ����¼��Ĵ���
*/
#ifndef _H_KEYBOARD_
#define _H_KEYBOARD_

#include <cocos2d.h>
USING_NS_CC;

class Keyboard : public Layer{
public:
    Keyboard();
    ~Keyboard();
    virtual bool init();
    CREATE_FUNC(Keyboard);

    //�����¼�
    void onKeyPress(EventKeyboard::KeyCode keycode, Event* event);
    //�ͷŰ����¼�
    void onKeyRelease(EventKeyboard::KeyCode keycode, Event* event);
};

#endif