#include "GameUtile.h"

Animation* GameUtile::createNormalAction(const char* format_string, int frame_count, int fps){
    Vector<SpriteFrame*> pFrames;
    //根据编号，格式化帧名，并从帧缓存池中读出相应帧画面，组成帧数组
    for (int i = 0; i < frame_count; ++i){
        const char* ImgName = String::createWithFormat(format_string, i)->getCString();
        SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgName);
        pFrames.insert(i, pFrame);
    }

    //将帧数组创建为动画
    return Animation::createWithSpriteFrames(pFrames, 2.0f / fps);
}

BoundingBox GameUtile::createBoundingBox(Vec2 origin, Size size){
    BoundingBox boundingBox;
    boundingBox.origin = Rect(origin.x, origin.y, size.width, size.height);
    boundingBox.actual = Rect(origin.x + m_bodyBox.actual.origin.x, origin.y + m_bodyBox.actual.origin.y, size.width, size.height);
    return boundingBox;
}