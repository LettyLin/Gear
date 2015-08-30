#include "Keyboard.h"
#include "Global.h"
#include "Hero.h"
#include "NPC.h"
#include "Tool.h"
#include "Skill.h"

bool Keyboard::m_bKeyState[MAX_CHECK_KEY_NUMBER] = { false };

Keyboard::Keyboard(){
    for (int i = 0; i < MAX_CHECK_KEY_NUMBER; ++i){
        m_bKeyState[i] = false;
    }
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
    if (global->getGamePause() && !(global->getTalking() && keycode == EventKeyboard::KeyCode::KEY_SPACE)){
        return;
    }

    Hero* hero = global->hero;

    if (hero->getState() == ROLE_STATE_ATTACK){
        return;
    }

    //右键
    if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
        if (global->hero->getDropping()){
            hero->setVelocity(Vec2(3, hero->getVelocity().y));
        }
        hero->setDirection(ROLE_DIRECTION_RIGHT);
        hero->onWalk();
        m_bKeyState[KEY_STATE_RIGHT_ARROW] = true;
    }
    //左键
    else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
        if (global->hero->getDropping()){
            hero->setVelocity(Vec2(3, hero->getVelocity().y));
        }
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
        if (global->getTalking()){
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

    else if (keycode == EventKeyboard::KeyCode::KEY_Z){
        hero->UseSkill(SKILL_THROW_FIRE);
        m_bKeyState[KEY_STATE_Z] = true;
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
    else if (keycode == EventKeyboard::KeyCode::KEY_Z){
        m_bKeyState[KEY_STATE_Z] = false;
    }
}

bool Keyboard::getKeyState(eKeyState key){
    return m_bKeyState[key];
}