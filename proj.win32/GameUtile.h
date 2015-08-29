#ifndef _H_GAMEUTILE_
#define _H_GAMEUTILE_

#include <cocos2d.h>
USING_NS_CC;

//定义盒子模型用于进行攻击，对话等范围判定
struct BoundingBox {
    //绝对位置的盒子模型
    Rect actual;
    //相对位置的盒子模型
    Rect origin;
};

class GameUtile{
public:
    //创建常规动画（帧名相同，编号从0开始）
    static Animation* createNormalAction(const char* format_string, int frame_count, int fps);

    //创建盒子
    static BoundingBox createBoundingBox(Vec2 origin, Size size);
};

#endif