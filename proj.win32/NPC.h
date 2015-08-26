#ifndef _H_NPC_
#define _H_NPC_

#include "Role.h"
#include "TalkingLayer.h"

#define MAX_CONVERSATION 20

class NPC : public Role{
public:
    NPC();
    ~NPC();
    virtual bool init();
    CREATE_FUNC(NPC);

    void startTalking();
    void continueTalking();
    void endTalking();

private:
    Conversation m_conversation[MAX_CONVERSATION][20];
    int m_nTalkingTimes;

    TalkingLayer* m_talkingLayer;
};

#endif