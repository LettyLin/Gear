/*
    GameScene�࣬�̳���Scene��
    ��GameLayer, OperateLayer, UiLayer��ɣ�����Ϸ�ĺ��ĳ���
*/

#ifndef _H_GAME_SCENE_
#define _H_GAME_SCENE_

#include <cocos2d.h>
USING_NS_CC;

class GameScene : public Scene{
public:
    //ѡ����Ҫ�����ĳ���
    static Scene* createScene(int which_scene);
    static Scene* createSceneWithFile(int which_scene, const char* file_name);
};

#endif