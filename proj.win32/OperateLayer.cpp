#include "OperateLayer.h"
#include "Keyboard.h"
#include "Mouse.h"

OperateLayer::OperateLayer(){}
OperateLayer::~OperateLayer(){}

bool OperateLayer::init(){
    if (!Layer::init()){
        return false;
    }

    //添加键盘事件的处理
    Keyboard* keyboard = Keyboard::create();
    addChild(keyboard);

    Mouse* mouse = Mouse::create();
    addChild(mouse);

    return true;
}