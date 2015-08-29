#include "Keyboard.h"
#include "Global.h"
#include "Hero.h"
#include "NPC.h"

Keyboard::Keyboard(){
    for (int key = 0; key < MAX_CHECK_KEY_NUMBER; ++key){
        m_bKeyState[key] = false;
    }
    global->keyLayer = this;
}
Keyboard::~Keyboard(){}

bool Keyboard::init(){
    if (!Layer::init()){
        return false;
    }

    //增加并绑定键盘的按下和释放事件
    EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Keyboard::onKeyPress, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Keyboard::onKeyRelease, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

//按下键盘
void Keyboard::onKeyPress(EventKeyboard::KeyCode keycode, Event* event){
    Hero* hero = global->hero;

    //右键
    if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
        hero->setDirection(ROLE_DIRECTION_RIGHT);
        hero->onWalk();
        m_bKeyState[KEY_STATE_RIGHT_ARROW] = true;
    }
    //左键
    else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
        hero->setDirection(ROLE_DIRECTION_LEFT);
        hero->onWalk();
        m_bKeyState[KEY_STATE_LEFT_ARROW] = true;
    }
    //上键
    else if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW){
        hero->onJump();
        m_bKeyState[KEY_STATE_UP_ARROW] = true;
    }

    else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW){
        hero->onCrouch();
        m_bKeyState[KEY_STATE_DOWN_ARROW] = true;
    }
    
    else if (keycode == EventKeyboard::KeyCode::KEY_SPACE){
        if (global->IsTalking()){
            global->npc->continueTalking();
        }
        else{
            hero->onTalk();
        }
        m_bKeyState[KEY_STATE_SPACE] = true;
    }

    else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_CTRL){
        if (hero->getState() == ROLE_STATE_JUMP){
            hero->onJumpAttack();
        }
        if (hero->getState() == ROLE_STATE_WALK){
            hero->onWalkAttack();
        }
        else{
            hero->onAttack();
        }
        m_bKeyState[KEY_STATE_LEFT_CTRL] = true;
    }

    //Add other keycodes here

}

//释放按键
void Keyboard::onKeyRelease(EventKeyboard::KeyCode keycode, Event* event){
    Hero* hero = global->hero;

    if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
        m_bKeyState[KEY_STATE_LEFT_ARROW] = false;
        hero->CheckKeyState();
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
        m_bKeyState[KEY_STATE_RIGHT_ARROW] = false;
        hero->CheckKeyState();
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW){
        hero->onStandup();
        m_bKeyState[KEY_STATE_DOWN_ARROW] = false;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW){
        m_bKeyState[KEY_STATE_UP_ARROW] = false;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_SPACE){
        m_bKeyState[KEY_STATE_SPACE] = false;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_CTRL){
        m_bKeyState[KEY_STATE_LEFT_CTRL] = false;
    }
}

bool Keyboard::getKeyState(eKeyState key){
    return m_bKeyState[key];
}