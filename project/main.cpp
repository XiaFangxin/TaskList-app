#include<iostream>
using namespace std;

#include "Monitor.h"
#include "Database.h"
#include "TaskManager.h"

Monitor monitor;
Database database;
// DateTime defaultCreateTime = DateTime(2024,1,1);
// DateTime defaultDueTime = DateTime(2025, 1, 1);

void memoryLeak();
void doubleFree();
void nullPointerDereference();

int main() {
    // 打开App
    monitor.initialize();
    database.initialize();

    // 用户登录
    monitor.userLogin(&database);

    // 测试内存泄漏
    memoryLeak();
    // 测试重复释放内存
    doubleFree();
    // 测试空指针解引用
    nullPointerDereference();

    // 任务管理主界面
    monitor.mainFunction();
    system("pause");
    return 0;
}


void memoryLeak() {
    int* ptr = new int[10];  // 分配内存
    // 忘记释放内存
    // delete[] ptr; // 应该释放内存
}

void doubleFree() {
    int* ptr = new int[10];
    delete[] ptr;  // 第一次释放
    delete[] ptr;  // 第二次释放（错误）
}

void nullPointerDereference() {
    int* ptr = nullptr;
    *ptr = 10;  // 解引用空指针（错误）
}