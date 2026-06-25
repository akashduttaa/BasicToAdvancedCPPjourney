#include <iostream>
using namespace std;

int main() {
    int units;
    double bill;

    cout << "Enter electricity units consumed: ";
    cin >> units;

    if (units <= 100) {
        bill = units * 5;
    }
    else if (units <= 300) {
        bill = units * 7;
    }
    else {
        bill = units * 10;
    }

    cout << "Total Electricity Bill = Rs. " << bill;

    return 0;
}