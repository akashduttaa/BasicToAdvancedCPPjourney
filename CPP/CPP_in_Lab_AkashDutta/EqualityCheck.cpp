#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;

    if (a == b)
        cout << "Numbers are equal";
    else
        cout << "Numbers are not equal";

    return 0;
}