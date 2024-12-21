#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include<string>
#include<vector>
#include<iostream>
#include"TaskManager.h"
class Task;

class UserInterface {
    vector<Task>* showList;
    string input1;
    string input2;
    int inputNum;
    Tag inputTag;
    Priority inputPriority;
    DateTime cDate;
    DateTime dDate;
    Task* tempTask;
    void initialize();
    void userLogin();
    void mainFunctionInterface();
    void printTaskList();
    void addTaskInterface();
    void editTaskInterface();
    void printTask(Task* temptask);
    Task* deleteTaskInterface();
    void filterTagInterface();
    friend class Monitor;
};

void UserInterface::initialize() {
    cout << "*******************************" << endl << endl;
    cout << "   Welcome to TaskList App!!!" << endl << endl;
    cout << "*******************************" << endl << endl;
    system("pause");
}

void UserInterface::userLogin() {
    system("cls");
    cout << "*******************************" << endl;
    cout << "User Login" << endl << endl;
    cout << "*******************************" << endl;
    cout << "Username: ";
    cin >> input1;
    cout << "Password: ";
    cin >> input2;
}

void UserInterface::mainFunctionInterface() {
    system("cls");
    cout << "*******************************" << endl;
    cout << "Task List APP"<< endl << endl;
    cout << "*******************************" << endl;
    printTaskList();
    cout << "*******************************" << endl;
    cout << "Operation: " << endl;
    cout << "1. Add Task  2. Edit Task  " \
        << "3. Delete Task  4. Filter Tasks by Tag" << endl;
    cout << "5. Get Tasks By Priority   "\
        << "6. Get Tasks By CreateDate  7. Get Tasks By DueDate" << endl;
    cin >> inputNum;
}

void UserInterface::printTaskList() {
    if (showList== nullptr || showList->empty()) {
        cout << "No Task Yet" << endl;
        return;
    }
    int count = 1;
    for (vector<Task>::iterator iter = showList->begin(); \
        iter != showList->end(); iter++) {
            cout << count << ": "<< iter->name << endl;
            cout << "\t" << iter->description << endl<< endl;
            count++;
        }
}

void UserInterface::addTaskInterface() {
    system("cls");
    cout << "*******************************" << endl;
    cout << "Add Task"<< endl << endl;
    cout << "*******************************" << endl;
    cout << "Taskname: ";  // NOTE: 注意有的task name或description会携带空格
    char tempChar;
    input1 = "";
    cin >> tempChar;
    while (tempChar != '\n') {
        input1 += tempChar;
        tempChar = getchar();
    }
    cout << "Description: ";
    input2 = "";
    cin >> tempChar;
    while (tempChar != '\n') {
        input2 += tempChar;
        tempChar = getchar();
    }
    INPUT_TAG: cout << "Tag: 1.STUDY  2.LIFE  3.WORK  4.OTHER_TAG" << endl;
    cin >> inputNum;
    switch (inputNum) {
        case 1:
            inputTag = STUDY; break;
        case 2:
            inputTag = LIFE; break;
        case 3:
            inputTag = WORK; break;
        case 4:
            inputTag = OTHER_TAG; break;
        default:
            cout << "Wrong choice number!";
            goto INPUT_TAG;
    }
    INPUT_PRIORITY: cout << "Priority: 1.URGENT  " << \
        "2.IMPORTANT  3.OTHER_PRIORITY" << endl;
    cin >> inputNum;
    switch (inputNum) {
        case 1:
            inputPriority = URGENT; break;
        case 2:
            inputPriority = IMPORTANT; break;
        case 3:
            inputPriority = OTHER_PRIORITY; break;
        default:
            cout << "Wrong choice number!!!" << endl;
            goto INPUT_PRIORITY;
    }
    int year, month, day;
    cout << "Create date(please input 3 integer: year month day)" << endl;
    cin >> year >> month >> day;
    cDate = DateTime(year, month, day);
    cout << "Due date(please input 3 integer: year month day)" << endl;
    cin >> year >> month >> day;
    dDate = DateTime(year, month, day);
}

void UserInterface::editTaskInterface() {
    system("cls");
    cout << "*******************************" << endl;
    cout << "Edit Task"<< endl << endl;
    cout << "*******************************" << endl;
    cout << "Temp Task:" << endl;
    printTaskList();
    cout << "*******************************" << endl;
    EditNum: cout << "Choose your task number:";
    cin >> inputNum;
    if (inputNum > showList->size()) {
        cout << "Wrong number !" <<endl;
        goto EditNum;
    }
    vector<Task>::iterator iter = showList->begin();
    while (inputNum != 1) {
        inputNum--;
        iter++;
    }
    tempTask = &(*iter);
    printTask(tempTask);
    cout << "Please rewrite the task's information." << endl;
    cout << "Taskname: ";
    cin >> input1;
    cout << "Description: ";
    cin >> input2;
    INPUT_TAG: cout << "Tag: 1.STUDY  2.LIFE  3.WORK  4.OTHER_TAG" <<endl;
    cin >> inputNum;
    switch (inputNum) {
        case 1:
            inputTag = STUDY; break;
        case 2:
            inputTag = LIFE; break;
        case 3:
            inputTag = WORK; break;
        case 4:
            inputTag = OTHER_TAG; break;
        default:
            cout << "Wrong choice number!";
            goto INPUT_TAG;
    }
    INPUT_PRIORITY: cout << "Priority: 1.URGENT  2.IMPORTANT  " << \
        "3.OTHER_PRIORITY" << endl;
    cin >> inputNum;
    switch (inputNum) {
        case 1:
            inputPriority = URGENT; break;
        case 2:
            inputPriority = IMPORTANT; break;
        case 3:
            inputPriority = OTHER_PRIORITY; break;
        default:
            cout << "Wrong choice number!!!" << endl;
            goto INPUT_PRIORITY;
    }
    int year, month, day;
    cout << "Create date(please input 3 integer: year month day)" << endl;
    cin >> year >> month >> day;
    cDate = DateTime(year, month, day);
    cout << "Due date(please input 3 integer: year month day)" << endl;
    cin >> year >> month >> day;
    dDate = DateTime(year, month, day);
}

void UserInterface::printTask(Task* temptask) {
    cout << "*******************************" << endl;
    cout << "Task Information" << endl;
    cout << "Task name:\t" << temptask->name << endl;
    cout << "Description:\t" << temptask->description << endl;
    cout << "Tag:\t" << temptask->getTag() << endl;
    cout << "Priority:\t" << temptask->getPriority() << endl;
    cout << "CreateDate:\t" << temptask->getCreateDate() << endl;
    cout << "DueDate:\t" << temptask->getDueDate() << endl;
    cout << "*******************************" << endl;
}

Task* UserInterface::deleteTaskInterface() {
    system("cls");
    cout << "*******************************" << endl;
    cout << "Delete Task"<< endl << endl;
    cout << "*******************************" << endl;
    cout << "Temp Task:" << endl;
    printTaskList();
    cout << "*******************************" << endl;
    EditNum: cout << "Choose your task number:";
    cin >> inputNum;
    if (inputNum > showList->size()) {
        cout << "Wrong number !" <<endl;
        goto EditNum;
    }
    vector<Task>::iterator iter = showList->begin();
    while (inputNum != 1) {
        inputNum--;
        iter++;
    }
    return &(*iter);
}

void UserInterface::filterTagInterface() {
    cout << "*******************************" << endl;
    ChooseTag: cout << "Choose one tag: "<< endl;
    cout << "1.STUDY  2.LIFE  3.WORK  4.OTHER_TAG" << endl;
    cin >> inputNum;
    switch (inputNum) {
        case 1:
            inputTag = STUDY;
            break;
        case 2:
            inputTag = LIFE;
            break;
        case 3:
            inputTag = WORK;
            break;
        case 4:
            inputTag = OTHER_TAG;
            break;
        default:
            cout << "Wrong number!";
            goto ChooseTag;
    }
}

#endif  // USERINTERFACE_H_