#include "Role.h"
#include "MapLayer.h"
#include "Global.h"
//构造函数，初始化动画并设置必要的状态
Role::Role() :
m_pStandAction(NULL),
m_pWalkAction(NULL),
m_pJumpAction(NULL),
m_pDropAction(NULL),
m_pCrouchAction(NULL),
m_pStandupAction(NULL),
m_pAttackAction(NULL),
m_pWalkAttackAction(NULL),
m_pJumpAttackAction(NULL), 
m_pSpecialAttackAction(NULL),
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
        CC_SAFE_RELEASE_NULL(m_pStandAction);
        CC_SAFE_RELEASE_NULL(m_pWalkAction);
        CC_SAFE_RELEASE_NULL(m_pJumpAction);
        CC_SAFE_RELEASE_NULL(m_pDropAction);
        CC_SAFE_RELEASE_NULL(m_pCrouchAction);
        CC_SAFE_RELEASE_NULL(m_pStandupAction);
        CC_SAFE_RELEASE_NULL(m_pJumpAction);
        CC_SAFE_RELEASE_NULL(m_pAttackAction);
        CC_SAFE_RELEASE_NULL(m_pWalkAttackAction);
        CC_SAFE_RELEASE_NULL(m_pJumpAttackAction);
        CC_SAFE_RELEASE_NULL(m_pSpecialAttackAction);
        CC_SAFE_RELEASE_NULL(m_pHurtAction);
        CC_SAFE_RELEASE_NULL(m_pDieAction);
        //CC_SAFE_RELEASE_NULL(m_hurtShow);
}

//根据当前状态判断是否可以转换到期望状态
bool Role::ChangeState(const eRoleState new_state){
    m_state = new_state;
    return true;
}

void Role::runStandAction(){
    stopAllActions();
    this->runAction(m_pStandAction);
}

void Role::runWalkAction(){
    stopAllActions();
    this->runAction(m_pWalkAction);
}

void Role::runJumpAction(){
    stopAllActions();
    this->runAction(m_pJumpAction);
}

void Role::runDropAction(){
    stopAllActions();
    this->runAction(m_pDropAction);
}

void Role::runCrouchAction(){
    stopAllActions();
    this->runAction(m_pCrouchAction);
}

void Role::runStandupAction(){
    stopAllActions();
    this->runAction(m_pStandupAction);
}

void Role::runWalkAttackAction(){
    stopAllActions();
    this->runAction(m_pWalkAttackAction);
}

void Role::runJumpAttackAction(){
    stopAllActions();
    this->runAction(m_pJumpAttackAction);
}

void Role::runSpecialAttackAction(){
    stopAllActions();
    this->runAction(m_pSpecialAttackAction);
}

void Role::runAttackAction(){
    stopAllActions();
    this->runAction(m_pAttackAction);
}

void Role::runHurtAction(){
    stopAllActions();
    this->runAction(m_pHurtAction);
}

void Role::runDieAction(){
    stopAllActions();
    this->runAction(m_pDieAction);
}

void Role::onStand(){
    if (ChangeState(ROLE_STATE_STAND)){
        runStandAction();
    }
}

void Role::onWalk(){
    if (ChangeState(ROLE_STATE_WALK)){
        runWalkAction();
    }
}

void Role::onJump(){
    m_lastJump = m_bodyBox.actual.origin;

    if (ChangeState(ROLE_STATE_JUMP)){
        runJumpAction();
    }
    m_moveable = false;
}

void Role::onDrop(){
    if (ChangeState(ROLE_STATE_DROP)){
        //runDropAction();
    }
    m_moveable = false;
}

void Role::onCrouch(){
    if (ChangeState(ROLE_STATE_CROUCH)){
        runCrouchAction();
    }
    m_moveable = false;
}

void Role::onStandup(){
    runStandupAction();
}

void Role::onWalkAttack(){
    if (ChangeState(ROLE_STATE_ATTACK)){
        runWalkAttackAction();
    }
    m_moveable = false;
}

void Role::onJumpAttack(){
    if (ChangeState(ROLE_STATE_ATTACK)){
        runJumpAttackAction();
    }
    m_moveable = false;
}

void Role::onSpecialAttack(){
    if (ChangeState(ROLE_STATE_ATTACK)){
        runSpecialAttackAction();
    }
    m_moveable = false;
}

void Role::onAttack(){
    if (ChangeState(ROLE_STATE_ATTACK)){
        runAttackAction();
    }
    m_moveable = false;
}

void Role::onHurt(int hurt){
    if (m_hurtShow != NULL){
        removeChild(m_hurtShow, true);
    }

    ShowHurt(hurt);
    if (ChangeState(ROLE_STATE_HURT)){
        runHurtAction();
    }
    m_moveable = false;
}

void Role::onDie(){
    EndHurt();

    if (ChangeState(ROLE_STATE_DIE)){
        runDieAction();
        die();
    }
    m_moveable = false;
    m_velocity = Vec2::ZERO;
}

void Role::updateBox(BoundingBox &box){
    Vec2 origin = box.origin.origin;
    Size size = box.origin.size;
    if (m_direction == ROLE_DIRECTION_RIGHT){
        box.actual = Rect(origin.x +getPositionX(), origin.y + getPositionY(), size.width, size.height);
    }
    else{
        box.actual = Rect(getContentSize().width - origin.x - size.width + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    }
}

void Role::update(){
    if (m_currentHp <= 0 && m_moveable){
        onDie();
        return;
    }

    if (m_direction == ROLE_DIRECTION_LEFT){
        if (isFlippedX()){
            setFlippedX(false);
        }
    }
    else{
        if (!isFlippedX()){
            setFlippedX(true);
        }
    }

    m_lastCollisionState = 0;
    Point newPosition = getNextPosition();
    //检测碰撞
    checkCollisionWithMap(newPosition);

    Point finalPosition;
    GameUtile::CheckCollision(this, newPosition, finalPosition, m_lastCollisionState);


    if (m_lastCollisionState & ROLE_COLLISION_WALL){
        setVelocity(Vec2(0, m_velocity.y));
    }

    if (m_lastCollisionState & ROLE_COLLISION_FLOOR){
        if (m_dropping){
            m_dropping = false;
            EnableMoveable();
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
        if (!m_dropping){
            m_dropping = true;
            onDrop();
        }
    }

    setPosition(finalPosition - m_bodyBox.origin.origin);
    updateAllBox();
}

Point Role::getNextPosition(){
    Point lastPosition = m_bodyBox.actual.origin;
    Point newPosition;
    Size roleSize = m_bodyBox.actual.size;

    if (m_dropping && m_velocity.y > -4){
        m_velocity.y -= 0.4;
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

void Role::ShowHurt(int hurt){
    const char* str_hurt = String::createWithFormat("%d", hurt)->getCString();
    m_hurtShow = Label::create(str_hurt, "COMIC SANS MS", 50);
    m_hurtShow->setColor(Color3B(255, 30, 20));
    m_hurtShow->setAnchorPoint(Vec2::ZERO);
    m_hurtShow->setPosition(Vec2(30, 80));
   
    MoveBy* fly_0 = MoveBy::create(0.2, Vec2(30, 20));
    MoveBy* fly_1 = MoveBy::create(0.1, Vec2(10, 0));
    MoveBy* fly_2 = MoveBy::create(0.3, Vec2(10, 30));
    ScaleTo* scale = ScaleTo::create(0.6, 0.5);

    addChild(m_hurtShow);

    m_hurtShow->runAction(Sequence::create(
        Spawn::create(Sequence::create(fly_0, fly_1, fly_2, NULL), scale, NULL),
        CallFuncN::create(CC_CALLBACK_0(Role::EndHurt, this)),
        NULL));
}

void Role::EnableMoveable(){
    m_moveable = true;
    onStand();
}

void Role::EndHurt(){
    removeChild(m_hurtShow, true);
}

void Role::setMapSize(Size new_mapSize){
    m_mapSize = new_mapSize;
}

Size Role::getMapSize(){
    return m_mapSize;
}