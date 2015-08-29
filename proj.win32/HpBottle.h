#ifndef _H_HP_BOTTLE_
#define _H_HP_BOTTLE_

#include "Tool.h"

class HpBottle : public Tool{
public:
    HpBottle();
    ~HpBottle();
    virtual bool init();
    CREATE_FUNC(HpBottle);
};

#endif