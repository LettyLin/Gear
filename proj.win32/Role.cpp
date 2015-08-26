#include "Role.h"
#include "MapLayer.h"
#include "Global.h"
//构造函数，初始化动画并设置必要的状态
Role::Role() :
m_pStandAction(NULL),
m_pWalkAction(NULL),
m_pJumpAction(NULL),
m_moveable(true),
m_dropping(true),
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
    if (m_state == ROLE_STATE_DIE || (m_state == ROLE_STATE_JUMP)&&(m_dropping)){
        return false;
    }

    m_state = new_state;
    return true;
}

void Role::runStandAction(){
    if (ChangeState(ROLE_STATE_STAND)){
        this->stopAllActions();
        this->runAction(m_pStandAction);
    }
}

void Role::runWalkAction(){
    if (ChangeState(ROLE_STATE_WALK) && m_moveable){
        this->runAction(m_pWalkAction);
    }
}

void Role::runJumpAction(){
    if (ChangeState(ROLE_STATE_JUMP)){
        this->runAction(m_pJumpAction);
    }
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
    return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

BoundingBox Role::createBoundingBox(Vec2 origin, Size size){
    BoundingBox boundingBox;
    boundingBox.origin = Rect(origin.x, origin.y, size.width, size.height);
    boundingBox.actual = Rect(origin.x + getPositionX(), origin.y + getPositionY(), size.width, size.height);
    return boundingBox;
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
    Point lastPosition = getPosition();
    Point newPosition ;
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

    m_lastCollisionState = 0;

    //防止角色移出地图
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

    //检测碰撞
    Point finalPosition;
    global->CheckCollision(lastPosition, newPosition, getContentSize(), finalPosition, m_lastCollisionState);
    setPosition(finalPosition);

    if (m_lastCollisionState & ROLE_COLLISION_WALL  && m_lastCollisionState & ROLE_COLLISION_DROP){
        m_dropping= true;
        setVelocity(Vec2(0, m_velocity.y));
    }

    if (m_lastCollisionState & ROLE_COLLISION_WALL  && m_lastCollisionState & ROLE_COLLISION_FLOOR){
        m_dropping = false;
        setVelocity(Vec2(0, 0));
    }

    else if (m_lastCollisionState == ROLE_COLLISION_CORNER){
        m_dropping = false;
        setVelocity(Vec2(0, 0));
    }

    else if (m_lastCollisionState & ROLE_COLLISION_FLOOR){
        if (m_velocity.y > 0){
            setPosition(newPosition);
        }
        else if (m_lastCollisionState){
            m_dropping = false;
            setVelocity(Vec2(m_velocity.x, 0));
            if (m_velocity.x == 0){
                runStandAction();
            }
            else{
                runWalkAction();
            }
        }
    }
 
    else if (m_lastCollisionState & ROLE_COLLISION_DROP){
        m_dropping = true;
        runJumpAction();
    }

    this->updateBox(m_bodyBox);
}

void Role::setMapSize(Size new_mapSize){
    m_mapSize = new_mapSize;
}

Size Role::getMapSize(){
    return m_mapSize;
}