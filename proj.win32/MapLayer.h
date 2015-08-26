/*
    MapLayer类，继承自Layer类
    实现地图的载入和更新
*/
#ifndef _H_MAP_LAYER_
#define _H_MAP_LAYER_

#include <cocos2d.h>
USING_NS_CC;

class MapLayer : public Layer{
public:
    //根据地图名创建地图层
    static MapLayer* create(const char* map_name);
    
    MapLayer();
    ~MapLayer();
    virtual bool init(const char* map_name);
    void LoadMapFromFile(const char* map_name);

    void addFrontSprite(const char* front_sprite_name, int z_order);
    void addScrollSprite(const char* scroll_sprite_name, int z_order, int tag);

    //保存地图和碰撞层以加速碰撞检测
    CC_SYNTHESIZE(TMXTiledMap*, m_pMap, Map);
    CC_SYNTHESIZE(TMXLayer*, m_pFloor, Floor);
    CC_SYNTHESIZE(TMXLayer*, m_pWall, Wall);
    
    CC_SYNTHESIZE(int, m_nScrollSpriteTag, ScrollSpriteTag);
    CC_SYNTHESIZE(bool, m_bHasScrollFront, HasScrollFront);

    //更新地图
    void update();

private:
    //从指定文件中加载地图
};

#endif