/*
EnterLayer类，继承自Layer类
用于进入界面的信息显示
*/
#ifndef _H_ENTER_LAYER_
#define _H_ENTER_LAYER_

#include <cocos2d.h>
USING_NS_CC;

class EnterLayer : public Layer{
public:
    EnterLayer();
    ~EnterLayer();
    virtual bool init();
    CREATE_FUNC(EnterLayer);

    void NewGame(Ref* pSender);
    void LoadGame(Ref* pSender);
    void ExitGame(Ref* pSender);

    virtual void update(float ft);

    //鼠标回调函数
    void onMouseMove(Event* event);
private:
    Size m_visibleSize;

    Sprite* m_smallGear;
    MoveTo* m_pMoveToMenuItem[4];
};

#endif
