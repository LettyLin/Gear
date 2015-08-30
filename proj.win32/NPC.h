#ifndef _H_NPC_
#define _H_NPC_

#include "Role.h"

class TalkingLayer;
struct Conversation;

class NPC : public Role{
public:
    NPC();
    ~NPC();
    virtual bool init(char const* npcName);
    static NPC* create(char const* npcName);
    void LoadConversations(char const*npcName);

    void startTalking();
    void continueTalking();
    void endTalking();

    CC_SYNTHESIZE(int, m_nTalkingTimes, TalkingTimes);

private:
    Conversation** m_conversation;
    int m_nMaxTalkingTimes;

    TalkingLayer* m_talkingLayer;
};

#endif