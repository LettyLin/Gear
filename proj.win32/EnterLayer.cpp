#include "EnterLayer.h"
#include "GameScene.h"
#include "Global.h"

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
        Label* labelNewGame = Label::create("New Game", "Comic Sans MS", 30);
        MenuItemLabel* menuNewGame = MenuItemLabel::create(labelNewGame, CC_CALLBACK_1(EnterLayer::NewGame, this));
        menuNewGame->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.5));	
		
        Label* labelLoadGame = Label::create("Load Game", "Comic Sans MS", 30);
        MenuItemLabel* menuLoadGame = MenuItemLabel::create(labelLoadGame, CC_CALLBACK_1(EnterLayer::LoadGame, this));
        menuLoadGame->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.4));
		
        Label* labelSetting = Label::create("Setting", "Comic Sans MS", 30);
        MenuItemLabel* menuSetting = MenuItemLabel::create(labelSetting, CC_CALLBACK_1(EnterLayer::Setting, this));
        menuSetting->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.3));

        Label* labelExitGame = Label::create("Exit Game", "Comic Sans MS", 30);
        MenuItemLabel* menuExitGame = MenuItemLabel::create(labelExitGame, CC_CALLBACK_1(EnterLayer::ExitGame, this));
        menuExitGame->setPosition(Vec2(m_visibleSize.width * 0.5, m_visibleSize.height * 0.2));

        Menu* menu = Menu::create(menuNewGame, menuLoadGame, menuSetting, menuExitGame, NULL);
        menu->setPosition(Vec2::ZERO);
        addChild(menu);


		//��Ӱ�ťǰ�����
		m_smallGear = Sprite::create("enter_geer_small.png");
		m_smallGear->setPosition(530, 400);
		this->addChild(m_smallGear);

		RotateBy* rotate_small = RotateBy::create(8.0f, 360);
		RepeatForever* rotate_repeate_samll1 = RepeatForever::create(rotate_small);
		m_smallGear->runAction(rotate_repeate_samll1);
		m_smallGear->setVisible(false);

        //����ѡ��menuʱ�ĳ��ֶ���
        for (int i = 0; i < 4; ++i){
		    m_pMoveToMenuItem[i] = MoveTo::create(1, Vec2(530, 400 - i * 80));
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
        if (yPos <= (m_visibleSize.height * 0.5 + 21) && yPos >= (m_visibleSize.height * 0.5 - 21)){
			m_smallGear->runAction(m_pMoveToMenuItem[0]);
            return;
		}
        //�ڶ�����ť
		else if (yPos <= (m_visibleSize.height * 0.4 + 21) && yPos >= (m_visibleSize.height * 0.4 - 21))
		{
            m_smallGear->runAction(m_pMoveToMenuItem[1]);
            return;
		}
        //��������ť
        else if (yPos <= (m_visibleSize.height * 0.3 + 21) && yPos >= (m_visibleSize.height * 0.3 - 21))
        {
            m_smallGear->runAction(m_pMoveToMenuItem[2]);
            return;
        }
        //���ĸ���ť
        else if (yPos <= (m_visibleSize.height * 0.2 + 21) && yPos >= (m_visibleSize.height * 0.2 - 21))
        {
            m_smallGear->runAction(m_pMoveToMenuItem[3]);
            return;
        }

        if (yPos <= (m_visibleSize.height * 0.5 + 21) && yPos >= (m_visibleSize.height * 0.2 - 21)){
            return;
        }
	}

    //����겻���κΰ�ť��ʱ
    m_smallGear->setVisible(false);

}

void EnterLayer::NewGame(Ref* pSender){
    global->EnterScene(0);
}

void EnterLayer::LoadGame(Ref* pSender){

}

void EnterLayer::Setting(Ref* pSender){

}

void EnterLayer::ExitGame(Ref* pSender){

}

void EnterLayer::update(float ft){
    if (m_smallGear->getPositionY() > m_visibleSize.height * 0.5){
        m_smallGear->setPositionY(m_visibleSize.height * 0.5);
    }
    else if (m_smallGear->getPositionY() < m_visibleSize.height * 0.2){
        m_smallGear->setPositionY(m_visibleSize.height * 0.2);
    }
}