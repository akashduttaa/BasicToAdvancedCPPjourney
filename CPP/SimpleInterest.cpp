#include <iostream>
using namespace std;

int main() {
    float p, r, t, si;

    cout << "Enter principal, rate and time(in years): ";
    cin >> p >> r >> t;

    si = (p * r * t) / 100;

    cout << "Simple Interest = " << si;

    return 0;
}