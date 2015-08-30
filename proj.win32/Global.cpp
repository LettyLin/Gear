#include "Global.h"
#include "Hero.h"
#include "NPC.h"
#include "Enemy.h"
#include "MapLayer.h"
#include"Backpack.h"
#include "Property.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "UiLayer.h"
#include "ButtonLayer.h"

DECLARE_SINGLETON_MEMBER(Global)

//���캯������ʼ��׼��ע�����Ϣ
Global::Global() :
hero(NULL),
npc(NULL),
mapLayer(NULL),
backpack(NULL),
gameLayer(NULL),
operateLayer(NULL),
uiLayer(NULL),
property(NULL),
m_bTalking(false),
m_bGamePause(false),
m_bMusicPause(false)
{
}

//�����������ͷ�ע�����Ϣ
Global::~Global(){
    CC_SAFE_RELEASE_NULL(hero);
}


