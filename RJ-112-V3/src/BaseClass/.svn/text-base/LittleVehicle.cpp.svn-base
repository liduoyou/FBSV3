#include "LittleVehicle.h"

LittleVehicle::LittleVehicle()
    : m_Forward(false)
    , m_Backward(false)
    , m_Braking(true)
    , m_changeBraking(false)
    , m_BrakingNumber(0)
    , m_Gear(0)
    , m_LimitStatus(0x3F)
    , m_speed(0.00)
    , m_distance(0.00)
    , m_MaxDistance(100.00)
    , m_NearMaxDistance(100.00)
    , m_MinDistance(100.00)
    , m_NearMinDistance(100.00)
    , m_MaxSpeed(100.00)
    , m_NearMaxSpeed(100.00)
{
}

LittleVehicle::~LittleVehicle()
{
}

void LittleVehicle::setForward(bool forward)
{
    m_Forward = forward;
}

bool LittleVehicle::getForward() const
{
    return m_Forward;
}

void LittleVehicle::setBackward(bool backward)
{
    m_Backward = backward;
}

bool LittleVehicle::getBackward() const
{
    return m_Backward;
}

void LittleVehicle::setBraking(bool braking)
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

bool LittleVehicle::getBraking() const
{
    return m_Braking;
}

//制动次数
void LittleVehicle::setBrakingNumber(quint64 brakeNumber)
{
    m_BrakingNumber = brakeNumber;
}

quint64 LittleVehicle::getBrakingNumber() const
{
    return m_BrakingNumber;
}

void LittleVehicle::setGear(int gear)
{
    m_Gear = gear;
}

int LittleVehicle::getGear() const
{
    return m_Gear;
}

//限位状态
void LittleVehicle::setLimitStatus(quint8 limitstatus)
{
    m_LimitStatus = limitstatus;
}

quint8 LittleVehicle::getLimitStatus() const
{
    return m_LimitStatus;
}
//速度
void LittleVehicle::setSpeed(double speed)
{
    m_speed = speed;
}

double LittleVehicle::getSpeed() const
{
    return m_speed;
}

//速度最值
void LittleVehicle::setMaxSpeed(double maxspeed)
{
    m_MaxSpeed = maxspeed;
}

double LittleVehicle::getMaxSpeed() const
{
    return m_MaxSpeed;
}

void LittleVehicle::setnearMaxSpeed(double nearmaxspeed)
{
    m_NearMaxSpeed = nearmaxspeed;
}

double LittleVehicle::getnearMaxSpeed() const
{
    return m_NearMaxSpeed;
}
//行程
void LittleVehicle::setDistance(double distance)
{
    m_distance = distance;
}

double LittleVehicle::getDistance() const
{
    return m_distance;
}
//行程最值
void LittleVehicle::setMaxDistance(double maxdistance)
{
    m_MaxDistance = maxdistance;
}

double LittleVehicle::getMaxDistance() const
{
    return m_MaxDistance;
}

void LittleVehicle::setnearMaxDistance(double nearmaxdistance)
{
    m_NearMaxDistance = nearmaxdistance;
}

double LittleVehicle::getnearMaxDistance() const
{
    return m_NearMaxDistance;
}

void LittleVehicle::setMinDistance(double mindistance)
{
    m_MinDistance = mindistance;
}

double LittleVehicle::getMinDistance() const
{
    return m_MinDistance;
}

void LittleVehicle::setnearMinDistance(double nearmindistance)
{
    m_NearMinDistance = nearmindistance;
}

double LittleVehicle::getnearMinDistance() const
{
    return m_NearMinDistance;
}
