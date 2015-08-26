/*
    MapLayer�࣬�̳���Layer��
    ʵ�ֵ�ͼ������͸���
*/
#ifndef _H_MAP_LAYER_
#define _H_MAP_LAYER_

#include <cocos2d.h>
USING_NS_CC;

class MapLayer : public Layer{
public:
    //���ݵ�ͼ��������ͼ��
    static MapLayer* create(const char* map_name);
    
    MapLayer();
    ~MapLayer();
    virtual bool init(const char* map_name);
    void LoadMapFromFile(const char* map_name);

    void addFrontSprite(const char* front_sprite_name, int z_order);
    void addScrollSprite(const char* scroll_sprite_name, int z_order, int tag);

    //�����ͼ����ײ���Լ�����ײ���
    CC_SYNTHESIZE(TMXTiledMap*, m_pMap, Map);
    CC_SYNTHESIZE(TMXLayer*, m_pFloor, Floor);
    CC_SYNTHESIZE(TMXLayer*, m_pWall, Wall);
    
    CC_SYNTHESIZE(int, m_nScrollSpriteTag, ScrollSpriteTag);
    CC_SYNTHESIZE(bool, m_bHasScrollFront, HasScrollFront);

    //���µ�ͼ
    void update();

private:
    //��ָ���ļ��м��ص�ͼ
};

#endif