#ifndef LITTLEVEHICLE_H
#define LITTLEVEHICLE_H

#include <QObject>

class LittleVehicle
{

public:
    enum LittleVehicleType{
        LVtype_UpVehicle,   //上小车
        LVtype_DownVehicle, //下小车
        LVtype_FrontVehicle,//前天车
        LVtype_BackVehicle, //后天车
        LVtype_NO1Vehicle,  //1#小车
        LVtype_NO2Vehicle   //2#小车
    };

    LittleVehicle();
    ~LittleVehicle();

    void setForward(bool forward);
    bool getForward()const;
    void setBackward(bool backward);
    bool getBackward()const;
    void setBraking(bool braking);
    bool getBraking()const;
    void setBrakingNumber(quint64 brakeNumber);
    quint64 getBrakingNumber()const;

    void setGear(int gear);
    int getGear()const;
    void setLimitStatus(quint8 limitstatus);//限位状态 8bit从高位到低位依次: 0 0 后极限限位 前极限限位 后减速限位 前减速限位 后限位 前限位
    quint8 getLimitStatus()const;

    void setSpeed(double speed);
    double getSpeed()const;
    void setMaxSpeed(double maxspeed);
    double getMaxSpeed()const;
    void setnearMaxSpeed(double nearmaxspeed);
    double getnearMaxSpeed()const;

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
    
signals:
    
private slots:

private:

    //开关量
    bool          m_Forward;//前行
    bool          m_Backward;//后行
    bool          m_Braking;//制动
    bool          m_changeBraking;//制动change后状态
    quint64       m_BrakingNumber;//制动次数

    int           m_Gear;//档位
    quint8        m_LimitStatus;//限位状态

    double        m_speed;//速度
    double        m_distance;//行程

    //设置最值
    double           m_MaxDistance;//最大行程
    double           m_NearMaxDistance;//near最大行程
    double           m_MinDistance;//最小行程
    double           m_NearMinDistance;//near最小行程 大小依次: 最小行程 < near最小行程 < near最大行程 < 最大行程

    double           m_MaxSpeed;//最大速度
    double           m_NearMaxSpeed;//near最大速度 大小依次:最大速度 < 最大速度
    
};

#endif // LITTLEVEHICLE_H
