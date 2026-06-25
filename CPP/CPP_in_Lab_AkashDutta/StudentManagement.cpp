#include <iostream>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    int marks1, marks2, marks3;
    int total;
    float percentage;

public:
    void input()
    {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Marks of 3 Subjects: ";
        cin >> marks1 >> marks2 >> marks3;
    }

    void calculateMarks()
    {
        total = marks1 + marks2 + marks3;
        percentage = total / 3.0;
    }

    void display()
    {
        cout << "\n----- Student Details -----" << endl;
        cout << "Roll Number : " << rollNo << endl;
        cout << "Name        : " << name << endl;
        cout << "Marks 1     : " << marks1 << endl;
        cout << "Marks 2     : " << marks2 << endl;
        cout << "Marks 3     : " << marks3 << endl;
        cout << "Total Marks : " << total << endl;
        cout << "Percentage  : " << percentage << "%" << endl;
    }
};

int main()
{
    Student s;

    s.input();
    s.calculateMarks();
    s.display();

    return 0;
}