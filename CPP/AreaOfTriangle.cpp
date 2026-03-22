#include <iostream>
using namespace std;

int main() {
    float base, height, area;

    cout << "Enter base and height of triangle: ";
    cin >> base >> height;

    area = 0.5 * base * height;

    cout << "Area = " << area;
    return 0;
}