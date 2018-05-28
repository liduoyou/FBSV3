#include "CDateBase.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
//1.加载驱动sqllite（addDatebase）
//2.open
//3.建表
//4. sql操作
CDateBase::CDateBase()
{
}
void CDateBase::db_Connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");//
}
bool CDateBase::db_Open(QString name)
{
    db.setDatabaseName(name);
    if(!db.open())
    {
//        CommonNotify::instance()->messageBox("cannot open database","Unabel to connect");
        return false;
    }
    return true;
}
bool CDateBase::db_Createtable(QString tablename)
{
    QSqlQuery query;
    QString sql = "create table WorkTime(Date datetime primary key,Accumulativetime text, totalWorkNumber text)";
    query.exec(sql);
    if(!db_Exist(tablename)){
        QString sqlstr = "create table %1(\
                Date datetime primary key,\
                EquiNumber text,\
                BigVehicleForward text,\
                BigVehicleBackward text,\
                BigVehicleBraking text,\
                BigVehicleRailDistanceStatus text,\
                BigVehicleDoorLimit text,\
                BigVehicleLeftRollerStatus text,\
                BigVehicleRightRollerStatus text,\
                BigVehicleRailClampSteelleg text,\
                BigVehicleRailClampSoftleg text,\
                BigVehicleGear text,\
                BigVehicleSteelLegDistance text,\
                BigVehicleSoftLegDistance text,\
                BigVehicleWindSpeed text,\
                BigVehicleDeflection text,\
                UpLittleVehicleForward text,\
                UpLittleVehicleBackward text,\
                UpLittleVehicleBraking text,\
                UpLittleVehicleGear text,\
                UpLittleVehicleNo1HookUp text,\
                UpLittleVehicleNo1HookDown text,\
                UpLittleVehicleNo1HookBraking text,\
                UpLittleVehicleNo1HookGear text,\
                UpLittleVehicleNo1HookWieght text,\
                UpLittleVehicleNo1HookHeight text,\
                UpLittleVehicleNo1HookScope text,\
                UpLittleVehicleNo2HookUp text,\
                UpLittleVehicleNo2HookDown text,\
                UpLittleVehicleNo2HookBraking text,\
                UpLittleVehicleNo2HookGear text,\
                UpLittleVehicleNo2HookWieght text,\
                UpLittleVehicleNo2HookHeight text,\
                UpLittleVehicleNo2HookScope text,\
                DownLittleVehicleForward text,\
                DownLittleVehicleBackward text,\
                DownLittleVehicleBraking text,\
                DownLittleVehicleGear text,\
                DownLittleVehicleNo1HookUp text,\
                DownLittleVehicleNo1HookDown text,\
                DownLittleVehicleNo1HookBraking text,\
                DownLittleVehicleNo1HookGear text,\
                DownLittleVehicleNo1HookWieght text,\
                DownLittleVehicleNo1HookHeight text,\
                DownLittleVehicleNo1HookScope text,\
                DownLittleVehicleNo2HookUp text,\
                DownLittleVehicleNo2HookDown text,\
                DownLittleVehicleNo2HookBraking text,\
                DownLittleVehicleNo2HookGear text,\
                DownLittleVehicleNo2HookWieght text,\
                DownLittleVehicleNo2HookHeight text,\
                DownLittleVehicleNo2HookScope text,\
                WarningGrade text,\
                WarningType text)";
        query.exec(sqlstr.arg(tablename));
        db_isDropTable();
        return true;//新创建表
    }else{
        return false;//未创建新表
    }
    return true;
}

bool CDateBase::db_Exist(QString tablename)
{
    QSqlQuery query;
    QString _existTable = "select count(*) from sqlite_master where type='table' and tbl_name = '%1'";
    query.exec(_existTable.arg(tablename));
    while(query.next()){
        int count;
        count = query.value(0).toInt();
        if(count>0){
            return true;
        }else{
            return false;
        }
        count++;
    }
    return true;
}

void CDateBase::db_isDropTable()
{
    QSqlQuery query;
    QString _willdroptablename;
    QString _tablecount = "select count(*) from sqlite_master where type='table'";
    query.exec(_tablecount);
    while(query.next()){
        int count;
        count = query.value(0).toInt();
        if(count > 47){
            qDebug()<<count<<"> 47";
            QString _tablename= "select name from sqlite_master where type='table' order by name";
            query.exec(_tablename);
            if(query.first()){
                _willdroptablename = query.value(0).toString();
                qDebug()<<"_willdroptablename"<<_willdroptablename;
            }
            QString _dropstr= "drop table '%1'";
            qDebug()<<"sql"<<_dropstr.arg(_willdroptablename);
            query.exec(_dropstr.arg(_willdroptablename));
        }else{
            qDebug()<<count<<"< 46";

        }
    }
}
void CDateBase::db_Close()
{
    qDebug()<<"CDateBase::db_Close()";
    db.close();
}
