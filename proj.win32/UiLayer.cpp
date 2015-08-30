#include "UiLayer.h"
#include "StateBar.h"
#include "ButtonLayer.h"
#include "MenuLayer.h"
#include "Hero.h"


UiLayer::UiLayer()
{
}


UiLayer::~UiLayer()
{
}


bool UiLayer::init(){
	if (!Layer::init())
	{
		return false;
	}

    StateBar* stateBar = StateBar::create();
    addChild(stateBar);

    //MenuLayer* menu = MenuLayer::create();
    //addChild(menu);

    ButtonLayer* buttonLayer = ButtonLayer::create();
    addChild(buttonLayer);

	return true;
}