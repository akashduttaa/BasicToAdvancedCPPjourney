
#include <iostream>
using namespace std;

int main() {
    int choice;

    cout << "Traffic Light Options:\n";
    cout << "1. Red\n2. Yellow\n3. Green\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "STOP!";
            break;
        case 2:
            cout << "GET READY!";
            break;
        case 3:
            cout << "GO!";
            break;
        default:
            cout << "Invalid choice!";
    }

    return 0;
}
