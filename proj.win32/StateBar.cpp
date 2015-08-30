#include "StateBar.h"
#include "Global.h"
#include "Hero.h"

StateBar::StateBar(){}
StateBar::~StateBar(){}

bool StateBar::init()
{
	if (!Layer::init())
	{
		return false;
	}


	//创建血条
	Sprite* sprite = Sprite::create("Blood.png");
	sprite->setTag(10);
	sprite->setScale(0.5);
	ProgressTimer* pthp = ProgressTimer::create(Sprite::create("HP.png"));

	this->addChild(sprite,10);
	sprite->addChild(pthp);

	pthp->setAnchorPoint(Point(0, 0));
	sprite->setAnchorPoint(Point(0, 0));
	sprite->setPosition(0, 580);
	pthp->setPosition(Point(0,0));

	pthp->setType(ProgressTimer::Type::BAR);
	pthp->setBarChangeRate(Point(1, 0));
	pthp->setMidpoint(Point(0, 0)); //设置图片percent0所在的点
	pthp->setPercentage(100.0);
	pthp->setTag(100);
	/*pthp->setScale(0.8);*/

	//创建能量条
	ProgressTimer* ptmp = ProgressTimer::create(Sprite::create("MP.png"));


	ptmp->setAnchorPoint(Point(0, 0));
	ptmp->setPosition(Point(0, 0));

	ptmp->setType(ProgressTimer::Type::BAR);
	ptmp->setBarChangeRate(Point(1, 0));
	ptmp->setMidpoint(Point(0, 0)); //设置图片percent0所在的点
	ptmp->setPercentage(100.0);
	ptmp->setTag(20);
	/*ptmp->setScale(0.8);*/
	sprite->addChild(ptmp);

	scheduleUpdate();

	return true;
}

void StateBar::update(float dt)
{
    Hero* hero = global->hero;
	Sprite* sprite0 = (Sprite*)getChildByTag(10);

	ProgressTimer* pt0 = (ProgressTimer*)sprite0->getChildByTag(100);
    float perc = (hero->getCurrentHp() * 1.0) / hero->getMaxHp() * 100;
    float pt0_perc = pt0->getPercentage();
    if (pt0_perc - perc >= 1){
        pt0->setPercentage(--pt0_perc);
    }
    else if (pt0_perc - perc <= -1){
        pt0->setPercentage(++pt0_perc);
    }


	ProgressTimer* pt1 = (ProgressTimer*)sprite0->getChildByTag(20);
 //   pt1->setPercentage(pt1->getPercentage() - 1);
    perc = (hero->getCurrentMp() * 1.0) / hero->getMaxMp() * 100;
    float pt1_perc = pt1->getPercentage();
    if (pt1_perc - perc >= 1){
        pt1->setPercentage(pt0_perc - 1);
    }
    else if (pt1_perc - perc <= -1){
        pt1->setPercentage(pt0_perc + 1);
    }

}
