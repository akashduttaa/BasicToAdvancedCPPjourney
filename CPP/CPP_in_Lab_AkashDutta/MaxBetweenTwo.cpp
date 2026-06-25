#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;

    if (a > b)
        cout << "Maximum is: " << a;
    else
        cout << "Maximum is: " << b;

    return 0;
}