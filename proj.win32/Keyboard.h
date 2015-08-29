/*
    Keyboard�࣬�̳���Layer��
    ���ڼ����¼��Ĵ���
*/
#ifndef _H_KEYBOARD_
#define _H_KEYBOARD_

#include <cocos2d.h>
USING_NS_CC;

enum eKeyState{
    KEY_STATE_LEFT_ARROW = 0,
    KEY_STATE_RIGHT_ARROW,
    KEY_STATE_UP_ARROW,
    KEY_STATE_DOWN_ARROW,
    KEY_STATE_LEFT_CTRL,
    KEY_STATE_SPACE,
    MAX_CHECK_KEY_NUMBER
};

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

    bool getKeyState(eKeyState key);

private:
    bool m_bKeyState[MAX_CHECK_KEY_NUMBER];
};

#endif