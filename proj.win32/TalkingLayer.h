#ifndef _H_TALKING_LAYER_
#define _H_TALKING_LAYER_

#include <cocos2d.h>
USING_NS_CC;

enum eTalker{
    TALKER_NPC,
    TALKER_HERO
};

struct Conversation{
    eTalker talker;
    std::string text;
};

class TalkingLayer : public Layer{
public:
    TalkingLayer();
    ~TalkingLayer();
    virtual bool init(Conversation* conversations);
    static TalkingLayer* create(Conversation* conversations);

    bool ShowNextConversation();
    void EndConversation();

private:
    Sprite* m_talkingBackground;
    Label* m_text;

    Sprite* m_hero;
    Sprite* m_npc;

    Conversation* m_conversations;
    int m_nConversationTimes;

    bool m_bEnd;
};

#endif