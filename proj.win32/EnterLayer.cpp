#include "EnterLayer.h"
#include "GameScene.h"
#include "GameUtile.h"

EnterLayer::EnterLayer()
{
}

EnterLayer::~EnterLayer()
{
}

bool EnterLayer::init(){
    if (!Layer::init()){
        return false;
    }

    //��ӱ���
    Sprite* background = Sprite::create("enter_scene.png");
    background->setAnchorPoint(Vec2(0.0f, 0.0f));
    addChild(background, 0);

    //�ĳ�ȫ��visibleSize
    m_visibleSize = Director::getInstance()->getVisibleSize();

    //���menu��ť
    /*Label* labelNewGame = Label::create();*/
    MenuItemImage* menuNewGame = MenuItemImage::create("startgame_01.png", "startgame_02.png", CC_CALLBACK_1(EnterLayer::NewGame, this));
    menuNewGame->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.5));

    /*Label* labelLoadGame = Label::create("Load Game", "Comic Sans MS", 30);*/
    MenuItemImage* menuLoadGame = MenuItemImage::create("loadgame_01.png", "loadgame_02.png", CC_CALLBACK_1(EnterLayer::LoadGame, this));
    menuLoadGame->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.35));

    /*Label* labelSetting = Label::create("Setting", "Comic Sans MS", 30);*/
    /*MenuItemImage* menuSetting = MenuItemImage::create("", CC_CALLBACK_1(EnterLayer::Setting, this));
    menuSetting->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.3));*/

    /*Label* labelExitGame = Label::create("Exit Game", "Comic Sans MS", 30);*/
    MenuItemImage* menuExitGame = MenuItemImage::create("exit_01.png", "exit_02.png", CC_CALLBACK_1(EnterLayer::ExitGame, this));
    menuExitGame->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.2));

    Menu* menu = Menu::create(menuNewGame, menuLoadGame, /*menuSetting,*/ menuExitGame, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);


    //��Ӱ�ťǰ�����
    m_smallGear = Sprite::create("enter_geer_small.png");
    m_smallGear->setPosition(500, 400);
    m_smallGear->setScale(0.5);
    this->addChild(m_smallGear);

    RotateBy* rotate_small = RotateBy::create(8.0f, 360);
    RepeatForever* rotate_repeate_samll1 = RepeatForever::create(rotate_small);
    m_smallGear->runAction(rotate_repeate_samll1);
    m_smallGear->setVisible(false);

    //����ѡ��menuʱ�ĳ��ֶ���
    for (int i = 0; i < 3; ++i){
        m_pMoveToMenuItem[i] = MoveTo::create(1, Vec2(490, 400 - i * 119));
        m_pMoveToMenuItem[i]->retain();
    }

    //���������  ����Ƶ���ť�ϰ�ťǰ�����ֳ���
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(EnterLayer::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->scheduleUpdate();

    return true;
}


void EnterLayer::onMouseMove(Event* event){
    EventMouse* e = (EventMouse*)event;
    float xPos = e->getCursorX();
    float yPos = e->getCursorY();
    if (xPos >= 568 && xPos <= 712)
    {
        m_smallGear->setVisible(true);
        //�����λ�ڵ�һ����ťʱ
        if (yPos <= (m_visibleSize.height * 0.5 + 35) && yPos >= (m_visibleSize.height * 0.5 - 35)){
            m_smallGear->runAction(m_pMoveToMenuItem[0]);
            return;
        }
        //�ڶ�����ť
        else if (yPos <= (m_visibleSize.height * 0.38 + 35) && yPos >= (m_visibleSize.height * 0.38 - 35))
        {
            m_smallGear->runAction(m_pMoveToMenuItem[1]);
            return;
        }
        //��������ť
        /*   else if (yPos <= (m_visibleSize.height * 0.3 + 21) && yPos >= (m_visibleSize.height * 0.3 - 21))
        {
        m_smallGear->runAction(m_pMoveToMenuItem[2]);
        return;
        }*/
        //���ĸ���ť
        else if (yPos <= (m_visibleSize.height * 0.2 + 35) && yPos >= (m_visibleSize.height * 0.2 - 35))
        {
            m_smallGear->runAction(m_pMoveToMenuItem[2]);
            return;
        }

        if (yPos <= (m_visibleSize.height * 0.5 + 35) && yPos >= (m_visibleSize.height * 0.2 - 35)){
            return;
        }
    }

    //����겻���κΰ�ť��ʱ
    m_smallGear->setVisible(false);

}

void EnterLayer::NewGame(Ref* pSender){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("action.plist", "action.png");
    GameUtile::EnterScene(0);
}

void EnterLayer::LoadGame(Ref* pSender){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("action.plist", "action.png");
    GameUtile::Load(0);
}


void EnterLayer::ExitGame(Ref* pSender){
    Director::getInstance()->end();
}

void EnterLayer::update(float ft){
    if (m_smallGear->getPositionY() > m_visibleSize.height * 0.5){
        m_smallGear->setPositionY(m_visibleSize.height * 0.5);
    }
    else if (m_smallGear->getPositionY() < m_visibleSize.height * 0.2){
        m_smallGear->setPositionY(m_visibleSize.height * 0.2);
    }
}