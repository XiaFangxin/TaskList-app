#ifndef _DATABASE_H
#define _DATABASE_H
//模拟真实App中的数据库部分

#include<iostream>
#include<vector>
#include"User.h"
#include"TaskManager.h"

class User;

class Database{
    vector<User> userList;
    friend class Monitor;
public:   
    void initialize();  
    void addUser(User* user);
};

void Database::initialize(){
    //放入两个已有用户
    User user1;
    user1.username = "njucs";
    user1.password = "123";
    user1.taskmanager.createTask("A-task", "Description of A", STUDY, IMPORTANT, defaultCreateTime, defaultDueTime);
    user1.taskmanager.createTask("B-task", "Description of dear task B");
    User user2;
    user2.username = "user";
    user2.password = "8888";
    userList.insert(userList.begin(), user1);
    userList.insert(userList.begin(), user2);
}

void Database::addUser(User* user){
    userList.insert(userList.begin(), *user);
}

#endif