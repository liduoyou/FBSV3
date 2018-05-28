#ifndef CPUMEMTHREAD_H
#define CPUMEMTHREAD_H

#include <QThread>
#include <QTimer>
#include <unistd.h>   //头文件

#define VMRSS_LINE 15//VMRSS所在行
#define PROCESS_ITEM 14//进程CPU时间开始的项数

typedef struct        //声明一个occupy的结构体
{
    unsigned int user;  //从系统启动开始累计到当前时刻，处于用户态的运行时间，不包含 nice值为负进程。
    unsigned int nice;  //从系统启动开始累计到当前时刻，nice值为负的进程所占用的CPU时间
    unsigned int system;//从系统启动开始累计到当前时刻，处于核心态的运行时间
    unsigned int idle;  //从系统启动开始累计到当前时刻，除IO等待时间以外的其它等待时间iowait (12256) 从系统启动开始累计到当前时刻，IO等待时间(since 2.5.41)
}total_cpu_occupy_t;

typedef struct
{
    pid_t pid;//pid号
    unsigned int utime;  //该任务在用户态运行的时间，单位为jiffies
    unsigned int stime;  //该任务在核心态运行的时间，单位为jiffies
    unsigned int cutime;//所有已死线程在用户态运行的时间，单位为jiffies
    unsigned int cstime;  //所有已死在核心态运行的时间，单位为jiffies
}process_cpu_occupy_t;

class CpuMemThread : public QThread
{
    Q_OBJECT
public:
    explicit CpuMemThread(QObject *parent = 0);
    ~CpuMemThread();

    virtual void run();
signals:
    void sendCpuMemData(double,double);
private slots:

private:
    float getPcpu(__pid_t p);//获取进程CPU占用
    float getPmem(__pid_t p);//获取进程内存占用
    int getRmem(__pid_t p);//获取真实物理内存
    char *getItems(char *buffer, int ie);//取得缓冲区指定项的起始地址

    unsigned int getCpuProcessOccupy(__pid_t p);//获取进程的CPU时间
    unsigned int getCpuTotalOccupy();//获取总的CPU时间

    int getPhyMem(__pid_t p);//获取占用物理内存
    int getTotalMem();//获取系统总内存
};

#endif // CPUMEMTHREAD_H
