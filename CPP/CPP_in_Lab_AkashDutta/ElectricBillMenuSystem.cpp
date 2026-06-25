#include <iostream>
using namespace std;

int main() {
    int type, units;
    float bill;

    cout << "Customer Type:\n";
    cout << "1. Domestic\n2. Commercial\n3. Industrial\n";
    cout << "Enter your choice: ";
    cin >> type;

    cout << "Enter units consumed: ";
    cin >> units;

    switch(type) {
        case 1: 
            bill = units * 5;
            break;

        case 2: 
            bill = units * 8;
            break;

        case 3: 
            bill = units * 10;
            break;

        default:
            cout << "Invalid customer type!";
            return 0;
    }

    cout << "Total Bill = Rs. " << bill;
    return 0;
}
