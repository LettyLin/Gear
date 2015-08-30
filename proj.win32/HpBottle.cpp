#include "HpBottle.h"
#include "Hero.h"
#include "Global.h"

HpBottle::HpBottle(){}
HpBottle::~HpBottle(){}

bool HpBottle::init(){
    if (!Sprite::init()){
        return false;
    }

    initWithFile("hpbottle.png");

    m_toolId = TOOL_HPBOTTLE;
    m_toolType = TOOL_TYPE_ADDHP;
    m_toolValue = 20;

    return true;
}

void HpBottle::use(){
    global->hero->AddHp(m_toolValue);
}