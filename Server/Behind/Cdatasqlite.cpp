#include "Cdatasqlite.h"
//静态数据成员的初始化
Cdatasqlite* Cdatasqlite::pTntence = nullptr;
Cdatasqlite* Cdatasqlite::getIntence()
{
    //先判断这个唯一的对象是否已经创建
    if (Cdatasqlite::pTntence == nullptr)//判断相等必须要==不能在这里出问题
    {
        //创建这个对象
        Cdatasqlite::pTntence = new Cdatasqlite();
    }
    //返回这个对象
    return Cdatasqlite::pTntence;
}

int Cdatasqlite::noResSql(const char* sql)
{
    char* errmsg;
    int res = sqlite3_exec(mysql, sql, nullptr, nullptr, &errmsg);
    if (res == 0)//打开成功
    {
        return 0;
    }
    else
    {
        return sqlite3_errcode(mysql);
    }
}

int Cdatasqlite::getDataSql(const char* sql, char**& qres, int& row, int& col)
{
    char* errmsg;
    int res = sqlite3_get_table(mysql, sql, &qres, &row, &col, &errmsg);
    if (res == 0)//打开成功
    {
        return 0;
    }
    else
    {
        return sqlite3_errcode(mysql);
    }
}



Cdatasqlite::Cdatasqlite()
{
    mysql = nullptr;
    int res = sqlite3_open("thirdstage.db", &mysql);
    if (res == 0)//打开成功
    {
       cout << "open dataBase success" << endl;

    }
    else
    {
        //错误信息输出
        cout << sqlite3_errcode(mysql) << endl;
        cout << sqlite3_errmsg(mysql) << endl;
    }

}