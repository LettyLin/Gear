#include "NPC.h"
#include "Global.h"

NPC::NPC(){
    global->npc = this;
}
NPC::~NPC(){}

bool NPC::init(){
    if (!Sprite::init()){
        return false;
    }

    m_conversation[0][0].talker = TALKER_HERO;
    m_conversation[0][1].talker = TALKER_HERO;
    m_conversation[0][0].text = "Hello, I am erwa!";
    m_conversation[0][1].text = "NULL";
    m_conversation[1][0].text = "...";
    m_conversation[1][1].text = "NULL";

    SpriteFrame* frame = SpriteFrame::create("npc_normal.png", Rect(0, 0, 64, 128));
    SpriteFrameCache::getInstance()->addSpriteFrame(frame, "npc_normal.png");

    initWithSpriteFrameName("npc_normal.png");

    Animation* stand = createNormalAction("npc_normal.png", 1, 10);
    setStandAction(RepeatForever::create(Animate::create(stand)));

    setJumpAction(RepeatForever::create(Animate::create(stand)));

    runStandAction();

    m_bodyBox = createBoundingBox(Vec2(0, 0), getContentSize());
    m_nTalkingTimes = 0;

    return true;
}

void NPC::startTalking(){
    if (m_nTalkingTimes > 1){
        m_nTalkingTimes = 1;
    }

    m_talkingLayer = TalkingLayer::create(m_conversation[m_nTalkingTimes]);
    addChild(m_talkingLayer);
    global->setTalking(true);
    ++m_nTalkingTimes;
};

void NPC::continueTalking(){
    if (!m_talkingLayer->ShowNextConversation()){
        endTalking();
    }
}

void NPC::endTalking(){
    m_talkingLayer->EndConversation();
    removeChild(m_talkingLayer, true);
    m_talkingLayer = NULL;
    global->setTalking(false);
}


