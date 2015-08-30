#pragma once
#ifndef _BUTTON_LAYER_H_
#define _BUTTON_LAYER_H_

#include <cocos2d.h>
USING_NS_CC;

class ButtonLayer :public Layer
{
public:
    ButtonLayer();
    ~ButtonLayer();
    virtual bool init();
    CREATE_FUNC(ButtonLayer);

    void BrightBackpack();
    void UnBrightBackpack();
    void BrightSkilllist();
    void UnBrightSkilllist();
    void BrightProperty();
    void UnBrightProperty();

private:
    Sprite* property_hover;
    Sprite* goods_hover;
    Sprite* skills_hover;
};
#endif