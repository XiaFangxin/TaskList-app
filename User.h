#ifndef USER_H_
#define USER_H_

#include<iostream>
#include<string>

#include"TaskManager.h"
class TaskManager;

enum Role {
    STUDENT, WORKER
};

class User {
    string username;
    string password;
    Role role;
    TaskManager taskmanager;;

    friend class Database;
    friend class Monitor;
    User(string n = "", string p = "", Role r = STUDENT): \
        username(n), password(p), role(r){}
};

#endif  // USER_H_