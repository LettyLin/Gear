#include "Backpack.h"
#include "Global.h"

Backpack::Backpack()
{
    global->backpack = this;
}


Backpack::~Backpack()
{
    global->backpack = NULL;
}


bool Backpack::init(){
    if (!Sprite::init())
    {
        return false;
    }

    initWithFile("backpackbox.png");
    setAnchorPoint(Vec2::ZERO);
    setPosition(Vec2(960, 300));

    m_nTimer = 0;
    m_Point[0] = Vec2(100, 100);
    m_Point[1] = Vec2(-152, 495);
    m_Point[2] = Vec2(-82, 495);
    m_Point[3] = Vec2(-222, 440);
    m_Point[4] = Vec2(-152, 440);
    m_Point[5] = Vec2(-82, 440);
    m_Point[6] = Vec2(-222, 385);
    m_Point[7] = Vec2(-152, 385);
    m_Point[8] = Vec2(-82, 385);
    return true;
}

int Backpack::getTag(Point point){
    setAnchorPoint(Vec2::ZERO);
    Vec2 backpack_position = getPosition();

    for (int i = 0; i < 9; ++i){
        Rect block = Rect(backpack_position.x + m_Point[i].x, backpack_position.y + m_Point[i].y, 40, 40);
        if (block.containsPoint(point)){
            return i;
        }
    }

    return -1;
}

void Backpack::ResetPosition(){
    setAnchorPoint(Vec2::ZERO);
    setPosition(getPosition() + Vec2(-getContentSize().width, getContentSize().height));
}

void Backpack::addItem(Tool* tool){
    tool->setPosition(m_Point[m_nTimer]);
    m_nTimer++;
    this->addChild(tool);
}