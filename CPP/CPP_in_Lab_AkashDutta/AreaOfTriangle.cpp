#include <iostream>
using namespace std;

int main() {
    double base, height, area;

    cout << "Enter base: ";
    cin >> base;

    cout << "Enter height: ";
    cin >> height;

    area = 0.5 * base * height;

    cout << "Area of triangle = " << area << endl;

    return 0;
}
