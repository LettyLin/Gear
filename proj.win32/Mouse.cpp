#include "Mouse.h"
#include "Backpack.h"
#include "UiLayer.h"
#include "ButtonLayer.h"
#include "Tool.h"


Mouse::Mouse() : m_currentTool(NULL){}
Mouse::~Mouse(){}

bool Mouse::init(){
    if (!Layer::init()){
        return false;
    }
    UiLayer* uiLayer = global->uiLayer;

    m_nMenuUpBounce = 112;
    
    m_nBackpackLeftBounce = 800;
    m_nPropertyLeftBounce = 1000;

    m_bOnProperty = false;
    m_bOnBackpack = false;

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Mouse::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Mouse::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Mouse::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

//����϶����ߣ�Ѫƿ�ȣ������ܷŵ���ݼ��˵�����갴���ƶ��ſ���
void Mouse::dragMouseDown(Event* event){
    
    
    //��ȡ���λ��
    EventMouse* e = (EventMouse*)event;
    float xPos = e->getCursorX();
    float yPos = e->getCursorY();
    //��ǰ��ȡҪ�ƶ���Ѫƿ���ܵȵ�λ��

   
    Vec2 backpack_position = global->backpack->getPosition();
    Size backpack_size = global->backpack->getContentSize();
    Rect backpack_rect = Rect(backpack_position.x, backpack_position.y, backpack_size.width, backpack_size.height);

    if (!backpack_rect.containsPoint(Vec2(xPos, yPos))){
        return;
    }

    int tag = global->backpack->getTag(Point(xPos, yPos));
    if (tag == -1){
        return;
    }

    m_currentTool = (Tool*)global->backpack->getChildByTag(tag);
    m_lastPoint = m_currentTool->getPosition();
    global->backpack->removeChild(m_currentTool, false);

    m_currentTool->setPosition(Point(xPos, yPos));
    global->uiLayer->addChild(m_currentTool);
}

void Mouse::dragMouseMove(Event* event){
    EventMouse* e = (EventMouse*)event;
    float xPos = e->getCursorX();
    float yPos = e->getCursorY();

    m_currentTool->setPosition(Point(xPos, yPos));
}

void Mouse::dragMouseUp(Event* event){
    EventMouse* e = (EventMouse*)event;
    float xPos = e->getCursorX();
    float yPos = e->getCursorY();

    if (yPos < 200 && yPos > 100){
        if (xPos < 200 && xPos > 100){
            m_currentTool->setPosition(Vec2(100, 100));
            m_currentTool = NULL;
        }
    }

    else{
        m_currentTool->setPosition(m_lastPoint);
        //global->backpack->getTag(m_lastPoint);
        global->backpack->addChild(m_currentTool);
        m_currentTool = NULL;
    }
}

//���������ܡ����ð�ť����ת
void Mouse::setMenuBright(Event* event){
    EventMouse* e = (EventMouse*)event;
    float xPos = e->getCursorX();
    float yPos = e->getCursorY();

    ButtonLayer* buttonLayer = global->buttonLayer;

    if (yPos < m_nMenuUpBounce && yPos > m_nMenuUpBounce - 32){
        if (xPos > m_nPropertyLeftBounce  && xPos < m_nPropertyLeftBounce + 32)
        {
            if (!m_bOnProperty){
                buttonLayer->BrightProperty();
                m_bOnProperty = true;
            }
            if (m_bOnBackpack){
                buttonLayer->UnBrightBackpack();
                m_bOnBackpack = false;
            }
            return;
        }
        else if (xPos > m_nBackpackLeftBounce && xPos < m_nBackpackLeftBounce + 32)
        {
            if (!m_bOnBackpack){
                buttonLayer->BrightBackpack();
                m_bOnBackpack = true;
            }
            if (m_bOnProperty){
                buttonLayer->UnBrightProperty();
                m_bOnProperty = false;
            }
        }
        else{
            if (m_bOnProperty){
                buttonLayer->UnBrightProperty();
                m_bOnProperty = false;
            }
            if (m_bOnBackpack){
                buttonLayer->UnBrightBackpack();
                m_bOnBackpack = false;
            }
        }
    }
}





void Mouse::onMouseDown(Event* event){

    if (global->backpack == NULL){
        return;
    }

    //������Ʒ�϶�����ݼ���
    dragMouseDown(event);
    //menuDown(event);
}

void Mouse::onMouseMove(Event* event){
    //������Ʒ�϶�����ݼ���
    setMenuBright(event);
    if (m_currentTool == NULL){
        return;
    }
    dragMouseMove(event);
}

void Mouse::onMouseUp(Event* event){
    //������Ʒ�϶�����ݼ���
    if (m_currentTool == NULL){
        return;
    }
    dragMouseUp(event);

    //menuUp(event);
}