#include "Property.h"
#include "Global.h"

Property::Property()
{
    global->property = this;
}


Property::~Property()
{
    global->property = NULL;
}


bool Property::init(){
    if (!Sprite::init())
    {
        return false;
    }

    initWithFile("Propertybox.png");
    setAnchorPoint(Vec2::ZERO);
    setPosition(Vec2(960, 300));

    m_nTimer = 0;
    m_Point[0] = Vec2(330, 230);
    m_Point[1] = Vec2(330, 205);
    m_Point[2] = Vec2(330, 178);
    m_Point[3] = Vec2(330, 151);
    m_Point[4] = Vec2(330, 125);
    return true;
}

void Property::ResetPosition(){
    setAnchorPoint(Vec2::ZERO);
    setPosition(getPosition() + Vec2(-0.9 * getContentSize().width, getContentSize().height * 0.1));
}

void Property::addItem(Label* label){
    label->setPosition(m_Point[m_nTimer]);
    m_nTimer++;
    this->addChild(label);
}