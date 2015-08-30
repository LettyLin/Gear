#include "Hero.h"
#include "Global.h"
#include "NPC.h"
#include "Enemy.h"
#include "Keyboard.h"
#include "Tool.h"
#include "Skill.h"
#include "Backpack.h"
#include "Property.h"
#include "UiLayer.h"
#include "Formater.h"

Hero::Hero(){
}
Hero::~Hero(){
}

//初始化主角各动作的动画
bool Hero::init(){
    if (!Sprite::init()){
        return false;
    }
    
    //将包含主角所有动作帧的合图载入到帧缓存池中
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hero.plist", "hero.png");

    //设置主角初始帧
    this->initWithSpriteFrameName("hero_stand00.png");

    //创建站立动画，帧数8，帧率10
    Animation* standAnimation = GameUtile::createNormalAction("hero_stand%02d.png", 8, 10);
    this->setStandAction(RepeatForever::create(Animate::create(standAnimation)));

    //创建行走动画，帧数8，帧率20
    Animation* walkAnimation = GameUtile::createNormalAction("hero_walk%02d.png", 8, 14);
    this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

    Animation* jumpAnimation = GameUtile::createNormalAction("hero_jump%02d.png", 9, 20);
    this->setJumpAction(Sequence::create(Animate::create(jumpAnimation),
        CallFuncN::create(CC_CALLBACK_0(Hero::EnableMoveable, this)),
        NULL));

    //Animation* dropAnimation = GameUtile::createNormalAction("hero_stand00.png", 1, 10);
    //this->setDropAction(RepeatForever::create(Animate::create(dropAnimation)));

    Animation* crouchAnimation = GameUtile::createNormalAction("hero_crouch%02d.png", 4, 20);
    this->setCrouchAction(Animate::create(crouchAnimation));
    Animation* standupAnimation = GameUtile::createNormalAction("hero_standup%02d.png", 4, 20);
    this->setStandupAction(Sequence::create(Animate::create(standupAnimation),
        CallFuncN::create(CC_CALLBACK_0(Hero::EnableMoveable, this)), 
        NULL));

    Animation* attackAnimation = GameUtile::createNormalAction("hero_attack%02d.png", 12, 20);
    this->setAttackAction(Sequence::create(Animate::create(attackAnimation),
        CallFuncN::create(CC_CALLBACK_0(Hero::EnableMoveable, this)), 
        NULL));

    Animation* walkAttackAnimation = GameUtile::createNormalAction("hero_walkattack%02d.png", 6, 30);
    this->setWalkAttackAction(Sequence::create(Animate::create(walkAttackAnimation),
        CallFuncN::create(CC_CALLBACK_0(Hero::EnableMoveable, this)),
        NULL));

    Animation* jumpAttackAnimation = GameUtile::createNormalAction("hero_jumpattack%02d.png", 4, 14);
    this->setJumpAttackAction(Sequence::create(Animate::create(jumpAttackAnimation),
        CallFuncN::create(CC_CALLBACK_0(Hero::EnableMoveable, this)),
        NULL));

    Animation* hurtAnimation = GameUtile::createNormalAction("hero_hurt%02d.png", 2, 20);
    this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), 
        CallFuncN::create(CC_CALLBACK_0(Role::EndHurt, this)), 
        NULL));

    Animation* dieAnimation = GameUtile::createNormalAction("hero_die%02d.png", 5, 10);
    this->setHurtAction(Animate::create(dieAnimation));

    //Add other actions here

    m_currentHp = 100;
    m_maxHp = 100;
    m_currentMp = 100;
    m_maxMp = 100;
    m_strenth = 20;
    m_defence = 20;
    m_moveVelocity = 5;

    m_bodyBox = GameUtile::createBoundingBox(Vec2(32, 16), getContentSize() - Size(64, 28));
    m_attackBox = GameUtile::createBoundingBox(Vec2(80, 20), Size(80, getContentSize().height + 20));
    m_talkingBox = GameUtile::createBoundingBox(Vec2(-400, -50), Size(800, getContentSize().height + 100));

    GetTool(TOOL_HPBOTTLE);
    GetSkill(SKILL_THROW_FIRE);

    //设置初始速度
    this->setVelocity(Vec2(0, 0));

    //set other properties here

    return true;
}

void Hero::Inherit(Hero* hero){
    if (hero == NULL){
        return;
    }

    m_currentHp = hero->getCurrentHp();
    m_maxHp = hero->getMaxHp();
    m_currentMp = hero->getCurrentMp();
    m_maxMp = hero->getMaxMp();
    setStrenth(hero->getStrenth());
    setDefence(hero->getDefence());
    setMoveVelocity(hero->getMoveVelocity());
    for (Tool* tool : hero->getTools()){
        GetTool(tool->getToolId());
    }
    for (Skill* skill : hero->getSkills()){
        GetSkill(skill->getSkillId());
    }
}

//调用站立动作
void Hero::onStand(){
    if (!m_moveable){
        return;
    }

    setVelocity(Vec2::ZERO);
    Role::onStand();
}

//调用行走动作
void Hero::onWalk(){
    if (!m_moveable){
        return;
    }

    setVelocity(Vec2(m_moveVelocity, 0));
    Role::onWalk();
}

void Hero::onJump(){
    if (!m_moveable && (m_state != ROLE_STATE_CROUCH)){
        return;
    }

    if (!m_dropping){
        m_dropping = true;
        setVelocity(Vec2(m_velocity.x, 8));
    }
    Role::onJump();
}

void Hero::onDrop(){
    Role::onDrop();
}

void Hero::onCrouch(){
    if (!m_moveable){
        return;
    }
    m_velocity = Vec2::ZERO;

    Role::onCrouch();
}

void Hero::onStandup(){
    Role::onStandup();
}

void Hero::onHurt(int hurt){
    if (!m_moveable){
        return;
    }

    int actual_hurt = hurt - (m_defence + rand() % 20 - 10);
    m_currentHp -= actual_hurt;
    Role::onHurt(actual_hurt);
}

void Hero::onDie(){
    m_moveable = false;
    setVelocity(Vec2::ZERO);
    Role::onDie();
}

void Hero::onAttack(){
    if (!m_moveable){
        return;
    }
    Role::onAttack();
    CheckAttack(0);
}

void Hero::onWalkAttack(){
    if (!m_moveable){
        return;
    }
    Role::onWalkAttack();
    CheckAttack(0);
}

void Hero::onJumpAttack(){
    Role::onJumpAttack();
    m_velocity.x = 0;
    CheckAttack(0);
}

void Hero::onTalk(){
    Rect npcBox = global->npc->getBodyBox().actual;
    Rect a = getTalkingBox().actual;
    if (a.intersectsRect(npcBox)){
        global->npc->startTalking();
    }
}

void Hero::AddHp(int dirta_hp){
    m_currentHp += dirta_hp;
    if (m_currentHp > m_maxHp){
        m_currentHp = m_maxHp;
    }
}


void Hero::die(){}

void Hero::GetTool(int tool_id){
    m_tools.pushBack(Tool::create(tool_id));
}

void Hero::UseTool(int tool_id){
    for (Tool* tool : m_tools){
        if (tool->getToolId() == tool_id){
            tool->use();
            m_tools.eraseObject(tool, true);
            CC_SAFE_RELEASE_NULL(tool);
        }
    }
}

void Hero::GetSkill(int skill_id){
    for (Skill* skill : m_skills){
        if (skill->getSkillId() == skill_id){
            return;
        }
    }
    m_skills.pushBack(Skill::create(skill_id));
}

void Hero::UseSkill(int skill_id){
    if (!m_moveable){
        return;
    }

    for (Skill* skill : m_skills){
        if (skill->getSkillId() == skill_id){
            skill->use();
        }
    }
}

void Hero::ShowProperties(){
    if (global->property != NULL){
        global->uiLayer->removeChild(global->property, true);
        global->property = NULL;
        return;
    }
    Property* property = Property::create();
    property->addItem(Label::create(Formater::IntToString(m_currentHp), "Comic Sans MS", 16));
    property->addItem(Label::create(Formater::IntToString(m_currentMp), "Comic Sans MS", 16));
    property->addItem(Label::create(Formater::IntToString(m_strenth), "Comic Sans MS", 16));
    property->addItem(Label::create(Formater::IntToString(m_defence), "Comic Sans MS", 16));
    property->addItem(Label::create(Formater::IntToString(m_moveVelocity), "Comic Sans MS", 16));

    global->uiLayer->addChild(property);
    property->setAnchorPoint(Vec2(0.9, -0.1));
    property->setRotation(-90);
    property->setPosition(Vec2(1280, 0));
    RotateBy* rotate_shelf_wise = RotateBy::create(0.3f, 90);
    property->runAction(Sequence::create(rotate_shelf_wise,
        CallFuncN::create(CC_CALLBACK_0(Property::ResetPosition, property)),
        NULL));
}

void Hero::ShowBackpack(){
    if (global->backpack != NULL){
        global->uiLayer->removeChild(global->backpack, true);
        global->backpack = NULL;
        return;
    }

    backpack = Backpack::create();

    int i = 0;
    for (Tool* tool : m_tools){
        tool->setTag(i);
        backpack->addItem(tool);
    }

    global->uiLayer->addChild(backpack);
    backpack->setAnchorPoint(Vec2(1, -1));
    backpack->setRotation(-90);
    backpack->setPosition(Vec2(1280, 0));
    RotateBy* rotate_shelf_wise = RotateBy::create(0.3f, 90);
    backpack->runAction(Sequence::create(rotate_shelf_wise, 
        CallFuncN::create(CC_CALLBACK_0(Backpack::ResetPosition, backpack)),
        NULL));
}


void Hero::ShowSkillList(){
}

void Hero::CheckAttack(int base_hurt){
    Vector<Enemy*> enemies = global->enemies;

    if (enemies.empty()){
        return;
    }

    Vector<Enemy*>::iterator it = enemies.begin();
    for (; it != enemies.end(); ++it){
        if ((*it)->getState() == ROLE_STATE_DIE){
            continue;
        }
        Rect enemyBox = (*it)->getBodyBox().actual;
        if (enemyBox.intersectsRect(getAttackBox().actual)){
            int hurt = m_strenth + rand() % 20 - 10;
            if (rand() % 100 < 5){
                hurt *= 2;
            }
            (*it)->onHurt(hurt);
        }
    }
}

void Hero::CheckKeyState(){
    if (Keyboard::getKeyState(KEY_STATE_LEFT_ARROW)){
        setDirection(ROLE_DIRECTION_LEFT);
        onWalk();
    }
    else if (Keyboard::getKeyState(KEY_STATE_RIGHT_ARROW)){
        setDirection(ROLE_DIRECTION_RIGHT);
        onWalk();
    }
    else{
        m_velocity = Vec2::ZERO;
        onStand();
    }
}

void Hero::EnableMoveable(){
    m_moveable = true;
    CheckKeyState();
}

void Hero::updateAllBox(){
    updateBox(m_bodyBox);
    updateBox(m_attackBox);
    updateBox(m_talkingBox);
}