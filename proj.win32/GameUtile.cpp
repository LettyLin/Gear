#include "GameUtile.h"
#include "GameScene.h"
#include "Global.h"
#include "MapLayer.h"
#include "GameLayer.h"
#include "UiLayer.h"
#include "Role.h"
#include "Formater.h"
#include "Hero.h"
#include "NPC.h"
#include "Tool.h"
#include "Skill.h"
#include <fstream>

#include <cocos2d.h>
USING_NS_CC;

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
    boundingBox.actual = Rect(origin.x, origin.y, size.width, size.height);
    return boundingBox;
}

//以渐隐的方式切换场景
//参数为场景编号
void GameUtile::EnterScene(int scene_number){
    global->setSceneIndex(scene_number);

    Scene* gameScene = GameScene::createScene(scene_number);
    TransitionSlideInR* slide = TransitionSlideInR::create(1.0f, gameScene);
    Director::getInstance()->replaceScene(slide);
}

void GameUtile::EnterSceneWithFile(int scene_number, const char* file_name){
    global->setSceneIndex(scene_number);

    Scene* gameScene = GameScene::createSceneWithFile (scene_number, file_name);
    TransitionSlideInR* slide = TransitionSlideInR::create(1.0f, gameScene);
    Director::getInstance()->replaceScene(slide);
}

//地图坐标转换瓦块坐标函数，用于碰撞检测
//参数为带转换点的地图坐标
Point GameUtile::tileCoordForPosition(const Point &position){
    Size tileSize = Size(32, 32);
    int x = static_cast<int>((position.x / tileSize.width));
    int y = static_cast<int>((global->mapLayer->getMap()->getContentSize().height - position.y) / tileSize.height);

    return Point(x, y);
}

void GameUtile::CheckCollision(Role* role, const Point &expect_position, Point &final_position, int &dropping){
    final_position = expect_position;

    //计算精灵两个顶点坐标
    Point expect_leftTop = Point(expect_position.x, expect_position.y + role->getBodyBox().origin.size.height);
    Point expect_rightBottom = Point(expect_position.x + role->getBodyBox().origin.size.width, expect_position.y);
    //获取精灵上次位置处理角碰撞
    Point last_leftTop = Point(role->getBodyBox().actual.origin.x, role->getBodyBox().actual.origin.y + role->getBodyBox().origin.size.height);
    Point last_rightBottom = Point(role->getBodyBox().actual.origin.x + role->getBodyBox().origin.size.width, role->getBodyBox().actual.origin.y);

    //将精灵坐标转换为瓦片坐标
    Point expect_leftTop_tileCoord = tileCoordForPosition(expect_leftTop);
    Point expect_rightBottom_tileCoord = tileCoordForPosition(expect_rightBottom);
    Point last_leftTop_tileCoord = tileCoordForPosition(last_leftTop);
    Point last_rightBottom_tileCoord = tileCoordForPosition(last_rightBottom);

    //保存瓦片地图信息
    TMXTiledMap* map = global->mapLayer->getMap();
    TMXLayer* floor = global->mapLayer->getFloor();
    TMXLayer* wall = global->mapLayer->getWall();
    TMXLayer* left_slope = global->mapLayer->getLeftSlope();
    TMXLayer* right_slope = global->mapLayer->getRightSlope();

    Size tileSize = map->getTileSize();
    Size mapSize = map->getContentSize();

    //检测墙碰撞
    for (int y = expect_leftTop_tileCoord.y + 2; y < expect_rightBottom_tileCoord.y; ++y){
        for (int x = expect_leftTop_tileCoord.x; x <= expect_rightBottom_tileCoord.x; ++x){
            Point tileCoord = Point(x, y);
            int tileGid = wall->getTileGIDAt(tileCoord);
            if (tileGid != 0){
                dropping |= ROLE_COLLISION_WALL;
                //如果碰到了左侧墙壁

                if (x == expect_leftTop_tileCoord.x){
                    final_position.x = (expect_leftTop_tileCoord.x + 1) * tileSize.width + 1;
                }
                //如果碰到了右侧墙壁
                else if (x == expect_rightBottom_tileCoord.x){
                    final_position.x = expect_leftTop_tileCoord.x * tileSize.width - 1;
                }
                break;
            }
        }
    }

    //检测是否位于地面上或坡面上
    for (int x = expect_leftTop_tileCoord.x; x <= expect_rightBottom_tileCoord.x; ++x){
        Point tileCoord = Point(x, expect_rightBottom_tileCoord.y);
        //地面
        int floor_tileGid = floor->getTileGIDAt(tileCoord);
        if (floor_tileGid != 0){
            //利用精灵上次的位置处理角碰撞
            if (expect_rightBottom_tileCoord.y != last_rightBottom_tileCoord.y){
                if (!(role->getVelocity().y > 0)){
                    dropping |= ROLE_COLLISION_FLOOR;
                    final_position.y = mapSize.height - expect_rightBottom_tileCoord.y * tileSize.height + 1;
                }
                else{
                    dropping = ROLE_COLLISION_NULL;
                }
                break;
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

        //检测坡面碰撞
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

void GameUtile::Pause(){
    global->setGamePause(true);
    Sprite* gray = Sprite::create("gray.png");
    gray->setAnchorPoint(Vec2::ZERO);
    gray->setTag(PAUSE_BACK_GRAY);
    global->uiLayer->addChild(gray, 100);
}

void GameUtile::Continue(){
    global->uiLayer->removeChildByTag(PAUSE_BACK_GRAY);
    global->setGamePause(false);
}

void GameUtile::Save(int save_index){
    std::string saveName = String::createWithFormat("Save%d.save", save_index)->getCString();

    std::ofstream Saver(saveName);
    CC_ASSERT(Saver.is_open());

    Hero* hero = global->hero;

    Saver << "Scene = " << global->getSceneIndex() << std::endl;
    Saver << "Point = " << Formater::PointToString(hero->getPosition()) << std::endl;
    Saver << "TalkingTimes = " << global->npc->getTalkingTimes() << std::endl;
    Saver << "CurrentHp = " << hero->getCurrentHp() << std::endl;
    Saver << "MaxHp = " << hero->getMaxHp() << std::endl;
    Saver << "CurrentMp = " << hero->getCurrentMp() << std::endl;
    Saver << "MaxMp = " << hero->getMaxMp() << std::endl;
    Saver << "Strenth = " << hero->getStrenth() << std::endl;
    Saver << "Defence = " << hero->getDefence() << std::endl;
    Saver << "Velocity = " << hero->getMoveVelocity() << std::endl;
    Saver << "Direction = " << hero->getDirection() << std::endl;
    Saver << "Tools = {" << std::endl;
    for (Tool* tool : hero->getTools()){
        Saver << "id = " << tool->getToolId() << std::endl;
    }
    Saver << "}" << std::endl;
    Saver << "Skills = {" << std::endl;
    for (Skill* skill : hero->getSkills()){
        Saver << "id = " << skill->getSkillId() << std::endl;
    }
    Saver << "}" << std::endl;

    Saver.close();
}

void GameUtile::Load(int save_index){
    std::string saveName = String::createWithFormat("Save%d.save", save_index)->getCString();
    std::ifstream Reader(saveName);
    if (!Reader.is_open()){
        return;
    }

    std::string buffer;
    std::string discard;
    Reader >> buffer;
    Reader >> discard;
    CC_ASSERT(buffer == "Scene");
    Reader >> buffer;

    int scene_index = Formater::getInt(buffer);

    EnterSceneWithFile(scene_index, saveName.c_str());
}

bool GameUtile::StringToWString(const std::string &str, std::wstring &wstr)
{
    int nLen = (int)str.length();
    wstr.resize(nLen, ' ');
    int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);
    if (nResult == 0)
    {
        return FALSE;
    }
    return TRUE;
}

bool GameUtile::WStringToString(const std::wstring &wstr, std::string &str)
{
    int nLen = (int)wstr.length();
    str.resize(nLen, ' ');
    int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
    if (nResult == 0)
    {
       return FALSE;
    }
    return TRUE;
}

std::string GameUtile::WideByte2UTF8(const std::wstring& text)
{
    int asciisize = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), NULL, 0, NULL, NULL);
    if (asciisize == ERROR_NO_UNICODE_TRANSLATION ||
        asciisize == 0)
    {
        return std::string();
    }

    char* resultstring = new char[asciisize];
    int convresult = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), resultstring, asciisize, NULL, NULL);

    if (convresult != asciisize)
    {
        return std::string();
    }

    std::string buffer(resultstring, convresult);
    delete[] resultstring;
    return buffer;
}