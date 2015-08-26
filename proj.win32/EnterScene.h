/*
    EnterScene类，继承自Scene类
    由EnterLayer组成，用于初始界面的显示
*/

#ifndef _H_ENTER_SCENE_
#define _H_ENTER_SCENE_

#include <cocos2d.h>
USING_NS_CC;

class EnterScene : public Scene{
public:
    static Scene* createScene();
};

#endif