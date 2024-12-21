#ifndef MONITOR_H_
#define MONITOR_H_
// 后端控制台，加载用户信息，加载用户界面
// 连接前端UserInterface和后端Database

#include"User.h"
#include"UserInterface.h"
#include"Database.h"
#include<vector>
#include<iostream>
class User;
class UserInterface;
class Database;

class Monitor {
    User* user;
    UserInterface userInterface;
    friend class Database;
 public:
    void initialize();  // 初始化控制台，加载用户界面
    void userLogin(Database* database);  // 用户登录（或注册）
    void mainFunction();
};

void Monitor::initialize() {
    user = nullptr;
    userInterface.initialize();
}

void Monitor::userLogin(Database* database) {
    L1: userInterface.userLogin();
    bool find = false;
    for (vector<User>::iterator iter = database->userList.begin();
        iter != database->userList.end(); iter++) {
            if (iter->username == userInterface.input1) {
                find = true;
                if (iter->password == userInterface.input2) {
                    user = &(*iter);
                    cout << "Successfully login!" << endl;
                } else {
                    cout << \
                        "Error password! Press ENTER to restart your login." \
                        << endl;
                    system("pause");
                    goto L1;
                }
                break;
            }
        }
    if (find == false) {
        cout << "Your account does not exit.Do you want to create it?" << endl;
        cout << "YES: 1, NO: 0"<< endl;
        int choice;
        cin >> choice;
        if (choice) {
            User* newUser = new User(userInterface.input1, \
                userInterface.input2);
            database->addUser(newUser);
            user = newUser;
            cout << \
                "Your account has been created. Press ENTER to user login" \
                << endl;
            system("pause");
        }
        goto L1;
    }

    userInterface.showList = &user->taskmanager.taskList;
}

void Monitor::mainFunction() {
    userInterface.mainFunctionInterface();  // 打印出主用户界面（标题、任务表）
/*
    1. Add Task  2. Edit Task  3. Delete Task  4. Filter Tasks by Tag
    5. Get Tasks By Priority   6. Get Tasks By CreateDate  7. Get Tasks By DueDate
*/
    switch (userInterface.inputNum) {
        case 1:
            {
                userInterface.addTaskInterface();
                user->taskmanager.createTask(userInterface.input1, \
                    userInterface.input2, \
                    userInterface.inputTag, userInterface.inputPriority, \
                    userInterface.cDate, userInterface.dDate);
            }
            break;
        case 2:
            {
                userInterface.editTaskInterface();  // get task num of showlist
                user->taskmanager.createTask(userInterface.input1, \
                    userInterface.input2, \
                    userInterface.inputTag, userInterface.inputPriority, \
                    userInterface.cDate, userInterface.dDate);
                user->taskmanager.deleteTask(userInterface.tempTask);
                cout << \
                    "You have successfully edited the task! " \
                    << "Press ENTER to go back to main interface." \
                    << endl;
                system("pause");
            }
            break;
        case 3:
            {
                Task* tempTask = userInterface.deleteTaskInterface();
                user->taskmanager.deleteTask(tempTask);
                cout << \
                "You have successfully deleted the task! " \
                << "Press ENTER to go back to main interface." << endl;
                system("pause");
            }
            cout << "Undone" << endl;
            break;
        case 4:
            {
                userInterface.filterTagInterface();
                userInterface.showList = \
                    user->taskmanager.filterTasks(userInterface.inputTag);
                cout << "*******************************" << endl;
                cout << "Tag: " << \
                    tag_to_string(userInterface.inputTag) << endl;
                userInterface.printTaskList();
                system("pause");
            }
            break;
        case 5:
            {
                cout << "*******************************" << endl;
                userInterface.showList = \
                    user->taskmanager.filterPriority(URGENT);
                cout <<endl<< "Priority: " << \
                    priority_to_string(URGENT) << endl;
                userInterface.printTaskList();
                userInterface.showList = \
                    user->taskmanager.filterPriority(IMPORTANT);
                cout << endl << "Priority: " << \
                    priority_to_string(IMPORTANT) << endl;
                userInterface.printTaskList();
                userInterface.showList = \
                    user->taskmanager.filterPriority(OTHER_PRIORITY);
                cout <<endl<< "Priority: " << \
                    priority_to_string(OTHER_PRIORITY) << endl;
                userInterface.printTaskList();
                system("pause");
            }
            break;
        case 6:
            {
                cout << "*******************************" << endl;
                user->taskmanager.getTasksByCreateDate();
                userInterface.printTaskList();
                system("pause");
            }
            break;
        case 7:
            {
                cout << "*******************************" << endl;
                user->taskmanager.getTasksByDueDate();
                userInterface.printTaskList();
                system("pause");
            }
            break;
        default:
            break;
    }
    userInterface.showList = &user->taskmanager.taskList;
    mainFunction();
}

#endif  // MONITOR_H_"