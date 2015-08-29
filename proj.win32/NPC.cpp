#include "NPC.h"
#include "TalkingLayer.h"
#include "Global.h"
#include "Formater.h"
#include <fstream>

NPC::NPC() : m_conversation(NULL){
    global->npc = this;
}
NPC::~NPC(){
    for (int i = 0; i < m_nMaxTalkingTimes; ++i){
        delete[] m_conversation[i];
    }
    delete[] m_conversation;
    m_conversation = NULL;
}

bool NPC::init(char const* npcName){
    if (!Sprite::init()){
        return false;
    }

    std::string npcNameCopy = (char*)npcName;

    SpriteFrame* sprite = SpriteFrame::create("npc_stand00.png", Rect(0, 0, 64, 128));
    SpriteFrameCache::getInstance()->addSpriteFrame(sprite, "npc_stand00.png");

    std::string npcImgFormat = npcNameCopy + "_stand%02d.png";

    initWithSpriteFrameName(npcNameCopy + "_stand00.png");

    Animation* stand = createNormalAction(npcImgFormat.c_str(), 1, 10);
    setStandAction(RepeatForever::create(Animate::create(stand)));
    setJumpAction(RepeatForever::create(Animate::create(stand)));

    m_maxHp = 1;
    m_currentHp = 1;

    m_bodyBox = createBoundingBox(Vec2(0, 0), getContentSize());
    m_nTalkingTimes = 0;

    runStandAction();

    LoadConversations(npcNameCopy.c_str());

    return true;
}

NPC* NPC::create(char const* npcName){
    NPC* npc = new NPC;
    if (npc != NULL && npc->init(npcName)){
        npc->autorelease();
    }
    else{
        delete npc;
        npc = NULL;
    }
    return npc;
}

void NPC::LoadConversations(char const* npcName){
    std::string npcNameCopy = (char*)npcName;
    std::string npcFileName = npcNameCopy + "_conversations.ini";

    std::ifstream FileReader(npcFileName);

    int currentSceneIndex = global->getSceneIndex();

    CC_ASSERT(FileReader.is_open());
    std::string buffer;
    std::string discard;

    for (; !FileReader.eof();){
        FileReader >> buffer;
        FileReader >> discard;
        if (buffer == "Scene"){
            FileReader >> buffer;
            if (Formater::getInt(buffer) != currentSceneIndex){
                continue;
            }
            FileReader >> buffer;
            FileReader >> discard;
            if (buffer == "MaxTalkingTimes"){
                FileReader >> buffer;
                m_nMaxTalkingTimes = Formater::getInt(buffer);
                m_conversation = new Conversation*[m_nMaxTalkingTimes];

                for (int i = 0; i < m_nMaxTalkingTimes; ++i){
                    FileReader >> buffer;
                    FileReader >> discard;
                    if (buffer == "Conversation"){
                        FileReader >> buffer;
                        int nContentNumber = Formater::getInt(buffer);
                        m_conversation[i] = new Conversation[nContentNumber + 1];
                        for (int j = 0; j < nContentNumber; ++j){
                            FileReader >> buffer;
                            if (buffer == "H:"){
                                m_conversation[i][j].talker = TALKER_HERO;
                            }
                            else if (buffer == "N:"){
                                m_conversation[i][j].talker = TALKER_NPC;
                            }
                            for (;;){
                                std::getline(FileReader, buffer);
                                if (buffer == "end;"){
                                    break;
                                }
                                m_conversation[i][j].text.append(buffer);
                            }
                        }
                        m_conversation[i][nContentNumber].text = "NULL";
                    }
                    continue;
                }
            }
            break;
        }
        else{
            for (;;){
                getline(FileReader, buffer);
                if (buffer == ""){
                    break;
                }
            }
        }
    }

    FileReader.close();
}

void NPC::startTalking(){
    if (m_nTalkingTimes == m_nMaxTalkingTimes){
        m_nTalkingTimes -= 1;
    }

    m_talkingLayer = TalkingLayer::create(m_conversation[m_nTalkingTimes]);
    getParent()->getParent()->addChild(m_talkingLayer);
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
    getParent()->getParent()->removeChild(m_talkingLayer, true);
    m_talkingLayer = NULL;
    global->setTalking(false);
}


