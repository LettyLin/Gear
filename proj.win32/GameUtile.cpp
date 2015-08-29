#include "GameUtile.h"

Animation* GameUtile::createNormalAction(const char* format_string, int frame_count, int fps){
    Vector<SpriteFrame*> pFrames;
    //���ݱ�ţ���ʽ��֡��������֡������ж�����Ӧ֡���棬���֡����
    for (int i = 0; i < frame_count; ++i){
        const char* ImgName = String::createWithFormat(format_string, i)->getCString();
        SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgName);
        pFrames.insert(i, pFrame);
    }

    //��֡���鴴��Ϊ����
    return Animation::createWithSpriteFrames(pFrames, 2.0f / fps);
}

BoundingBox GameUtile::createBoundingBox(Vec2 origin, Size size){
    BoundingBox boundingBox;
    boundingBox.origin = Rect(origin.x, origin.y, size.width, size.height);
    boundingBox.actual = Rect(origin.x + m_bodyBox.actual.origin.x, origin.y + m_bodyBox.actual.origin.y, size.width, size.height);
    return boundingBox;
}