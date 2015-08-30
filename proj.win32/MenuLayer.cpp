#include "MenuLayer.h"
#include "UiLayer.h"
#include "StateBar.h"
#include "Global.h"
#include "Hero.h"
#include "Sound.h"

MenuLayer::MenuLayer()
{
}


MenuLayer::~MenuLayer()
{
}


bool MenuLayer::init(){
    if (!Layer::init())
    {
        return false;
    }

    GameUtile::Pause();

    m_visibleSize = Director::getInstance()->getVisibleSize();
    //Ìí¼Ómenu°´Å¥
    Label* labelSave = Label::create("Save", "Comic Sans MS", 30);
    MenuItemLabel* menuSave = MenuItemLabel::create(labelSave, CC_CALLBACK_0(MenuLayer::saveGame, this));
    menuSave->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.7));

    Label* labelRead = Label::create("Read", "Comic Sans MS", 30);
    MenuItemLabel* menuRead = MenuItemLabel::create(labelRead, CC_CALLBACK_0(MenuLayer::readGame, this));
    menuRead->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.6));

    Label* labelMusic = Label::create("Muisc", "Comic Sans MS", 30);
    global->uiLayer->addChild(labelMusic, 110);

    Label* labelON = Label::create("ON", "Comic Sans MS", 30);
    Label* labelOFF = Label::create("OFF", "Comic Sans MS", 30);
    MenuItemLabel* menuMusic0 = MenuItemLabel::create(labelON, CC_CALLBACK_0(MenuLayer::musicON, this));
    MenuItemLabel* menuMusic1 = MenuItemLabel::create(labelOFF, CC_CALLBACK_0(MenuLayer::musicOFF, this));
    menuMusic0->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.5));
    menuMusic1->setPosition(Vec2(m_visibleSize.width * 0.6, m_visibleSize.height * 0.5));

    Label* labelReturn = Label::create("Return", "Comic Sans MS", 30);
    MenuItemLabel* menuReturn = MenuItemLabel::create(labelReturn, CC_CALLBACK_0(MenuLayer::returnGame, this));
    menuReturn->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.4));

    Label* labelExit = Label::create("Exit Game", "Comic Sans MS", 30);
    MenuItemLabel* menuExit = MenuItemLabel::create(labelExit, CC_CALLBACK_0(MenuLayer::exitGame, this));
    menuExit->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.3));

    Menu* menu0 = Menu::create(menuSave, menuRead, menuMusic0, menuMusic1, menuReturn, menuExit, NULL);
    menu0->setPosition(Vec2::ZERO);
    global->uiLayer->addChild(menu0, 110);
    menu0->setTag(0);



    return true;
}

void MenuLayer::saveGame()
{
    GameUtile::Save(0);
}

void MenuLayer::readGame()
{
    GameUtile::Load(0);
}

void MenuLayer::musicON()
{
    if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        Sound::play_bgmusic(global->getSceneIndex());
    }
}

void MenuLayer::musicOFF()
{
    if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
    {
        Sound::stop_bgmusic();
    }
}

void MenuLayer::returnGame()
{
    global->uiLayer->removeChildByTag(0, true);
    global->uiLayer->removeChildByTag(1, true);
}

void MenuLayer::exitGame()
{
    Director::getInstance()->end();
}