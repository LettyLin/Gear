#include "OperateLayer.h"
#include "Keyboard.h"

OperateLayer::OperateLayer(){}
OperateLayer::~OperateLayer(){}

bool OperateLayer::init(){
    if (!Layer::init()){
        return false;
    }

    //��Ӽ����¼��Ĵ���
    Keyboard* keyboard = Keyboard::create();
    addChild(keyboard);



    return true;
}