#include "Global.h"
#include "Hero.h"
#include "NPC.h"
#include "Enemy.h"
#include "MapLayer.h"
#include "EnterScene.h"
#include "GameScene.h"

DECLARE_SINGLETON_MEMBER(Global)

//���캯������ʼ��׼��ע�����Ϣ
Global::Global() :
hero(NULL),
npc(NULL),
mapLayer(NULL),
m_bTalking(false)
{}

//�����������ͷ�ע�����Ϣ
Global::~Global(){
    CC_SAFE_RELEASE_NULL(hero);
    hero = NULL;
}

//�Խ����ķ�ʽ�л�����
//����Ϊ�������
void Global::EnterScene(int scene_number){
    Scene* gameScene = GameScene::createScene(scene_number);
    TransitionSlideInR* slide = TransitionSlideInR::create(1.0f, gameScene);
    Director::getInstance()->replaceScene(slide);
}

//��ͼ����ת���߿����꺯����������ײ���
//����Ϊ��ת����ĵ�ͼ����
Point Global::tileCoordForPosition(const Point &position){
    Size tileSize = mapLayer->getMap()->getTileSize();
    int x = static_cast<int>((position.x / tileSize.width));
    int y = static_cast<int>((mapLayer->getMap()->getContentSize().height  - position.y) / tileSize.height);

    return Point(x, y);
}

void Global::CheckCollision(Role* role, const Point &expect_position, Point &final_position, int &dropping){
    final_position = expect_position;

    //���㾫��������������
    Point expect_leftTop = Point(expect_position.x, expect_position.y + role->getBodyBox().origin.size.height);
    Point expect_rightBottom = Point(expect_position.x + role->getBodyBox().origin.size.width, expect_position.y);
    //��ȡ�����ϴ�λ�ô������ײ
    Point last_leftTop = Point(role->getPositionX(), role->getPositionY() + role->getBodyBox().origin.size.height);
    Point last_rightBottom = Point(role->getPositionX() + role->getBodyBox().origin.size.width, role->getPositionY());

    //����������ת��Ϊ��Ƭ����
    Point expect_leftTop_tileCoord = tileCoordForPosition(expect_leftTop);
    Point expect_rightBottom_tileCoord = tileCoordForPosition(expect_rightBottom);
    Point last_leftTop_tileCoord = tileCoordForPosition(last_leftTop);
    Point last_rightBottom_tileCoord = tileCoordForPosition(last_rightBottom);

    //������Ƭ��ͼ��Ϣ
    TMXTiledMap* map = mapLayer->getMap();
    TMXLayer* floor = mapLayer->getFloor();
    TMXLayer* wall = mapLayer->getWall();
    TMXLayer* left_slope = mapLayer->getLeftSlope();
    TMXLayer* right_slope = mapLayer->getRightSlope();

    Size tileSize = map->getTileSize();
    Size mapSize = map->getContentSize();

    //���ǽ��ײ
    for (int y = expect_leftTop_tileCoord.y + 2; y < expect_rightBottom_tileCoord.y; ++y){
        for (int x = expect_leftTop_tileCoord.x; x <= expect_rightBottom_tileCoord.x; ++x){
            Point tileCoord = Point(x, y);
            int tileGid = wall->getTileGIDAt(tileCoord);
            if (tileGid != 0){
                dropping |= ROLE_COLLISION_WALL;
                //������������ǽ��

                if (x == expect_leftTop_tileCoord.x){
                    final_position.x = (expect_leftTop_tileCoord.x + 1) * tileSize.width + 1;
                }
                //����������Ҳ�ǽ��
                else if(x == expect_rightBottom_tileCoord.x){
                    final_position.x = expect_leftTop_tileCoord.x * tileSize.width;
                }
                break;
            }
        }
    }

    //����Ƿ�λ�ڵ����ϻ�������
    for (int x = expect_leftTop_tileCoord.x; x <= expect_rightBottom_tileCoord.x; ++x){
        Point tileCoord = Point(x, expect_rightBottom_tileCoord.y);
        //����
        int floor_tileGid = floor->getTileGIDAt(tileCoord);
        if (floor_tileGid != 0){
            //���þ����ϴε�λ�ô������ײ
            if (expect_rightBottom_tileCoord.y != last_rightBottom_tileCoord.y){
                if (role->getState() == ROLE_STATE_JUMP){
                    if (role->getLastJump().y < mapSize.height - expect_rightBottom_tileCoord.y * tileSize.height){
                        dropping = ROLE_COLLISION_NULL;
                        break;
                    }
                }
                dropping |= ROLE_COLLISION_FLOOR;
                final_position.y = mapSize.height - expect_rightBottom_tileCoord.y * tileSize.height + 1;
            }
            else if (wall->getTileGIDAt(tileCoord) != 0){
                dropping |= ROLE_COLLISION_WALL;
                if (x == expect_leftTop_tileCoord.x){
                    final_position.x = (expect_leftTop_tileCoord.x + 1) * tileSize.width + 1;
                }
                else{
                    final_position.x = expect_leftTop_tileCoord.x * tileSize.width;
                }
            }
        }

        //���������ײ
        int lslope_tileGid = left_slope->getTileGIDAt(tileCoord);
        if (lslope_tileGid != 0){
            if (floor_tileGid != 0 && !role->getOnSlope()){
                role->setOnSlope(true);
                role->setSlopeDirection(ROLE_DIRECTION_LEFT);
                dropping = ROLE_COLLISION_SLOPE;
            }
            else if (role->getState() == ROLE_STATE_JUMP){
                if (role->getLastJump().y < mapSize.height - expect_rightBottom_tileCoord.y * tileSize.height){
                    dropping = ROLE_COLLISION_NULL;
                    break;
                }
            }
            else{
                dropping = ROLE_COLLISION_SLOPE;
            }
        }

        int rslope_tileGid = right_slope->getTileGIDAt(tileCoord);
        if (rslope_tileGid != 0){
            if (floor_tileGid != 0 && !role->getOnSlope()){
                role->setOnSlope(true);
                role->setSlopeDirection(ROLE_DIRECTION_RIGHT);
                dropping = ROLE_COLLISION_SLOPE;
            }
            else if (role->getState() == ROLE_STATE_JUMP){
                if (role->getLastJump().y < mapSize.height - expect_rightBottom_tileCoord.y * tileSize.height){
                    dropping = ROLE_COLLISION_NULL;
                    break;
                }
            }
            else{
                dropping = ROLE_COLLISION_SLOPE;
            }
        }
    }

    for (int x = expect_leftTop_tileCoord.x; x <= expect_rightBottom_tileCoord.x; ++x){
        if (left_slope->getTileGIDAt(Point(x, expect_rightBottom_tileCoord.y + 1)) != 0 || right_slope->getTileGIDAt(Point(x, expect_rightBottom_tileCoord.y + 1))){
            if (expect_position.y == map->getContentSize().height - (expect_rightBottom_tileCoord.y + 1) * map->getTileSize().height + 1){
                dropping |= ROLE_COLLISION_SLOPE;
                break;
            }
        }
    }

    if (!(dropping & ROLE_COLLISION_SLOPE) && role->getOnSlope()){
        role->setOnSlope(false);
    }

    if (role->getOnSlope()){
        dropping = ROLE_COLLISION_SLOPE;
        return;
    }

    if (dropping & (ROLE_COLLISION_FLOOR | ROLE_COLLISION_SLOPE)){
        return;
    }

    for (int x = expect_leftTop_tileCoord.x; x <= expect_rightBottom_tileCoord.x; ++x){
        Point tileCoord = Point(x, expect_rightBottom_tileCoord.y + 1);
        int tileGid = floor->getTileGIDAt(tileCoord);
        if (tileGid != 0){
            if (expect_position.y == map->getContentSize().height - (expect_rightBottom_tileCoord.y + 1) * map->getTileSize().height + 1){
                dropping |= ROLE_COLLISION_NULL;
                return;
            }
        }
        
        if (left_slope->getTileGIDAt(tileCoord) != 0 || right_slope->getTileGIDAt(tileCoord)){
            if (expect_position.y == map->getContentSize().height - (expect_rightBottom_tileCoord.y + 1) * map->getTileSize().height + 1){
                dropping |= ROLE_COLLISION_SLOPE;
                return;
            }
        }
    }

    dropping |= ROLE_COLLISION_DROP;
    return;
}

//��⾫�����ͼ��ײ�����ײ
//����Ϊ����⾫������¶��㣬����ߴ磬�Լ��������
//--------��--------��-------��--------��--------��--------
