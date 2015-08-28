#include "TalkingLayer.h"
#include "Global.h"

TalkingLayer::TalkingLayer(){}
TalkingLayer::~TalkingLayer(){}

bool TalkingLayer::init(Conversation* conversations){
    if (!Layer::init()){
        return false;
    }

    if (conversations == NULL){
        return false;
    }

    m_conversations = conversations;
    m_nConversationTimes = 0;

    m_bEnd = false;

    m_talkingBackground = Sprite::create("talking_box.png");
    m_talkingBackground->retain();
    m_talkingBackground->setAnchorPoint(Vec2::ZERO);
    m_talkingBackground->setPosition(Vec2(200, -300));
    addChild(m_talkingBackground, 128);
    m_talkingBackground->runAction(MoveTo::create(0.5, Vec2(200, 0)));

    ShowNextConversation();

    return true;
}

TalkingLayer* TalkingLayer::create(Conversation* conversations){
    TalkingLayer* talkingLayer = new TalkingLayer;
    if (talkingLayer != NULL && talkingLayer->init(conversations)){
        talkingLayer->autorelease();
    }
    else{
        delete talkingLayer;
        talkingLayer = NULL;
    }

    return talkingLayer;
}

bool TalkingLayer::ShowNextConversation(){
    if (m_text != NULL){
        m_talkingBackground->removeChild(m_text, true);
    }

    if (m_conversations[m_nConversationTimes].text == "NULL"){
        return false;
    }

    if (m_conversations[m_nConversationTimes].talker == TALKER_HERO){
    }
    else{
    }

    Label* text = Label::create(m_conversations[m_nConversationTimes].text, "Comic Sans MS", 20);
    m_text = text;
    m_text->retain();
    text->setColor(Color3B(0, 0, 0));
    text->setAnchorPoint(Vec2::ZERO);
    text->setPosition(Vec2(100, 100));
    m_talkingBackground->addChild(text);

    ++m_nConversationTimes;
    return true;
}

void TalkingLayer::EndConversation(){
    getParent()->removeChild(m_talkingBackground, true);
    m_bEnd = true;
}