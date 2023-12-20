#include "SQL/sqlite3.h"
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

void entry() {
    sqlite3* db;
    int id;
    string name;
    int age;
    int marks;
    int rc = sqlite3_open("students.db", &db);
    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    try
    {
        cout << "Enter ID: " << endl;
        cin >> id;
        cout << "Enter name: " << endl;
        cin >> name;
        cout << "Enter age: " << endl;
        cin >> age;
        cout << "Enter marks: " << endl;
        cin >> marks;
        string sql = "INSERT INTO STUDENTS (ID, NAME, AGE, MARKS) VALUES (" + to_string(id) + ", '" + name + "', " + to_string(age) + ", " + to_string(marks) + ");";
        sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

void del() {
    sqlite3* db;
    int id;
    int rc = sqlite3_open("students.db", &db);

    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    try
    {
        cout << "Enter ID: " << endl;
        cin >> id;
        string sql = "DELETE FROM STUDENTS WHERE ID = " + to_string(id) + ";";
        sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

void update() {
    sqlite3* db;
    int id;
    string name;
    int age;
    int marks;
    int rc = sqlite3_open("students.db", &db);

    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    try
    {
        cout << "Enter ID: " << endl;
        cin >> id;
        cout << "Enter name: " << endl;
        cin >> name;
        cout << "Enter age: " << endl;
        cin >> age;
        cout << "Enter marks: " << endl;
        cin >> marks;
        string sql = "UPDATE STUDENTS SET NAME = '" + name + "', AGE = " + to_string(age) + ", MARKS = " + to_string(marks) + " WHERE ID = " + to_string(id) + ";";
        sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void disp() {
    sqlite3* db;
    int rc = sqlite3_open("students.db", &db);

    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    try
    {
        string sql = "SELECT * FROM STUDENTS;";
        sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("students.db", &db);

    if (rc) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }
    cout << "Database opened successfully" << endl;
    try {
    string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='STUDENTS';";
    int count = 0;
    sqlite3_exec(db, sql.c_str(), NULL, &count, NULL);
    if (count > 0) {
        cout << "Table STUDENTS exists" << endl;
    } else {
        try
    {
        sqlite3_exec(db,"CREATE TABLE STUDENTS(" \
            "ID INT, " \
            "NAME TEXT, " \
            "AGE INT, " \
            "MARKS INT);", NULL, NULL, NULL);
    }
        catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    }
}
catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
}
    int choice;
    cout << "What operation you want to do?\n 1. Enter data\n 2. Delete data\n 3. Update data\n 4. Display data\n 5. Exit" << endl;
    cin >> choice;
    switch (choice)
    {

    case 1:
        entry();
        break;
    case 2:
        del();
        break;
    case 3:
        update();
        break;
    case 4:
        disp();
        break;
    case 5:
        sqlite3_close(db);
        std::cout << "Press any key to exit...";
        getch();
        return 0;
    default:
        std::cout << "Invalid choice" << endl;
        break;
    }
    sqlite3_close(db);
    main();
    return 0;
}
