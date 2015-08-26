#include "Role.h"
#include "MapLayer.h"
#include "Global.h"
//���캯������ʼ�����������ñ�Ҫ��״̬
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

//�����������ͷŶ�����ռ�õ��ڴ�
Role::~Role(){
    /*CC_SAFE_RELEASE_NULL (m_pStandAction);
    CC_SAFE_RELEASE_NULL(m_pWalkAction);*/
}

//���ݵ�ǰ״̬�ж��Ƿ����ת��������״̬
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
    //���ݱ�ţ���ʽ��֡��������֡������ж�����Ӧ֡���棬���֡����
    for (int i = 0; i < frame_count; ++i){
        const char* ImgName = String::createWithFormat(format_string, i)->getCString();
        SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ImgName);
        pFrames.insert(i, pFrame);
    }

    //��֡���鴴��Ϊ����
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

    //�����ɫ��һ֡��λ��
    if (ROLE_DIRECTION_RIGHT == m_direction){
        newPosition.x = lastPosition.x + m_velocity.x;
        newPosition.y = lastPosition.y + m_velocity.y;
    }
    else{
        newPosition.x = lastPosition.x - m_velocity.x;
        newPosition.y = lastPosition.y + m_velocity.y;
    }

    m_lastCollisionState = 0;

    //��ֹ��ɫ�Ƴ���ͼ
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

    //�����ײ
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