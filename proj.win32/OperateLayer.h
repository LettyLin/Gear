/*
    OperateLayer��, �̳���Layer��
    ���ڽ��������ڴ˻����Ͽ���������Ӽ��̣���꣬�����������ˣ��Լ�����cocos2d֧�ֵĽ���ģʽ
*/

#ifndef _H_OPERATE_LAYER_
#define _H_OPERATE_LAYER_

#include <cocos2d.h>
USING_NS_CC;

class OperateLayer : public Layer{
public:
    OperateLayer();
    ~OperateLayer();
    virtual bool init();
    CREATE_FUNC(OperateLayer);
};

#endif