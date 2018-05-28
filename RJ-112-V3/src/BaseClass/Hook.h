#ifndef HOOK_H
#define HOOK_H

#include <QObject>

class Hook
{

public:
    enum HookType{
        Htype_NO1,   //上小车1号吊钩;
        Htype_NO2,   //上小车2号吊钩;
        Htype_NO3,   //下小车主钩;
        Htype_NO4,   //下小车副钩;

        Htype_NO5,   //前天车1号吊钩;
        Htype_NO6,   //前天车2号吊钩;
        Htype_NO7,   //后天车1号吊钩;
        Htype_NO8,   //后天车2号吊钩;

        Htype_NO9,    //1号小车1号吊钩;
        Htype_NO10,   //1号小车2号吊钩;
        Htype_NO11,   //2号小车1号吊钩;
        Htype_NO12    //2号小车2号吊钩;
    };

    Hook();
    ~Hook();

    void setUp(bool up);
    bool getUp()const;
    void setDown(bool down);
    bool getDown()const;
    void setBraking(bool braking);
    bool getBraking()const;
    void setBrakingNumber(quint64 brakeNumber);
    quint64 getBrakingNumber()const;

    void setGear(int gear);
    int getGear()const;
    void setLimitStatus(quint8 limitstatus);//限位状态 8bit从高位到低位依次: 0 0 下极限限位 上极限限位 下减速限位 上减速限位 下限位 上限位
    quint8 getLimitStatus()const;

    void setWeight(double weight);
    double getWeight()const;
    void setMaxWeight(double maxweight);
    double getMaxWeight()const;
    void setnearMaxWeight(double nearmaxweight);
    double getnearMaxWeight()const;

    void setHeight(double height);
    double getHeight()const;
    void setMaxHeight(double maxheight);
    double getMaxHeight()const;
    void setnearMaxHeight(double nearmaxheight);
    double getnearMaxHeight()const;
    void setMinHeight(double minheight);
    double getMinHeight()const;
    void setnearMinHeight(double nearminheight);
    double getnearMinHeight()const;

    void setSpeed(double speed);
    double getSpeed()const;
    void setMaxSpeed(double maxspeed);
    double getMaxSpeed()const;
    void setnearMaxSpeed(double nearmaxspeed);
    double getnearMaxSpeed()const;

    void setScope(double scope);
    double getScope()const;
    void setMaxScope(double maxscope);
    double getMaxScope()const;
    void setnearMaxScope(double nearmaxscope);
    double getnearMaxScope()const;
    void setMinScope(double minscope);
    double getMinScope()const;
    void setnearMinScope(double nearminscope);
    double getnearMinScope()const;

    void setMoment(double moment);
    double getMoment()const;
    void setMaxMoment(double maxmoment);
    double getMaxMoment()const;
    void setnearMaxMoment(double nearmaxmoment);
    double getnearMaxMoment()const;

signals:
    
private slots:

private:
    //开关量
    bool          m_Up;//上升
    bool          m_Down;//下降
    bool          m_Braking;//制动
    bool          m_changeBraking;//制动change后状态
    quint64       m_BrakingNumber;//制动次数

    int           m_Gear;//档位
    quint8        m_LimitStatus;//限位状态

    //状态量
    double           m_Weight;//吊重
    double           m_Height;//高度
    double           m_Speed;//速度
    double           m_Scope;//幅度
    double           m_Moment;//力矩

    //设置最值
    double           m_MaxWeight;//最大吊重
    double           m_NearMaxWeight;//near最大吊重 大小依次:最大吊重 < 最大吊重

    double           m_MaxHeight;//最大高度
    double           m_NearMaxHeight;//near最大高度
    double           m_MinHeight;//最小高度
    double           m_NearMinHeight;//near最小高度 大小依次: 最小高度 < near最小高度 < near最大高度 < 最大高度

    double           m_MaxSpeed;//最大速度
    double           m_NearMaxSpeed;//near最大速度 大小依次:最大速度 < 最大速度

    double           m_MaxScope;//最大幅度
    double           m_NearMaxScope;//near最大幅度
    double           m_MinScope;//最小幅度
    double           m_NearMinScope;//near最小幅度 大小依次: 最小幅度 < near最小幅度 < near最大幅度 < 最大幅度

    double           m_MaxMoment;//最大力矩
    double           m_NearMaxMoment;//near最大力矩 大小依次:最大力矩 < 最大力矩
};

#endif // HOOK_H
