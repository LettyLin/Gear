#pragma once
#ifndef _UI_LAYER_H_
#define _UI_LAYER_H_

#include <cocos2d.h>
USING_NS_CC;

class UiLayer :public Layer
{
public:
    UiLayer();
    ~UiLayer();
    virtual bool init();
    CREATE_FUNC(UiLayer);
};
#endif
