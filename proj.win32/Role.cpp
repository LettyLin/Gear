#include "Role.h"
#include "MapLayer.h"
#include "Global.h"
//构造函数，初始化动画并设置必要的状态
Role::Role() :
m_pStandAction(NULL),
m_pWalkAction(NULL),
m_pJumpAction(NULL),
m_pAttackAction(NULL),
m_pHurtAction(NULL),
m_pDieAction(NULL),
m_moveable(true),
m_dropping(true),
m_onSlope(false),
m_state(ROLE_STATE_STAND),
m_direction(ROLE_DIRECTION_RIGHT),
m_lastCollisionState(0)
{
    m_mapSize = global->mapLayer->getMap()->getContentSize();
}

//析构函数，释放动画所占用的内存
Role::~Role(){
    /*CC_SAFE_RELEASE_NULL (m_pStandAction);
    CC_SAFE_RELEASE_NULL(m_pWalkAction);*/
}

//根据当前状态判断是否可以转换到期望状态
bool Role::ChangeState(const eRoleState new_state){
    if (!m_moveable){
        return false;
    }

    m_state = new_state;
    return true;
}

void Role::runStandAction(){
    this->runAction(m_pStandAction);
}

void Role::runWalkAction(){
    this->runAction(m_pWalkAction);
}

void Role::runJumpAction(){
    this->runAction(m_pJumpAction);
}

void Role::runAttackAction(){
    this->runAction(m_pAttackAction);
}

void Role::runHurtAction(){
    this->runAction(m_pHurtAction);
}

void Role::runDieAction(){
    this->runAction(m_pDieAction);
}

void Role::onStand(){
    if (ChangeState(ROLE_STATE_STAND)){
        this->stopAllActions();
        runStandAction();
    }
}

void Role::onWalk(){
    if (ChangeState(ROLE_STATE_WALK)){
        runWalkAction();
    }
}

void Role::onJump(){
    m_lastJump = getPosition();

    if (ChangeState(ROLE_STATE_JUMP)){
        runJumpAction();
    }
}

void Role::onAttack(){
    if (ChangeState(ROLE_STATE_ATTACK)){
        runAttackAction();
    }
}

void Role::onHurt(int hurt){
    ShowHurt(hurt);
    if (ChangeState(ROLE_STATE_HURT)){
        runHurtAction();
    }
    if (m_currentHp <= 0){
        runDieAction();
    }
}

void Role::onDie(){
    stopAllActions();
    runDieAction();
    die();
}

void Role::updateBox(BoundingBox &box){
    Vec2 origin = box.origin.origin;
    Size size = box.origin.size;
    if (m_direction == ROLE_DIRECTION_RIGHT){
        box.actual = Rect(origin.x + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    }
    else{
        box.actual = Rect(getContentSize().width - origin.x - size.width + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    }
}

void Role::update(){
    m_lastCollisionState = 0;
    Point newPosition = getNextPosition();
    //检测碰撞
    checkCollisionWithMap(newPosition);

    Point finalPosition;
    global->CheckCollision(this, newPosition, finalPosition, m_lastCollisionState);


    if (m_lastCollisionState & ROLE_COLLISION_WALL){
        setVelocity(Vec2(0, m_velocity.y));
    }

    if (m_lastCollisionState & ROLE_COLLISION_FLOOR){
        if (m_dropping){
            m_dropping = false;
            setVelocity(Vec2(m_velocity.x, 0));
            if (m_velocity.x == 0){
                onStand();
            }
            else{
                onWalk();
            }
        }
    }

    if (m_lastCollisionState & ROLE_COLLISION_SLOPE){
            if (m_state == ROLE_STATE_WALK){
                if (getDirection() == getSlopeDirection()){
                    finalPosition.y += 3;
                }
                else{
                    finalPosition.y -= 2;
                }
            }
    }
 
    if (m_lastCollisionState & ROLE_COLLISION_DROP){
        m_dropping = true;
        onJump();
    }

    setPosition(finalPosition);
    updateAllBox();
}

Point Role::getNextPosition(){
    Point lastPosition = getPosition();
    Point newPosition;
    Size roleSize = getContentSize();

    if (m_dropping && m_velocity.y > -10){
        m_velocity.y -= 1.0;
    }

    //计算角色下一帧的位置
    if (ROLE_DIRECTION_RIGHT == m_direction){
        newPosition.x = lastPosition.x + m_velocity.x;
        newPosition.y = lastPosition.y + m_velocity.y;
    }
    else{
        newPosition.x = lastPosition.x - m_velocity.x;
        newPosition.y = lastPosition.y + m_velocity.y;
    }

    return newPosition;
}

void Role::checkCollisionWithMap(Point &newPosition){
    //防止角色移出地图
    Size roleSize = m_bodyBox.actual.size;

    if (newPosition.x < 0){
        m_lastCollisionState |= ROLE_COLLISION_BOUNCE;
        newPosition.x = 0;
    }
    else if (newPosition.x > m_mapSize.width - roleSize.width){
        m_lastCollisionState |= ROLE_COLLISION_BOUNCE;
        newPosition.x = m_mapSize.width - roleSize.width;
    }
    if (newPosition.y < 0){
        newPosition.y = 0;
    }
    else if (newPosition.y > m_mapSize.height - roleSize.height){
        newPosition.y = m_mapSize.height - roleSize.height;
    }
}

void Role::updateAllBox(){
    this->updateBox(m_bodyBox);
}

void Role::die(){
}

Animation* Role::createNormalAction(const char* format_string, int frame_count, int fps){
    Vector<SpriteFrame*> pFrames;
    //根据编号，格式化帧名，并从帧缓存池中读出相应帧画面，组成帧数组
    for (int i = 0; i < frame_count; ++i){
        const char* ImgName = String::createWithFormat(format_string, i)->getCString();
        SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgName);
        pFrames.insert(i, pFrame);
    }

    //将帧数组创建为动画
    return Animation::createWithSpriteFrames(pFrames, 2.0f / fps);
}

BoundingBox Role::createBoundingBox(Vec2 origin, Size size){
    BoundingBox boundingBox;
    boundingBox.origin = Rect(origin.x, origin.y, size.width, size.height);
    boundingBox.actual = Rect(origin.x + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    return boundingBox;
}

void Role::ShowHurt(int hurt){
    const char* str_hurt = String::createWithFormat("%d", hurt)->getCString();
    m_hurtShow = Label::create(str_hurt, "COMIC SANS MS", 20);
    m_hurtShow->setAnchorPoint(Vec2::ZERO);
    m_hurtShow->setPosition(Vec2(30, 80));
    addChild(m_hurtShow);

    MoveBy* fly_0 = MoveBy::create(0.2, Vec2(30, 20));
    MoveBy* fly_1 = MoveBy::create(0.1, Vec2(10, 0));
    MoveBy* fly_2 = MoveBy::create(0.3, Vec2(10, 30));
    ScaleTo* scale = ScaleTo::create(0.6, 0.5);

    m_hurtShow->runAction(Spawn::create(Sequence::create(fly_0, fly_1, fly_2, NULL), scale, NULL));
}

void Role::EndHurt(){
    removeChild(m_hurtShow, true);
    m_moveable = true;
}

void Role::setMapSize(Size new_mapSize){
    m_mapSize = new_mapSize;
}

Size Role::getMapSize(){
    return m_mapSize;
}