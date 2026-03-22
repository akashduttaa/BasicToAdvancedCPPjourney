#include <iostream>
using namespace std;

int main() {
    float d1, d2, area;

    cout << "Enter diagonals of rhombus: ";
    cin >> d1 >> d2;

    area = (d1 * d2) / 2;

    cout << "Area = " << area;

    return 0;
}