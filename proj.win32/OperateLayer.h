/*
    OperateLayer类, 继承自Layer类
    用于交互处理，在此基础上可以任意添加键盘，鼠标，触屏，操作杆，以及其它cocos2d支持的交互模式
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