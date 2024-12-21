#ifndef TASKMANAGER_H_
#define TASKMANAGER_H_

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#include"TaskManager.h"
#include"Monitor.h"
// #include"User.h"

class Monitor;
class User;

enum Tag {
    STUDY, LIFE, WORK, OTHER_TAG
};

enum Priority {
    URGENT, IMPORTANT, OTHER_PRIORITY
};

class DateTime {
    int year;
    int month;
    int day;
    friend class Task;
    friend class TaskManager;
 public:
    DateTime(int y = 0, int m = 0, int d = 0):
        year(y), month(m), day(d) {}
    friend bool operator < (const DateTime&d1, const DateTime& d2);
    friend bool operator > (const DateTime&d1, const DateTime& d2);
};

DateTime defaultCreateTime = DateTime(2024, 1, 1);
DateTime defaultDueTime = DateTime(2025, 1, 1);

class Task {
    string name;
    string description;
    DateTime createDate;
    DateTime dueDate;
    Tag tag;
    Priority priority;
    friend class TaskManager;
    friend class Monitor;
    friend class UserInterface;

    Task(string n = "", string d = "", \
        Tag t = OTHER_TAG, Priority p = OTHER_PRIORITY, \
        DateTime cDate = defaultCreateTime, DateTime dDate = defaultDueTime) {
            name = n; description = d;
            tag = t; priority = p;
            createDate = cDate;
            dueDate = dDate;
        }

    string getTag();
    string getPriority();
    string getCreateDate();
    string getDueDate();
};

class TaskManager {
    vector<Task> taskList;  // stored in database
    vector<Task> tempList;
    void createTask(string name, string descriptrion, \
        Tag tag, Priority Priority, DateTime createDate, DateTime dueDate);
    void editTask(Task* task);
    void deleteTask(Task* task);
    vector<Task>* searchTasks(string keyword);
    vector<Task>* filterTasks(Tag tag);
    vector<Task>* filterPriority(Priority priority);
    void getTasksByCreateDate();
    void getTasksByDueDate();
    friend class Monitor;
    friend class User;
    friend class Database;
};

/*---TaskManager---*/
void TaskManager::createTask(string name = "", string descriptrion = "", \
        Tag tag = OTHER_TAG, Priority Priority = OTHER_PRIORITY, \
        DateTime createDate = defaultCreateTime, \
        DateTime dueDate = defaultDueTime) {
    Task newTask = Task(name, descriptrion, tag, Priority, createDate, dueDate);
    taskList.insert(taskList.end(), newTask);
}

void TaskManager::deleteTask(Task* task) {
    vector<Task>::iterator iter = taskList.begin();
    while (iter != taskList.end()) {
        if (iter->name == task->name)
            break;
        iter++;
    }
    if (iter != taskList.end())  // error found by cppcheck
        taskList.erase(iter);
}

vector<Task>* TaskManager::filterTasks(Tag tag) {
    tempList.clear();
    for (vector<Task>::iterator iter = taskList.begin();
        iter != taskList.end(); iter++) {
            if (iter->tag == tag)
                tempList.insert(tempList.begin(), *iter);
        }
    return &tempList;
}

vector<Task>* TaskManager::filterPriority(Priority priority) {
    tempList.clear();
    for (vector<Task>::iterator iter = taskList.begin();
        iter != taskList.end(); iter++) {
            if (iter->priority == priority)
                tempList.insert(tempList.begin(), *iter);
        }
    return &tempList;
}

void TaskManager::getTasksByCreateDate() {
    sort(taskList.begin(), taskList.end(), \
        [&](const Task& a, const Task& b)->bool {
        return a.createDate < b.createDate;
    });
}

void TaskManager::getTasksByDueDate() {
    sort(taskList.begin(), taskList.end(), \
        [&](const Task& a, const Task& b)->bool {
        return a.dueDate < b.dueDate;
    });
}

/*---Task---*/
// STUDY, LIFE, WORK, OTHER_TAG
string Task::getTag() {
    switch (tag) {
        case STUDY:
            return "STUDY";
            break;
        case LIFE:
            return "LIFE";
            break;
        case WORK:
            return "WORK";
            break;
        case OTHER_TAG:
            return "OTHER_TAG";
            break;
    }
    return "";
}

// URGENT, IMPORTANT, OTHER_PRIORITY
string Task::getPriority() {
    switch (priority) {
        case URGENT:
            return "URGENT";
            break;
        case IMPORTANT:
            return "IMPORTANT";
            break;
        case OTHER_PRIORITY:
            return "OTHER_PRIORITY";
            break;
    }
    return "";
}

string Task::getCreateDate() {
    return to_string(createDate.year) + "/" \
        +  to_string(createDate.month) + "/" \
        +  to_string(createDate.day);
}

string Task::getDueDate() {
    return to_string(dueDate.year) + "/" \
        +  to_string(dueDate.month) + "/" \
        +  to_string(dueDate.day);
}

string tag_to_string(Tag tag) {
    switch (tag) {
        case STUDY:
            return "STUDY";
            break;
        case LIFE:
            return "LIFE";
            break;
        case WORK:
            return "WORK";
            break;
        case OTHER_TAG:
            return "OTHER_TAG";
            break;
    }
    return "";
}

string priority_to_string(Priority priority) {
    switch (priority) {
        case URGENT:
            return "URGENT";
            break;
        case IMPORTANT:
            return "IMPORTANT";
            break;
        case OTHER_PRIORITY:
            return "OTHER_PRIORITY";
            break;
    }
    return "";
}

bool operator < (const DateTime&d1, const DateTime& d2) {
    if (d1.year < d2.year) return true;
    if (d1.year > d2.year) return false;
    if (d1.month < d2.month) return true;
    if (d1.month > d2.month) return false;
    if (d1.day < d2.day) return true;
    return false;
}

bool operator > (const DateTime&d1, const DateTime& d2) {
    return !(d1 < d2);
}

#endif  // TASKMANAGER_H_