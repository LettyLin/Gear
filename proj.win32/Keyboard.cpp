#include "Keyboard.h"
#include "Global.h"
#include "Hero.h"
#include "NPC.h"

Keyboard::Keyboard(){}
Keyboard::~Keyboard(){}

bool Keyboard::init(){
    if (!Layer::init()){
        return false;
    }

    //���Ӳ��󶨼��̵İ��º��ͷ��¼�
    EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Keyboard::onKeyPress, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Keyboard::onKeyRelease, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

//���¼���
void Keyboard::onKeyPress(EventKeyboard::KeyCode keycode, Event* event){
    //�Ҽ�
    if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
        global->hero->setDirection(ROLE_DIRECTION_RIGHT);
        global->hero->onWalk();
    }
    //���
    if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW){
        global->hero->setDirection(ROLE_DIRECTION_LEFT);
        global->hero->onWalk();
    }
    //�ϼ�
    if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW){
        global->hero->onJump();
    }
    
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE){
        if (global->IsTalking()){
            global->npc->continueTalking();
        }
        else{
            global->hero->onTalk();
        }
    }

    if (keycode == EventKeyboard::KeyCode::KEY_LEFT_CTRL){
        global->hero->onAttack();
    }

    //Add other keycodes here

}

//�ͷŰ���
void Keyboard::onKeyRelease(EventKeyboard::KeyCode keycode, Event* event){
    if (!global->hero->getDropping()){
        global->hero->onStand();
    }
    if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
        global->hero->setVelocity(Vec2(0, global->hero->getVelocity().y));
    }
}