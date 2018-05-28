#ifndef CDATEBASE_H
#define CDATEBASE_H
#include "QSqlDatabase"
class CDateBase
{
public:
    CDateBase();
    void db_Connect();
    bool db_Open(QString name);
    bool db_Createtable(QString tablename);

    void db_Close();
private:
    bool db_Exist(QString tablename);
    void db_isDropTable();
    QSqlDatabase db;

};

#endif // CDATEBASE_H
