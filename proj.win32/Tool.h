#ifndef _H_TOOL_
#define _H_TOOL_

#include <cocos2d.h>
USING_NS_CC;

enum eToolsId{
    TOOL_HPBOTTLE = 0
};

enum eToolType{
    TOOL_TYPE_ADDHP = 0
};

class Tool : public Sprite{
public:
    Tool();
    ~Tool();

    static Tool* create(int tool_id);

    virtual void use();

    CC_SYNTHESIZE(eToolType, m_toolType, ToolType);
    CC_SYNTHESIZE(eToolsId, m_toolId, ToolId);
    CC_SYNTHESIZE(int, m_toolValue, ToolValue);
};

#endif