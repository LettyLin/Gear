/*
    Role类
    所有角色，怪物，Boss，NPC的基类。
    包含状态枚举定义和公共的属性和动作的声明
*/
#ifndef _H_ROLE_
#define _H_ROLE_

#include <cocos2d.h>
USING_NS_CC;

//定义盒子模型用于进行攻击，对话等范围判定
struct BoundingBox {
    //绝对位置的盒子模型
    Rect actual;
    //相对位置的盒子模型
    Rect origin;
};

//定义角色的所有可能状态
enum eRoleState{
    ROLE_STATE_STAND = 0,
    ROLE_STATE_WALK,
    ROLE_STATE_RUSH,
    ROLE_STATE_JUMP,
    ROLE_STATE_CROUCH,
    ROLE_STATE_ATTACK,
    ROLE_STATE_RUSHATTACK,
    ROLE_STATE_SKILL,
    ROLE_STATE_HURT,
    ROLE_STATE_DIE
};

//定义角色的面向方向
enum eRoleDirection{
    ROLE_DIRECTION_LEFT, 
    ROLE_DIRECTION_RIGHT
};

enum eCollisionState{
    ROLE_COLLISION_NULL = 1 << 0,
    ROLE_COLLISION_FLOOR = 1 << 1,
    ROLE_COLLISION_WALL =  1 << 2,
    ROLE_COLLISION_BOUNCE = 1 << 3,
    ROLE_COLLISION_DROP = 1 << 4,
    ROLE_COLLISION_SLOPE = 1 << 5,
    ROLE_COLLISION_CORNER = ROLE_COLLISION_NULL | ROLE_COLLISION_WALL
};

class Role : public Sprite{
public:
    Role();
    virtual ~Role();

    //利用CC_SYNTHESIZE宏便捷地添加角色属性
    CC_SYNTHESIZE(int, m_currentHp, CurrentHp);
    CC_SYNTHESIZE(int, m_maxHp, MaxHp);
    CC_SYNTHESIZE(int, m_currentMp, CurrentMp);
    CC_SYNTHESIZE(int, m_maxMp, MaxMp);
    CC_SYNTHESIZE(int, m_strenth, Strenth);
    CC_SYNTHESIZE(int, m_defence, Defence);
    CC_SYNTHESIZE(Vec2, m_velocity, Velocity);

    //Add other properties here

    CC_SYNTHESIZE(eRoleDirection, m_direction, Direction);
    CC_SYNTHESIZE(eRoleState, m_state, State);
    CC_SYNTHESIZE(bool, m_moveable, Moveable);
    CC_SYNTHESIZE(bool, m_dropping, Dropping);
    CC_SYNTHESIZE(bool, m_onSlope, OnSlope);
    CC_SYNTHESIZE(eRoleDirection, m_SlopeDirection, SlopeDirection);
    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
    CC_SYNTHESIZE(Point, m_lastJump, LastJump);

    //状态变更函数
    bool ChangeState(const eRoleState new_state);

    //生命各个动画属性和相应函数，并将其retain，以使动画能长期保存在内存中
    CC_SYNTHESIZE_RETAIN(Action*, m_pStandAction, StandAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pWalkAction, WalkAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pJumpAction, JumpAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pAttackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pHurtAction, HurtAction);
    CC_SYNTHESIZE_RETAIN(Action*, m_pDieAction, DieAction);

    //Add other actions here

    //播放动画
    virtual void runStandAction();
    virtual void runWalkAction();
    virtual void runJumpAction();
    virtual void runAttackAction();
    virtual void runHurtAction();
    virtual void runDieAction();

    //尝试执行动作
    virtual void onStand();
    virtual void onWalk();
    virtual void onJump();
    virtual void onAttack();
    virtual void onHurt(int hurt);
    virtual void onDie();

    //更新角色
    virtual void update();
    virtual Point getNextPosition();
    virtual void checkCollisionWithMap(Point &newPosition);
    virtual void updateAllBox();

    virtual void die();


    //创建常规动画（帧名相同，编号从0开始）
    Animation* createNormalAction(const char* format_string, int frame_count, int fps);
    //CallFunc* createIdleCallbackFunc()

    BoundingBox createBoundingBox(Vec2 origin, Size size);
    void updateBox(BoundingBox& box);

    void ShowHurt(int hurt);
    void EndHurt();

    //当地图改变时，接受通知
    void setMapSize(Size new_mapsize);
    Size getMapSize();

protected:
    Label* m_hurtShow;

    Size m_mapSize;    //存储地图大小
    int m_lastCollisionState;
};

#endif