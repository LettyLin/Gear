#include "TalkingLayer.h"
#include "Global.h"
#include "UiLayer.h"
#include "GameLayer.h"
#include "GameUtile.h"

TalkingLayer::TalkingLayer(){}
TalkingLayer::~TalkingLayer(){}

bool TalkingLayer::init(Conversation* conversations){
    if (!Layer::init()){
        return false;
    }

    if (conversations == NULL){
        return false;
    }

    GameUtile::Pause();

    m_conversations = conversations;
    m_nConversationTimes = 0;

    m_bEnd = false;

    m_talkingBackground = Sprite::create("dialogbox.png");
    //m_talkingBackground->retain();
    m_talkingBackground->setAnchorPoint(Vec2::ZERO);
    m_talkingBackground->setPosition(Vec2(140, -300));
    addChild(m_talkingBackground, 128);
    m_talkingBackground->runAction(MoveTo::create(0.5, Vec2(140, -50)));

    m_hero = Sprite::create("hero_talking.png");
    m_hero->setAnchorPoint(Vec2::ZERO);
    m_hero->setPosition(Vec2(-80, -100));
    addChild(m_hero, 120);

    m_npc = Sprite::create("npc_talking.png");
    m_npc->setAnchorPoint(Vec2::ZERO);
    m_npc->setPosition(Vec2(750, -230));
    addChild(m_npc, 120);

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
        m_hero->setOpacity(255);
        m_npc->setOpacity(128);
    }
    else{
        m_hero->setOpacity(128);
        m_npc->setOpacity(255);
    }

    Label* text = Label::create(m_conversations[m_nConversationTimes].text, "Comic Sans MS", 20);
    m_text = text;
    m_text->retain();
    text->setColor(Color3B(255, 255, 0));
    text->setAnchorPoint(Vec2(0, 1));
    text->setPosition(Vec2(100, 320));
    m_talkingBackground->addChild(text);

    ++m_nConversationTimes;
    return true;
}

void TalkingLayer::EndConversation(){
    getParent()->removeChild(m_talkingBackground, true);
    m_bEnd = true;
    GameUtile::Continue();
}