/*
    GameScene类，继承自Scene类
    由GameLayer, OperateLayer, UiLayer组成，是游戏的核心场景
*/

#ifndef _H_GAME_SCENE_
#define _H_GAME_SCENE_

#include <cocos2d.h>
USING_NS_CC;

class GameScene : public Scene{
public:
    //选择需要创建的场景
    static Scene* createScene(int which_scene);
    static Scene* createSceneWithFile(int which_scene, const char* file_name);
};

#endif