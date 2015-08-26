#include "MapLayer.h"
#include "Global.h"
#include "Hero.h"

MapLayer::MapLayer() :
m_pMap(NULL),
m_pWall(NULL)
{
    //���¹���ĵ�ͼ��ע���global����ʵ��
    if (NULL == global->mapLayer){
        global->mapLayer = this;
    }
}

MapLayer::~MapLayer(){
    /*CC_SAFE_RELEASE_NULL(m_pMap);
    CC_SAFE_RELEASE_NULL(m_pWall);

    global->mapLayer = NULL;*/
}

bool MapLayer::init(const char* map_name){
    if (!Layer::init()){
        return false;
    }

    //LoadMapFromFile(map_name);

    return true;
}

MapLayer* MapLayer::create(const char* map_name){
    //������ͼ��
    MapLayer* mapLayer = new MapLayer;
    //�������ɹ������ڴ潻��cocos2d���Զ�������ƣ����򷵻�NULL
    if (NULL != mapLayer && mapLayer->init(map_name)){
        mapLayer->autorelease();
        return mapLayer;
    }
    else{
        delete mapLayer;
        mapLayer = NULL;
        return NULL;
    }
}

void MapLayer::LoadMapFromFile(const char* map_name){

    //���ص�ͼ
    m_pMap = TMXTiledMap::create(map_name);
    //�ӵ�ͼ�л�ȡ�ذ��
    m_pFloor = m_pMap->getLayer("floor");
    m_pFloor->setVisible(false);
    //�ӵ�ͼ�л�ȡǽ�ڲ�
    m_pWall = m_pMap->getLayer("wall");
    m_pWall->setVisible(false);

    m_pMap->setAnchorPoint(Vec2::ZERO);
    addChild(m_pMap);
}

void MapLayer::addFrontSprite(const char* front_sprite_name, int z_order){
    Sprite* front_sprite = Sprite::create(front_sprite_name);
    front_sprite->setAnchorPoint(Vec2::ZERO);
    front_sprite->setPosition(Vec2::ZERO);
    getParent()->addChild(front_sprite, z_order);
}

void MapLayer::addScrollSprite(const char* scroll_sprite_name, int z_order, int tag){
    if (!m_bHasScrollFront){
        m_bHasScrollFront = true;
    }

    m_nScrollSpriteTag = tag;

    Sprite* scroll_sprite0 = Sprite::create(scroll_sprite_name);
    scroll_sprite0->setAnchorPoint(Vec2::ZERO);
    scroll_sprite0->setPosition(Vec2::ZERO);
    scroll_sprite0->setTag(tag);
    getParent()->addChild(scroll_sprite0, z_order);

    Sprite* scroll_sprite1 = Sprite::create(scroll_sprite_name);
    scroll_sprite1->setAnchorPoint(Vec2::ZERO);
    scroll_sprite1->setPosition(Vec2(scroll_sprite0->getContentSize().width, 0));
    scroll_sprite1->setTag(tag + 1);
    getParent()->addChild(scroll_sprite1, z_order);
}

//��������λ�ù�����ͼ��ʹ���Ǿ���λ�ڴ��ڵ��м�
void MapLayer::update(){
    Point heroPosition = global->hero->getPosition();   
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size mapSize = m_pMap->getContentSize();
    Vec2 centerPoint = visibleSize / 2;

    int x = MAX(visibleSize.width / 2 + heroPosition.x / 2, heroPosition.x);
    int y = MAX(visibleSize.height / 2, heroPosition.y);
    

    x = MIN(x, mapSize.width - visibleSize.width / 2);
    y = MIN(y, mapSize.height - visibleSize.height / 2 + 62);

    if (m_bHasScrollFront){
        Sprite* scroll_sprite0 = static_cast<Sprite*>(getParent()->getChildByTag(m_nScrollSpriteTag));
        Sprite* scroll_sprite1 = static_cast<Sprite*>(getParent()->getChildByTag(m_nScrollSpriteTag + 1));

        int scroll0_positionX = scroll_sprite0->getPositionX();
        int scroll1_positionX = scroll_sprite1->getPositionX();

        if (scroll0_positionX < -scroll_sprite0->getContentSize().width){
            scroll0_positionX = scroll_sprite0->getContentSize().width;
        }
        if (scroll1_positionX < -scroll_sprite1->getContentSize().width){
            scroll1_positionX = scroll_sprite1->getContentSize().width;
        }

        int scroll = getParent()->getPositionX() - (centerPoint.x - x);
        
        scroll_sprite0->setPositionX(scroll0_positionX - scroll);
        scroll_sprite1->setPositionX(scroll1_positionX - scroll);
    }

    getParent()->setPosition(centerPoint - Vec2(x, y));
}