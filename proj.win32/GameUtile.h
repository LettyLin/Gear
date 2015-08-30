#ifndef _H_GAMEUTILE_
#define _H_GAMEUTILE_

#include <string>
#include <cocos2d.h>
USING_NS_CC;

class Role;

enum {
    PAUSE_BACK_GRAY = 100
};

//�������ģ�����ڽ��й������Ի��ȷ�Χ�ж�
struct BoundingBox {
    //����λ�õĺ���ģ��
    Rect actual;
    //���λ�õĺ���ģ��
    Rect origin;
};

class GameUtile{
public:
    //�������涯����֡����ͬ����Ŵ�0��ʼ��
    static Animation* createNormalAction(const char* format_string, int frame_count, int fps);

    //��������
    static BoundingBox createBoundingBox(Vec2 origin, Size size);

    static void EnterScene(int scene_number);
    static void EnterSceneWithFile(int scene_number, const char* file_name);

    //��ͼ����ת���߿����꺯����������ײ���
    static Point tileCoordForPosition(const Point &position);

    //��ײ��⺯��
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