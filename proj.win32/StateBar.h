#ifndef GAMELAYER_H_
#define GAMELAYER_H_
#include <cocos2d.h>
USING_NS_CC;

class StateBar :public Layer
{
	StateBar();
	~StateBar();

public:
	virtual bool init();
	CREATE_FUNC(StateBar);
	void update(float dt);
	void changeScene();

private:
	Sprite* sp;
};

#endif