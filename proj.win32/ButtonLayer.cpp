#include "ButtonLayer.h"
#include "Hero.h"
#include "Global.h"


ButtonLayer::ButtonLayer()
{
    global->buttonLayer = this;
}


ButtonLayer::~ButtonLayer()
{
}


bool ButtonLayer::init(){
    if (!Layer::init())
    {
        return false;
    }

    Sprite* goods = Sprite::create("backpack_01.png");
    MenuItemSprite* goods_menu = MenuItemSprite::create(goods, goods, CC_CALLBACK_0(Hero::ShowBackpack, global->hero));
    goods_menu->setPosition(Vec2(800, 80));
    //this->addChild(goods, 0);

    Sprite* skills = Sprite::create("skill_01.png");
    MenuItemSprite* skills_menu = MenuItemSprite::create(skills, skills, CC_CALLBACK_0(Hero::ShowSkillList, global->hero));
    skills_menu->setPosition(Vec2(900, 80));
    //this->addChild(skills, 0);

    Sprite* properties = Sprite::create("skill_01.png");
    MenuItemSprite* properties_menu = MenuItemSprite::create(properties, properties, CC_CALLBACK_0(Hero::ShowProperties, global->hero));
    properties_menu->setPosition(Vec2(1000, 80));
    //this->addChild(setting, 0);

    Menu* menu = Menu::create(goods_menu, skills_menu, properties_menu, NULL);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 20);


    goods_hover = Sprite::create("backpack_02.png");
    goods_hover->setPosition(Vec2(800, 80));
    goods_hover->retain();


    skills_hover = Sprite::create("skill_02.png");
    skills_hover->setPosition(Vec2(900, 80));
    skills_hover->retain();


    property_hover = Sprite::create("skill_02.png");
    property_hover->setPosition(Vec2(1000, 80));
    property_hover->retain();


    Sprite* gear = Sprite::create("setting_up00.png");
    gear->setPosition(Vec2(1280, 0));
    addChild(gear);

    return true;
}

void ButtonLayer::BrightBackpack(){
    addChild(goods_hover);
}

void ButtonLayer::UnBrightBackpack(){
    removeChild(goods_hover);
}

void ButtonLayer::BrightSkilllist(){
    addChild(skills_hover);
}

void ButtonLayer::UnBrightSkilllist(){
    removeChild(skills_hover);
}

void ButtonLayer::BrightProperty(){
    addChild(property_hover);
}

void ButtonLayer::UnBrightProperty(){
    removeChild(property_hover);
}
