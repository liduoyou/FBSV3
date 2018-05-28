#ifndef BIGVEHICLE_H
#define BIGVEHICLE_H

#include <QObject>

class BigVehicle
{
public:
    enum BigVehicleType{
        //门式起重机，提梁机，缆索吊机
        BVtype_ALL,               //包括刚腿柔腿行程/风速/速度/偏斜;
        BVtype_NoSpeed,           //不包括速度;
        BVtype_OneDistance,       //无纠偏，只包括一个行程/风速;
        BVtype_OnlyWind,          //仅风速

        //架桥机，桥面吊机
        BVtype_NO5,      //整机纵移1，整机横移1，整机纵移2，整机横移2，风速，左右支腿水平度;
        BVtype_NO6,      //整机纵移，整机横移，风速，左右支腿水平度;
        BVtype_NO7,      //整机纵移，整机横移，风速，左右水平度;(桥面吊机)
        BVtype_NO8       //风速，左右水平度;(桥面吊机)
    };
    BigVehicle();
    ~BigVehicle();

    void setLeft(bool left);
    bool getLeft()const;
    void setRight(bool right);
    bool getRight()const;

    void setBraking(bool braking);
    bool getBraking()const;
    void setBrakingNumber(quint64 brakeNumber);
    quint64 getBrakingNumber()const;

    void setRailDistanceStatus(bool railDistance);
    bool getRailDistanceStatus()const;

    void setDoorLimit(bool doorlimit);
    bool getDoorLimit()const;

    void setLeftRollerStatus(bool leftRollerStatus);
    bool getLeftRollerStatus()const;
    void setRightRollerStatus(bool rightRollerStatus);
    bool getRightRollerStatus()const;

    void setrailclampSteelleg(bool steelLeg);
    bool getrailclampSteelleg()const;
    void setrailclampSoftleg(bool softLeg);
    bool getrailclampSoftleg()const;

    void setGear(int gear);
    int getGear()const;
    //限位状态 8bit从高位到低位依次: 0 0 左极限限位 右极限限位 左减速限位 右减速限位 左限位 右限位
    void setLimitStatus(quint8 limitstatus);
    quint8 getLimitStatus()const;
    //其他状态 8bit从高位到低位依次: 急停状态 轨距状态 锚定状态 门限位状态 柔腿夹轨器状态 刚腿夹轨器状态 右卷筒限位状态 左卷筒限位状态
    void setOtherStatus(quint8 othertatus);
    quint8 getOtherStatus()const;

    void setSteelLegDistance(double steeldistance);
    double getSteelLegDistance()const;
    void setMaxSteelLegDistance(double maxsteeldistance);
    double getMaxSteelLegDistance()const;
    void setnearMaxSteelLegDistance(double nearmaxsteeldistance);
    double getnearMaxSteelLegDistance()const;
    void setMinSteelLegDistance(double minsteeldistance);
    double getMinSteelLegDistance()const;
    void setnearMinSteelLegDistance(double nearminsteeldistance);
    double getnearMinSteelLegDistance()const;

    void setSoftLegDistance(double softdistance);
    double getSoftLegDistance()const;
    void setMaxSoftLegDistance(double maxsoftdistance);
    double getMaxSoftLegDistance()const;
    void setnearMaxSoftLegDistance(double nearmaxsoftdistance);
    double getnearMaxSoftLegDistance()const;
    void setMinSoftLegDistance(double minsoftdistance);
    double getMinSoftLegDistance()const;
    void setnearMinSoftLegDistance(double nearminsoftdistance);
    double getnearMinSoftLegDistance()const;

    void setDistance(double distance);
    double getDistance()const;
    void setMaxDistance(double maxdistance);
    double getMaxDistance()const;
    void setnearMaxDistance(double nearmaxdistance);
    double getnearMaxDistance()const;
    void setMinDistance(double mindistance);
    double getMinDistance()const;
    void setnearMinDistance(double nearmindistance);
    double getnearMinDistance()const;

    void setSideswayDistance(double sideswaydistance);
    double getSideswayDistance()const;
    void setMaxSideswayDistance(double maxsideswaydistance);
    double getMaxSideswayDistance()const;
    void setnearMaxSideswayDistance(double nearmaxsideswaydistance);
    double getnearMaxSideswayDistance()const;
    void setMinSideswayDistance(double minsideswaydistance);
    double getMinSideswayDistance()const;
    void setnearMinSideswayDistance(double nearminsideswaydistance);
    double getnearMinSideswayDistance()const;

    void setSpeed(double speed);
    double getSpeed()const;
    void setMaxSpeed(double maxspeed);
    double getMaxSpeed()const;
    void setnearMaxSpeed(double nearmaxspeed);
    double getnearMaxSpeed()const;

    void setWindSpeed(double windSpeed);
    double getWindSpeed()const;
    void setMaxWindSpeed(double maxwindspeed);
    double getMaxWindSpeed()const;
    void setnearMaxWindSpeed(double nearmaxwindspeed);
    double getnearMaxWindSpeed()const;

    void setMaxWindSpeedJIBIE(double maxwindspeedjibie);
    double getMaxWindSpeedJIBIE()const;
    void setnearMaxWindSpeedJIBIE(double nearmaxwindspeedjibie);
    double getnearMaxWindSpeedJIBIE()const;

    double getWindspeedJIBIE()const;

    void setDeflection(double deflection);
    double getDeflection()const;
    void setMaxDeflection(double maxdeflection);
    double getMaxDeflection()const;
    void setnearMaxDeflection(double nearmaxdeflection);
    double getnearMaxDeflection()const;

signals:
    
private slots:

private:

    //开关量
    bool          m_Left;//也称后行  海侧
    bool          m_Right;//也称前行 陆侧
    bool          m_Braking;//制动
    bool          m_changeBraking;//制动change后状态
    quint64       m_BrakingNumber;//制动次数

    bool          m_RailDistance;//轨道距离状态:正常 异常
    bool          m_DoorLimit;//起重机门限位:正常 异常
    bool          m_LeftRollerStatus;//电缆卷筒状态:左
    bool          m_RightRollerStatus;//电缆卷筒状态:右
    bool          m_RailClamp_SteelLeg;//钢腿夹轨器
    bool          m_RailClamp_SoftLeg;//柔腿夹轨器

    int           m_Gear;//档位
    quint8        m_LimitStatus;//限位状态
    quint8        m_OtherStatus;//其他状态

    //状态量
    double           m_SteelLegDistance;//钢腿行程
    double           m_SoftLegDistance;//柔腿行程
    double           m_Distance;//整车纵移
    double           m_SideswayDistance;//整车横移
    double           m_Speed;//速度
    double           m_WindSpeed;//风速
    double           m_Deflection;//偏斜值

    //设置最值
    double           m_MaxSteelLegDistance;//最大钢腿行程
    double           m_NearMaxSteelLegDistance;//near最大钢腿行程
    double           m_MinSteelLegDistance;//最小钢腿行程
    double           m_NearMinSteelLegDistance;//near最小钢腿行程 大小依次: 最小钢腿行程 < near最小钢腿行程 < near最大钢腿行程 < 最大钢腿行程

    double           m_MaxSoftLegDistance;//最大柔腿行程
    double           m_NearMaxSoftLegDistance;//near最大柔腿行程
    double           m_MinSoftLegDistance;//最小柔腿行程
    double           m_NearMinSoftLegDistance;//near最小柔腿行程 大小依次: 最小柔腿行程 < near最小柔腿行程 < near最大柔腿行程 < 最大柔腿行程

    double           m_MaxDistance;//最大整车纵移
    double           m_NearMaxDistance;//near最大整车纵移
    double           m_MinDistance;//最小整车纵移
    double           m_NearMinDistance;//near最小整车纵移 大小依次: 最小整车纵移 < near最小整车纵移 < near最大整车纵移 < 最大整车纵移

    double           m_MaxSideswayDistance;//最大整车横移
    double           m_NearMaxSideswayDistance;//near最大整车横移
    double           m_MinSideswayDistance;//最小整车横移
    double           m_NearMinSideswayDistance;//near最小整车横移 大小依次: 最小整车横移 < near最小整车横移 < near最大整车横移 < 最大整车横移

    double           m_MaxSpeed;//最大速度
    double           m_NearMaxSpeed;//near最大速度 大小依次:near最大速度 < 最大速度

    double           m_MaxWindSpeed;//最大风速
    double           m_NearMaxWindSpeed;//near最大风速 大小依次:near最大风速 < 最大风速
    double           m_MaxWindSpeedJIBIE;//最大风速级别
    double           m_NearMaxWindSpeedJIBIE;//near最大风速级别 大小依次:near最大风速级别 < 最大风速级别

    double           m_MaxDeflection;//最大偏斜值
    double           m_NearMaxDeflection;//near最大偏斜值 大小依次:near最大偏斜值 < 最大偏斜值
    
};

#endif // BIGVEHICLE_H
