
#include <iostream>
using namespace std;

int main() {
    int marks;
    char grade;

    cout << "Enter marks: ";
    cin >> marks;

    if(marks >= 90) grade = 'A';
    else if(marks >= 75) grade = 'B';
    else if(marks >= 50) grade = 'C';
    else if(marks >= 40) grade = 'D';
    else grade = 'F';

    switch(grade) {
        case 'A': cout << "Grade A" << "\n"; break;
        case 'B': cout << "Grade B"<<  "\n"; break;
        case 'C': cout << "Grade C" << "\n"; break;
        case 'D': cout << "Grade D" << "\n"; break;
        case 'F': cout << "Fail" << "\n"; break;
    }

    return 0;
}

