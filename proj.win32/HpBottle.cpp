#include "HpBottle.h"

HpBottle::HpBottle(){}
HpBottle::~HpBottle(){}

bool HpBottle::init(){
    if (!Sprite::init()){
        return false;
    }

    initWithFile("enter_geer_small");

    m_toolId = TOOL_HPBOTTLE;
    m_toolType = TOOL_TYPE_ADDHP;
    m_toolValue = 20;

    return true;
}