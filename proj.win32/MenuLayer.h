#ifndef _H_MENU_LAYER_
#define _H_MENU_LAYER_

#include <cocos2d.h>
USING_NS_CC;

class MenuLayer :public Layer
{
public:
    MenuLayer();
    ~MenuLayer();
    virtual bool init();
    CREATE_FUNC(MenuLayer);
    void changeScene();
    void onMouseMove(Event* event);
    void saveGame();
    void readGame();
    void musicON();
    void musicOFF();
    void returnGame();
    void exitGame();

private:
    Menu* menu0;
    Size m_visibleSize;
    Sprite* m_smallGear;
    MoveTo* m_pMoveToMenuItem[4];
};

#endif