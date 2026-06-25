#include <iostream>
using namespace std;

int main() {
    int x, n, result = 1;
    cout << "Enter the base number: ";
    cin >> x;
    cout << "Enter the exponent: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        result *= x;
    }

    cout << x << " raised to the power " << n << " is " << result << endl;
    return 0;
}