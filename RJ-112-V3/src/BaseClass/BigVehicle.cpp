#include "BigVehicle.h"

BigVehicle::BigVehicle()
    : m_Left(false)
    , m_Right(false)
    , m_Braking(true)
    , m_changeBraking(false)
    , m_BrakingNumber(0)
    , m_DoorLimit(false)
    , m_LeftRollerStatus(false)
    , m_RightRollerStatus(false)
    , m_RailClamp_SteelLeg(false)
    , m_RailClamp_SoftLeg(false)
    , m_Gear(0)
    , m_LimitStatus(0x3F)
    , m_OtherStatus(0xFF)
    , m_SteelLegDistance(0.0)
    , m_SoftLegDistance(0.0)
    , m_Distance(0.0)
    , m_SideswayDistance(0.0)
    , m_Speed(0)
    , m_WindSpeed(0)
    , m_Deflection(0.0)
    , m_MaxSteelLegDistance(100.00)
    , m_NearMaxSteelLegDistance(100.00)
    , m_MinSteelLegDistance(100.00)
    , m_NearMinSteelLegDistance(100.00)
    , m_MaxSoftLegDistance(100.00)
    , m_NearMaxSoftLegDistance(100.00)
    , m_MinSoftLegDistance(100.00)
    , m_NearMinSoftLegDistance(100.00)
    , m_MaxDistance(100.00)
    , m_NearMaxDistance(100.00)
    , m_MinDistance(100.00)
    , m_NearMinDistance(100.00)
    , m_MaxSideswayDistance(100.00)
    , m_NearMaxSideswayDistance(100.00)
    , m_MinSideswayDistance(100.00)
    , m_NearMinSideswayDistance(100.00)
    , m_MaxSpeed(100.00)
    , m_NearMaxSpeed(100.00)
    , m_MaxWindSpeed(17.1)
    , m_NearMaxWindSpeed(13.9)
    , m_MaxWindSpeedJIBIE(7.5)
    , m_NearMaxWindSpeedJIBIE(7.0)
    , m_MaxDeflection(100.0)
    , m_NearMaxDeflection(100.00)
{
}

BigVehicle::~BigVehicle()
{
}

void BigVehicle::setLeft(bool left)
{
    m_Left = left;
}

bool BigVehicle::getLeft() const
{
    return m_Left;
}

void BigVehicle::setRight(bool right)
{
    m_Right = right;
}

bool BigVehicle::getRight() const
{
    return m_Right;
}

void BigVehicle::setBraking(bool braking)
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

bool BigVehicle::getBraking() const
{
    return m_Braking;
}

//制动次数
void BigVehicle::setBrakingNumber(quint64 brakeNumber)
{
    m_BrakingNumber = brakeNumber;
}

quint64 BigVehicle::getBrakingNumber() const
{
    return m_BrakingNumber;
}

void BigVehicle::setRailDistanceStatus(bool railDistance)
{
    m_RailDistance = railDistance;
}

bool BigVehicle::getRailDistanceStatus() const
{
    return m_RailDistance;
}

void BigVehicle::setDoorLimit(bool doorlimit)
{
    m_DoorLimit = doorlimit;
}

bool BigVehicle::getDoorLimit() const
{
    return m_DoorLimit;
}

void BigVehicle::setLeftRollerStatus(bool leftRollerStatus)
{
    m_LeftRollerStatus = leftRollerStatus;
}

bool BigVehicle::getLeftRollerStatus() const
{
    return m_LeftRollerStatus;
}

void BigVehicle::setRightRollerStatus(bool rightRollerStatus)
{
    m_RightRollerStatus = rightRollerStatus;
}

bool BigVehicle::getRightRollerStatus() const
{
    return m_RightRollerStatus;
}

void BigVehicle::setrailclampSteelleg(bool steelLeg)
{
    m_RailClamp_SteelLeg = steelLeg;
}

bool BigVehicle::getrailclampSteelleg() const
{
    return m_RailClamp_SteelLeg;
}

void BigVehicle::setrailclampSoftleg(bool softLeg)
{
    m_RailClamp_SoftLeg = softLeg;
}

bool BigVehicle::getrailclampSoftleg() const
{
    return m_RailClamp_SoftLeg;
}

void BigVehicle::setGear(int gear)
{
    m_Gear = gear;
}

int BigVehicle::getGear() const
{
    return m_Gear;
}

//限位状态
void BigVehicle::setLimitStatus(quint8 limitstatus)
{
    m_LimitStatus = limitstatus;
}

quint8 BigVehicle::getLimitStatus() const
{
    return m_LimitStatus;
}
//其他状态
void BigVehicle::setOtherStatus(quint8 othertatus)
{
    m_OtherStatus = othertatus;
}

quint8 BigVehicle::getOtherStatus() const
{
    return m_OtherStatus;
}
//钢腿行程
void BigVehicle::setSteelLegDistance(double steeldistance)
{
    m_SteelLegDistance = steeldistance;
}

double BigVehicle::getSteelLegDistance() const
{
    return m_SteelLegDistance;
}

//钢腿行程最值
void BigVehicle::setMaxSteelLegDistance(double maxsteeldistance)
{
    m_MaxSteelLegDistance = maxsteeldistance;
}

double BigVehicle::getMaxSteelLegDistance() const
{
    return m_MaxSteelLegDistance;
}

void BigVehicle::setnearMaxSteelLegDistance(double nearmaxsteeldistance)
{
    m_NearMaxSteelLegDistance = nearmaxsteeldistance;
}

double BigVehicle::getnearMaxSteelLegDistance() const
{
    return m_NearMaxSteelLegDistance;
}

void BigVehicle::setMinSteelLegDistance(double minsteeldistance)
{
    m_MinSteelLegDistance = minsteeldistance;
}

double BigVehicle::getMinSteelLegDistance() const
{
    return m_MinSteelLegDistance;
}

void BigVehicle::setnearMinSteelLegDistance(double nearminsteeldistance)
{
    m_NearMinSteelLegDistance = nearminsteeldistance;
}

double BigVehicle::getnearMinSteelLegDistance() const
{
    return m_NearMinSteelLegDistance;
}
//柔腿行程
void BigVehicle::setSoftLegDistance(double softdistance)
{
    m_SoftLegDistance = softdistance;
}

double BigVehicle::getSoftLegDistance() const
{
    return m_SoftLegDistance;
}
//柔腿行程最值
void BigVehicle::setMaxSoftLegDistance(double maxsoftdistance)
{
    m_MaxSoftLegDistance = maxsoftdistance;
}

double BigVehicle::getMaxSoftLegDistance() const
{
    return m_MaxSoftLegDistance;
}

void BigVehicle::setnearMaxSoftLegDistance(double nearmaxsoftdistance)
{
    m_NearMaxSoftLegDistance = nearmaxsoftdistance;
}

double BigVehicle::getnearMaxSoftLegDistance() const
{
    return m_NearMaxSoftLegDistance;
}

void BigVehicle::setMinSoftLegDistance(double minsoftdistance)
{
    m_MinSoftLegDistance = minsoftdistance;
}

double BigVehicle::getMinSoftLegDistance() const
{
    return m_MinSoftLegDistance;
}

void BigVehicle::setnearMinSoftLegDistance(double nearminsoftdistance)
{
    m_NearMinSoftLegDistance = nearminsoftdistance;
}

double BigVehicle::getnearMinSoftLegDistance() const
{
    return m_NearMinSoftLegDistance;
}
//速度
void BigVehicle::setSpeed(double speed)
{
    m_Speed = speed;
}

double BigVehicle::getSpeed() const
{
    return m_Speed;
}

//速度最值
void BigVehicle::setMaxSpeed(double maxspeed)
{
    m_MaxSpeed = maxspeed;
}

double BigVehicle::getMaxSpeed() const
{
    return m_MaxSpeed;
}

void BigVehicle::setnearMaxSpeed(double nearmaxspeed)
{
    m_NearMaxSpeed = nearmaxspeed;
}

double BigVehicle::getnearMaxSpeed() const
{
    return m_NearMaxSpeed;
}
//风速
void BigVehicle::setWindSpeed(double windSpeed)
{
    m_WindSpeed = windSpeed;
}

double BigVehicle::getWindSpeed() const
{
    return m_WindSpeed;
}

//风速最值
void BigVehicle::setMaxWindSpeed(double maxwindspeed)
{
    m_MaxWindSpeed = maxwindspeed;
}

double BigVehicle::getMaxWindSpeed() const
{
    return m_MaxWindSpeed;
}

void BigVehicle::setnearMaxWindSpeed(double nearmaxwindspeed)
{
    m_NearMaxWindSpeed = nearmaxwindspeed;
}

double BigVehicle::getnearMaxWindSpeed() const
{
    return m_NearMaxWindSpeed;
}

//风速级别最值
void BigVehicle::setMaxWindSpeedJIBIE(double maxwindspeedjibie)
{
    m_MaxWindSpeedJIBIE = maxwindspeedjibie;
}

double BigVehicle::getMaxWindSpeedJIBIE() const
{
    return m_MaxWindSpeedJIBIE;
}

void BigVehicle::setnearMaxWindSpeedJIBIE(double nearmaxwindspeedjibie)
{
    m_NearMaxWindSpeedJIBIE = nearmaxwindspeedjibie;
}

double BigVehicle::getnearMaxWindSpeedJIBIE() const
{
    return m_NearMaxWindSpeedJIBIE;
}
//偏斜
void BigVehicle::setDeflection(double deflection)
{
    m_Deflection = deflection;
}

double BigVehicle::getDeflection() const
{
    return m_Deflection;
}

//偏斜最值
void BigVehicle::setMaxDeflection(double maxdeflection)
{
    m_MaxDeflection = maxdeflection;
}

double BigVehicle::getMaxDeflection() const
{
    return m_MaxDeflection;
}

void BigVehicle::setnearMaxDeflection(double nearmaxdeflection)
{
    m_NearMaxDeflection = nearmaxdeflection;
}

double BigVehicle::getnearMaxDeflection() const
{
    return m_NearMaxDeflection;
}
//整车纵移
void BigVehicle::setDistance(double distance)
{
    m_Distance = distance;
}

double BigVehicle::getDistance() const
{
    return m_Distance;
}

//整车纵移最值
void BigVehicle::setMaxDistance(double maxdistance)
{
    m_MaxDistance = maxdistance;
}

double BigVehicle::getMaxDistance() const
{
    return m_MaxDistance;
}

void BigVehicle::setnearMaxDistance(double nearmaxdistance)
{
    m_NearMaxDistance = nearmaxdistance;
}

double BigVehicle::getnearMaxDistance() const
{
    return m_NearMaxDistance;
}

void BigVehicle::setMinDistance(double mindistance)
{
    m_MinDistance = mindistance;
}

double BigVehicle::getMinDistance() const
{
    return m_MinDistance;
}

void BigVehicle::setnearMinDistance(double nearmindistance)
{
    m_NearMinDistance = nearmindistance;
}

double BigVehicle::getnearMinDistance() const
{
    return m_NearMinDistance;
}
//整车横移
void BigVehicle::setSideswayDistance(double sideswaydistance)
{
    m_SideswayDistance = sideswaydistance;
}

double BigVehicle::getSideswayDistance() const
{
    return m_SideswayDistance;
}

//整车横移最值
void BigVehicle::setMaxSideswayDistance(double maxsideswaydistance)
{
    m_MaxSideswayDistance = maxsideswaydistance;
}

double BigVehicle::getMaxSideswayDistance() const
{
    return m_MaxSideswayDistance;
}

void BigVehicle::setnearMaxSideswayDistance(double nearmaxsideswaydistance)
{
    m_NearMaxSideswayDistance = nearmaxsideswaydistance;
}

double BigVehicle::getnearMaxSideswayDistance() const
{
    return m_NearMaxSideswayDistance;
}

void BigVehicle::setMinSideswayDistance(double minsideswaydistance)
{
    m_MinSideswayDistance = minsideswaydistance;
}

double BigVehicle::getMinSideswayDistance() const
{
    return m_MinSideswayDistance;
}

void BigVehicle::setnearMinSideswayDistance(double nearminsideswaydistance)
{
    m_NearMinSideswayDistance = nearminsideswaydistance;
}

double BigVehicle::getnearMinSideswayDistance() const
{
    return m_NearMinSideswayDistance;
}

double BigVehicle::getWindspeedJIBIE() const
{
    /*0	无风	0.0-0.2
1	软风	0.3-1.5
2	轻风	1.6-3.3
3	微风	3.4-5.4
4	和风	5.5-7.9
5	清风	8.0-10.7
6	强风	10.8-13.8
7	劲风（疾风）	13.9-17.1
8	大风	17.2-20.7
9	烈风	20.8-24.4
10	狂风	24.5-28.4
11	暴风	28.5-32.6
*/
    double temp = 0;
    double windspeed;
    windspeed = getWindSpeed();

    if(windspeed >= 0.0 && windspeed <= 0.2){
        temp = 0.0;
    }else if(windspeed >= 0.3 && windspeed <= 1.5){
        if(windspeed>=0.3&& windspeed <=0.4){
            temp = 1.0;
        }
        else if(windspeed>0.4&& windspeed <=0.55){
            temp = 1.1;
        }
        else if(windspeed>0.55&& windspeed <=0.8){
            temp = 1.2;
        }
        else if(windspeed>0.8&& windspeed <=0.9){
            temp = 1.3;
        }
        else if(windspeed>0.9&& windspeed <=1.0){
            temp = 1.4;
        }
        else if(windspeed>1.0&& windspeed <=1.1){
            temp = 1.5;
        }
        else if(windspeed>1.1&& windspeed <=1.2){
            temp = 1.6;
        }
        else if(windspeed>1.2&& windspeed <=1.3){
            temp = 1.7;
        }
        else if(windspeed>1.3&& windspeed <=1.4){
            temp = 1.8;
        }
        else if(windspeed>1.4&& windspeed <=1.5){
            temp = 1.9;
        }
    }else if(windspeed >= 1.6 && windspeed <= 3.3){
        if(windspeed>=1.6&& windspeed <=1.8){
            temp = 2.0;
        }
        else if(windspeed>1.8&& windspeed <=2.0){
            temp = 2.1;
        }
        else if(windspeed>2.0&& windspeed <=2.2){
            temp = 2.2;
        }
        else if(windspeed>2.2&& windspeed <=2.4){
            temp = 2.3;
        }
        else if(windspeed>2.4&& windspeed <=2.6){
            temp = 2.4;
        }
        else if(windspeed>2.6&& windspeed <=2.8){
            temp = 2.5;
        }
        else if(windspeed>2.8&& windspeed <=3.0){
            temp = 2.6;
        }
        else if(windspeed>3.0&& windspeed <=3.1){
            temp = 2.7;
        }
        else if(windspeed>3.1&& windspeed <=3.2){
            temp = 2.8;
        }
        else if(windspeed>3.2&& windspeed <=3.3){
            temp = 2.9;
        }
    }else if(windspeed >= 3.4 && windspeed <= 5.4){
        if(windspeed>=3.4&& windspeed <=3.6){
            temp = 3.0;
        }
        else if(windspeed>3.6&& windspeed <=3.8){
            temp = 3.1;
        }
        else if(windspeed>3.8&& windspeed <=4.0){
            temp = 3.2;
        }
        else if(windspeed>4.0&& windspeed <=4.2){
            temp = 3.3;
        }
        else if(windspeed>4.2&& windspeed <=4.4){
            temp = 3.4;
        }
        else if(windspeed>4.4&& windspeed <=4.6){
            temp = 3.5;
        }
        else if(windspeed>4.6&& windspeed <=4.8){
            temp = 3.6;
        }
        else if(windspeed>4.8&& windspeed <=5.0){
            temp = 3.7;
        }
        else if(windspeed>5.0&& windspeed <=5.2){
            temp = 3.8;
        }
        else if(windspeed>5.2&& windspeed <=5.4){
            temp = 3.9;
        }
    }else if(windspeed >= 5.5 && windspeed <= 7.9){
        if(windspeed>=5.5&& windspeed <=5.8){
            temp = 4.0;
        }
        else if(windspeed>5.8&& windspeed <=6.1){
            temp = 4.1;
        }
        else if(windspeed>6.1&& windspeed <=6.3){
            temp = 4.2;
        }
        else if(windspeed>6.3&& windspeed <=6.6){
            temp = 4.3;
        }
        else if(windspeed>6.6&& windspeed <=6.8){
            temp = 4.4;
        }
        else if(windspeed>6.8&& windspeed <=7.1){
            temp = 4.5;
        }
        else if(windspeed>7.1&& windspeed <=7.3){
            temp = 4.6;
        }
        else if(windspeed>7.3&& windspeed <=7.5){
            temp = 4.7;
        }
        else if(windspeed>7.5&& windspeed <=7.7){
            temp = 4.8;
        }
        else if(windspeed>7.7&& windspeed <=7.9){
            temp = 4.9;
        }
    }else if(windspeed >= 8.0 && windspeed <= 10.7){
        if(windspeed>=8.0&& windspeed <8.3){
            temp = 5.0;
        }
        else if(windspeed>8.3&& windspeed <=8.6){
            temp = 5.1;
        }
        else if(windspeed>8.6&& windspeed <=8.9){
            temp = 5.2;
        }
        else if(windspeed>8.9&& windspeed <=9.2){
            temp = 5.3;
        }
        else if(windspeed>9.2&& windspeed <=9.5){
            temp = 5.4;
        }
        else if(windspeed>9.5&& windspeed <=9.7){
            temp = 5.5;
        }
        else if(windspeed>9.7&& windspeed <=9.9){
            temp = 5.6;
        }
        else if(windspeed>9.9&& windspeed <=10.2){
            temp = 5.7;
        }
        else if(windspeed>10.2&& windspeed <=10.5){
            temp = 5.8;
        }
        else if(windspeed>10.5&& windspeed <=10.7){
            temp = 5.9;
        }
    }else if(windspeed >= 10.8 && windspeed <= 13.8){
        if(windspeed>=10.8&& windspeed <11.1){
            temp = 6.0;
        }
        else if(windspeed>11.1&& windspeed <=11.4){
            temp = 6.1;
        }
        else if(windspeed>11.4&& windspeed <=11.7){
            temp = 6.2;
        }
        else if(windspeed>11.7&& windspeed <=12.0){
            temp = 6.3;
        }
        else if(windspeed>12.0&& windspeed <=12.3){
            temp = 6.4;
        }
        else if(windspeed>12.3&& windspeed <=12.6){
            temp = 6.5;
        }
        else if(windspeed>12.6&& windspeed <=12.9){
            temp = 6.6;
        }
        else if(windspeed>12.9&& windspeed <=13.1){
            temp = 6.7;
        }
        else if(windspeed>13.1&& windspeed <=13.5){
            temp = 6.8;
        }
        else if(windspeed>13.5&& windspeed <=13.8){
            temp = 6.9;
        }
    }else if(windspeed >= 13.9 && windspeed <= 17.1){
        if(windspeed>=13.9&& windspeed <14.1){
            temp = 7.0;
        }
        else if(windspeed>14.1&& windspeed <=14.4){
            temp = 7.1;
        }
        else if(windspeed>14.4&& windspeed <=14.7){
            temp = 7.2;
        }
        else if(windspeed>14.7&& windspeed <=15.0){
            temp = 7.3;
        }
        else if(windspeed>15.0&& windspeed <=15.3){
            temp = 7.4;
        }
        else if(windspeed>15.3&& windspeed <=16.6){
            temp = 7.5;
        }
        else if(windspeed>16.6&& windspeed <=16.9){
            temp = 7.6;
        }
        else if(windspeed>16.9&& windspeed <=17.1){
            temp = 7.7;
        }
        else if(windspeed>13.1&& windspeed <=13.5){
            temp = 7.8;
        }
        else if(windspeed>13.5&& windspeed <=13.8){
            temp = 7.9;
        }
    }else if(windspeed >= 17.2 && windspeed <= 20.7){
        if(windspeed>=17.2&& windspeed <18.1){
            temp = 8.0;
        }
        else if(windspeed>18.1&& windspeed <=18.4){
            temp = 8.1;
        }
        else if(windspeed>18.4&& windspeed <=18.7){
            temp = 8.2;
        }
        else if(windspeed>18.7&& windspeed <=19.0){
            temp = 8.3;
        }
        else if(windspeed>19.0&& windspeed <=19.3){
            temp = 8.4;
        }
        else if(windspeed>19.3&& windspeed <=19.6){
            temp = 8.5;
        }
        else if(windspeed>19.6&& windspeed <=19.9){
            temp = 8.6;
        }
        else if(windspeed>19.9&& windspeed <=20.1){
            temp = 8.7;
        }
        else if(windspeed>20.1&& windspeed <=20.3){
            temp = 8.8;
        }
        else if(windspeed>20.3&& windspeed <=20.7){
            temp = 8.9;
        }
    }else if(windspeed >= 20.8 && windspeed <= 24.4){
        if(windspeed>=20.8&& windspeed <21.1){
            temp = 9.0;
        }
        else if(windspeed>21.1&& windspeed <=21.4){
            temp = 9.1;
        }
        else if(windspeed>21.4&& windspeed <=21.7){
            temp = 9.2;
        }
        else if(windspeed>21.7&& windspeed <=22.0){
            temp = 9.3;
        }
        else if(windspeed>22.0&& windspeed <=22.3){
            temp = 9.4;
        }
        else if(windspeed>22.3&& windspeed <=22.6){
            temp = 9.5;
        }
        else if(windspeed>22.6&& windspeed <=22.9){
            temp = 9.6;
        }
        else if(windspeed>22.9&& windspeed <=23.5){
            temp = 9.7;
        }
        else if(windspeed>23.5&& windspeed <=24.0){
            temp = 9.8;
        }
        else if(windspeed>24.0&& windspeed <=24.4){
            temp = 9.9;
        }
    }else if(windspeed >= 24.5 && windspeed <= 28.4){
        if(windspeed>=24.5&& windspeed <24.8){
            temp = 10.0;
        }
        else if(windspeed>24.8&& windspeed <=25.1){
            temp = 10.1;
        }
        else if(windspeed>25.1&& windspeed <=25.4){
            temp = 10.2;
        }
        else if(windspeed>25.4&& windspeed <=25.7){
            temp = 10.3;
        }
        else if(windspeed>25.7&& windspeed <=26.0){
            temp = 10.4;
        }
        else if(windspeed>26.0&& windspeed <=26.3){
            temp = 10.5;
        }
        else if(windspeed>26.3&& windspeed <=26.6){
            temp = 10.6;
        }
        else if(windspeed>26.6&& windspeed <=26.9){
            temp = 10.7;
        }
        else if(windspeed>26.9&& windspeed <=27.1){
            temp = 10.8;
        }
        else if(windspeed>27.1&& windspeed <=28.4){
            temp = 10.9;
        }
    }else if(windspeed >= 28.5 && windspeed <= 32.6){
        if(windspeed>=28.5&& windspeed <=28.8){
            temp = 11.0;
        }
        else if(windspeed>28.8&& windspeed <=29.1){
            temp = 11.1;
        }
        else if(windspeed>29.1&& windspeed <=29.4){
            temp = 11.2;
        }
        else if(windspeed>29.4&& windspeed <=29.7){
            temp = 11.3;
        }
        else if(windspeed>29.7&& windspeed <=30.0){
            temp = 11.4;
        }
        else if(windspeed>30.0&& windspeed <=31.3){
            temp = 11.5;
        }
        else if(windspeed>31.3&& windspeed <=31.6){
            temp = 11.6;
        }
        else if(windspeed>31.6&& windspeed <=31.9){
            temp = 11.7;
        }
        else if(windspeed>31.9&& windspeed <=32.2){
            temp = 11.8;
        }
        else if(windspeed>32.2&& windspeed <=32.6){
            temp = 11.9;
        }
    }else if(windspeed > 32.7){
        temp = 12.0;
    }
    return temp;
}
