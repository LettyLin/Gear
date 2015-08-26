#include "Global.h"
#include "Hero.h"
#include "NPC.h"
#include "Enemy.h"
#include "MapLayer.h"
#include "EnterScene.h"
#include "GameScene.h"

DECLARE_SINGLETON_MEMBER(Global)

//构造函数，初始化准备注册的信息
Global::Global() :
hero(NULL),
mapLayer(NULL),
m_bTalking(false)
{}

//析构函数，释放注册的信息
Global::~Global(){
    CC_SAFE_RELEASE(hero);
    CC_SAFE_RELEASE(mapLayer);
    hero = NULL;
    mapLayer = NULL;
}

//以渐隐的方式切换场景
//参数为场景编号
void Global::EnterScene(int scene_number){
    Scene* gameScene = GameScene::createScene(scene_number);
    TransitionFade* fade = TransitionFade::create(1.0f, gameScene);
    Director::getInstance()->replaceScene(fade);
}

//地图坐标转换瓦块坐标函数，用于碰撞检测
//参数为带转换点的地图坐标
Point Global::tileCoordForPosition(const Point &position){
    Size tileSize = mapLayer->getMap()->getTileSize();
    int x = static_cast<int>((position.x / tileSize.width));
    int y = static_cast<int>((mapLayer->getMap()->getContentSize().height  - position.y) / tileSize.height);

    return Point(x, y);
}

void Global::CheckCollision(const Point &last_position, const Point &except_position, const Size &size, Point &final_position, int &dropping){
    final_position = except_position;

    //计算精灵四个顶点的坐标
    Point except_leftTop = Point(except_position.x, except_position.y + size.height);
    Point except_rightBottom = Point(except_position.x + size.width, except_position.y);

    Point last_rightBottom = Point(last_position.x + size.width, last_position.y);

    Point except_leftTop_tileCoord = tileCoordForPosition(except_leftTop);
    Point except_rightBottom_tileCoord = tileCoordForPosition(except_rightBottom);

    Point last_rightBottom_tileCoord = tileCoordForPosition(last_rightBottom);

    TMXTiledMap* map = mapLayer->getMap();
    TMXLayer* floor = mapLayer->getFloor();
    TMXLayer* wall = mapLayer->getWall();

    for (int y = except_leftTop_tileCoord.y; y < except_rightBottom_tileCoord.y; ++y){
        for (int x = except_leftTop_tileCoord.x; x <= except_rightBottom_tileCoord.x; ++x){
            Point tileCoord = Point(x, y);
            int tileGid = wall->getTileGIDAt(tileCoord);
            if (tileGid != 0){
                dropping |= ROLE_COLLISION_WALL;
                if (x == except_leftTop_tileCoord.x){
                    final_position.x = (except_leftTop_tileCoord.x + 1) * map->getTileSize().width + 1;
                }
                else{
                    final_position.x = except_leftTop_tileCoord.x * map->getTileSize().width;
                }
                break;
            }
        }
        if (dropping & ROLE_COLLISION_WALL){
            break;
        }
    }

    for (int x = except_leftTop_tileCoord.x; x <= except_rightBottom_tileCoord.x; ++x){
        Point tileCoord = Point(x, except_rightBottom_tileCoord.y);
        int tileGid = floor->getTileGIDAt(tileCoord);
        if (tileGid != 0){
            if (except_rightBottom_tileCoord.y != last_rightBottom_tileCoord.y){
                dropping |= ROLE_COLLISION_FLOOR;
                final_position.y = map->getContentSize().height - except_rightBottom_tileCoord.y * map->getTileSize().height + 1;
                break;
            }
            else if (wall->getTileGIDAt(tileCoord) != 0){
                dropping |= ROLE_COLLISION_WALL;
                if (x == except_leftTop_tileCoord.x){
                    final_position.x = (except_leftTop_tileCoord.x + 1) * map->getTileSize().width + 1;
                }
                else{
                    final_position.x = except_leftTop_tileCoord.x * map->getTileSize().width;
                }
                break;
            }
        }
    }

    for (int x = except_leftTop_tileCoord.x; x <= except_rightBottom_tileCoord.x; ++x){
        Point tileCoord = Point(x, except_rightBottom_tileCoord.y + 1);
        int tileGid = floor->getTileGIDAt(tileCoord);
        if (tileGid != 0){
            if (except_position.y == map->getContentSize().height - (except_rightBottom_tileCoord.y + 1) * map->getTileSize().height + 1){
                dropping |= ROLE_COLLISION_NULL;
                return;
            }
        }
    }

    dropping |= ROLE_COLLISION_DROP;

}

//检测精灵与地图碰撞层的碰撞
//参数为待检测精灵的左下顶点，精灵尺寸，以及重力情况
//--------算--------法-------待--------完--------善--------
