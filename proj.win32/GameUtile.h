#ifndef _H_GAMEUTILE_
#define _H_GAMEUTILE_

#include <string>
#include <cocos2d.h>
USING_NS_CC;

class Role;

enum {
    PAUSE_BACK_GRAY = 100
};

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

    static void EnterScene(int scene_number);
    static void EnterSceneWithFile(int scene_number, const char* file_name);

    //地图坐标转换瓦块坐标函数，用于碰撞检测
    static Point tileCoordForPosition(const Point &position);

    //碰撞检测函数
    static void CheckCollision(Role* role, const Point &expect_position, Point &final_position, int &dropping);

    static void Pause();
    static void Continue();

    static void Save(int save_index);
    static void Load(int save_index);

    static bool WStringToString(const std::wstring &wstr, std::string &str);
    static bool StringToWString(const std::string &str, std::wstring &wstr);
    static  std::string WideByte2UTF8(const std::wstring& text);
};

#endif