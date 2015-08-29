#include "Tool.h"
#include "Global.h"
#include "Hero.h"
#include "HpBottle.h"

Tool::Tool(){}
Tool::~Tool(){}

Tool* Tool::create(int tool_id){
    switch (tool_id){
    case TOOL_HPBOTTLE:
        Tool* hpBottle = HpBottle::create();
        hpBottle->retain();
        return hpBottle;
        break;
    }
    return NULL;
}

void Tool::use(){
    switch (m_toolType){
    case TOOL_TYPE_ADDHP:
        global->hero->AddHp(m_toolValue);
        break;

    default:
        break;
    }
}