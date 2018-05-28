#include "Hook.h"
Hook::Hook()
    : m_Up(false)
    , m_Down(false)
    , m_Braking(true)
    , m_changeBraking(false)
    , m_BrakingNumber(0)
    , m_Gear(0)
    , m_LimitStatus(0x3F)
    , m_Weight(0.0)
    , m_Height(0.0)
    , m_Speed(0.0)
    , m_Scope(0.0)
    , m_Moment(0.0)
    , m_MaxWeight(100.0)
    , m_NearMaxWeight(100.0)
    , m_MaxHeight(100.0)
    , m_NearMaxHeight(100.0)
    , m_MinHeight(100.0)
    , m_NearMinHeight(100.0)
    , m_MaxSpeed(100.0)
    , m_NearMaxSpeed(100.0)
    , m_MaxScope(100.0)
    , m_NearMaxScope(100.0)
    , m_MinScope(100.0)
    , m_NearMinScope(100.0)
    , m_MaxMoment(100.0)
    , m_NearMaxMoment(100.0)
{

}

Hook::~Hook()
{
}
// 上升
void Hook::setUp(bool up)
{
    m_Up = up;
}

bool Hook::getUp() const
{
    return m_Up;
}
//下降
void Hook::setDown(bool down)
{
    m_Down = down;
}

bool Hook::getDown() const
{
    return m_Down;
}
//制动
void Hook::setBraking(bool braking)
{
    m_Braking = braking;
    if(!m_Braking){
        m_changeBraking = m_Braking;
    }else{
        if(!m_changeBraking){
            m_BrakingNumber += 1;
        }
        m_changeBraking = m_Braking;
    }
}

bool Hook::getBraking() const
{
    return m_Braking;
}
//制动次数
void Hook::setBrakingNumber(quint64 brakeNumber)
{
    m_BrakingNumber = brakeNumber;
}

quint64 Hook::getBrakingNumber() const
{
    return m_BrakingNumber;
}
//档位
void Hook::setGear(int gear)
{
    m_Gear = gear;
}

int Hook::getGear() const
{
    return m_Gear;
}
//限位状态
void Hook::setLimitStatus(quint8 limitstatus)
{
    m_LimitStatus = limitstatus;
}

quint8 Hook::getLimitStatus() const
{
    return m_LimitStatus;
}
//重量
void Hook::setWeight(double weight)
{
    m_Weight = weight;
}

double Hook::getWeight() const
{
    return m_Weight;
}

void Hook::setMaxWeight(double maxweight)
{
    m_MaxWeight = maxweight;
}
//重量最值
double Hook::getMaxWeight() const
{
    return m_MaxWeight;
}
void Hook::setnearMaxWeight(double nearmaxweight)
{
    m_NearMaxWeight = nearmaxweight;
}

double Hook::getnearMaxWeight() const
{
    return m_NearMaxWeight;
}

//高度
void Hook::setHeight(double height)
{
    m_Height = height;
}

double Hook::getHeight() const
{
    return m_Height;
}

void Hook::setMaxHeight(double maxheight)
{
    m_MaxHeight = maxheight;
}

double Hook::getMaxHeight() const
{
    return m_MaxHeight;
}

void Hook::setnearMaxHeight(double nearmaxheight)
{
    m_NearMaxHeight = nearmaxheight;
}

double Hook::getnearMaxHeight() const
{
    return m_NearMaxHeight;
}

void Hook::setMinHeight(double minheight)
{
    m_MinHeight = minheight;
}

double Hook::getMinHeight() const
{
    return m_MinHeight;
}

void Hook::setnearMinHeight(double nearminheight)
{
    m_NearMinHeight = nearminheight;
}

double Hook::getnearMinHeight() const
{
    return m_NearMinHeight;
}

//速度
void Hook::setSpeed(double speed)
{
    m_Speed = speed;
}

double Hook::getSpeed() const
{
    return m_Speed;
}
//速度最值
void Hook::setMaxSpeed(double maxspeed)
{
    m_MaxSpeed = maxspeed;
}

double Hook::getMaxSpeed() const
{
    return m_MaxSpeed;
}

void Hook::setnearMaxSpeed(double nearmaxspeed)
{
    m_NearMaxSpeed = nearmaxspeed;
}

double Hook::getnearMaxSpeed() const
{
    return m_NearMaxSpeed;
}
//幅度
void Hook::setScope(double scope)
{
    m_Scope = scope;
}

double Hook::getScope() const
{
    return m_Scope;
}
void Hook::setMaxScope(double maxscope)
{
    m_MaxScope = maxscope;
}

double Hook::getMaxScope() const
{
    return m_MaxScope;
}

void Hook::setnearMaxScope(double nearmaxscope)
{
    m_NearMaxScope = nearmaxscope;
}

double Hook::getnearMaxScope() const
{
    return m_NearMaxScope;
}

void Hook::setMinScope(double minscope)
{
    m_MinScope = minscope;
}

double Hook::getMinScope() const
{
    return m_MinScope;
}

void Hook::setnearMinScope(double nearminscope)
{
    m_NearMinScope = nearminscope;
}

double Hook::getnearMinScope() const
{
    return m_NearMinScope;
}
//力矩
void Hook::setMoment(double moment)
{
    m_Moment = moment;
}

double Hook::getMoment() const
{
    return m_Moment;
}

void Hook::setMaxMoment(double maxmoment)
{
    m_MaxMoment = maxmoment;
}

double Hook::getMaxMoment() const
{
    return m_MaxMoment;
}

void Hook::setnearMaxMoment(double nearmaxmoment)
{
    m_NearMaxMoment = nearmaxmoment;
}

double Hook::getnearMaxMoment() const
{
    return m_NearMaxMoment;
}
