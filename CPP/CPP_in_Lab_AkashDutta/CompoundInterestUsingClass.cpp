#include <iostream>
#include <cmath>
using namespace std;

class CompoundInterest {
    float principal, rate, time, amount, ci;

public:
    void input() {
        cout << "Enter Principal Amount: ";
        cin >> principal;

        cout << "Enter Rate of Interest: ";
        cin >> rate;

        cout << "Enter Time (years): ";
        cin >> time;
    }

    void calculate() {
        amount = principal * pow((1 + rate / 100), time);
        ci = amount - principal;
    }

    void display() {
        cout << "Compound Interest = " << ci << endl;
        cout << "Total Amount = " << amount << endl;
    }
};

int main() {
    CompoundInterest c;

    c.input();
    c.calculate();
    c.display();

    return 0;
}