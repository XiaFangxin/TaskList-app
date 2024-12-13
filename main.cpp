#include<iostream>
using namespace std;

#include "Monitor.h"
#include "Database.h"
#include "TaskManager.h"

Monitor monitor;
Database database;
// DateTime defaultCreateTime = DateTime(2024,1,1);
// DateTime defaultDueTime = DateTime(2025, 1, 1);

int main(){
    //打开App
    monitor.initialize();
    database.initialize();

    //用户登录
    monitor.userLogin(&database);

    //任务管理主界面
    monitor.mainFunction();

	system("pause");
    return 0;
}