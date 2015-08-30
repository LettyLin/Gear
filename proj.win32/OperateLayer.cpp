#include "OperateLayer.h"
#include "Keyboard.h"
#include "Mouse.h"

OperateLayer::OperateLayer(){}
OperateLayer::~OperateLayer(){}

bool OperateLayer::init(){
    if (!Layer::init()){
        return false;
    }

    //��Ӽ����¼��Ĵ���
    Keyboard* keyboard = Keyboard::create();
    addChild(keyboard);

    Mouse* mouse = Mouse::create();
    addChild(mouse);

    return true;
}