#ifndef _H_GAMEUTILE_
#define _H_GAMEUTILE_

#include <cocos2d.h>
USING_NS_CC;

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
};

#endif