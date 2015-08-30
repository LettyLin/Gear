/*
EnterLayer�࣬�̳���Layer��
���ڽ���������Ϣ��ʾ
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

    //���ص�����
    void onMouseMove(Event* event);
private:
    Size m_visibleSize;

    Sprite* m_smallGear;
    MoveTo* m_pMoveToMenuItem[4];
};

#endif
