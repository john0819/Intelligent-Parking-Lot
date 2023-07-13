#pragma once
#include"sqlite3.h"
#include<iostream>
using namespace std;
//单例模式：懒汉模式：只有在用到的时候才会选择去做这个事，可以合理的分配资源
//        饿汉模式：一开始就准备好了，有可能会造成资源的浪费

//这个类的目的就是用来操作我们数据库的--数据库只能被打开一次
/*单例：只能创建一个对象，这个对象由谁去创建   由他自己去创建，创建对象就会去执行构造
    创建好了对象，要提供给其他对象去使用
提供一个静态的方法可以让别人获取到你的这个唯一的对象，因为别人没有创建这个类对象的资格



  */
class Cdatasqlite
{
public:
    //2.提供一个静态的成员函数，可以获取到唯一的对象
    static Cdatasqlite* getIntence();//静态成员函数只能访问静态的

    //不需要返回结果的:删除、修改、插入操作
    int noResSql(const char* sql);
    //需要返回结果的--查询  :可变使用引用传参
    int getDataSql(const char* sql, char**& qres, int& row, int& col);

private://单例：1.构造函数私有化
    Cdatasqlite();
    //3.需要一个静态的变量来存储这个唯一的对象
    static Cdatasqlite* pTntence;
    sqlite3* mysql;
};

