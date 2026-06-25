#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    if (num > 0)
        cout << "Positive number";
    else if (num < 0)
        cout << "Negative number";
    else
        cout << "Zero";

    return 0;
}