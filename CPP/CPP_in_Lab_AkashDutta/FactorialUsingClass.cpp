#include <iostream>
using namespace std;

class Factorial {
    int n;
    long fact;

public:
    void input() {
        cout << "Enter a number: ";
        cin >> n;
    }

    void calculate() {
        fact = 1;
        for(int i = 1; i <= n; i++) {
            fact *= i;
        }
    }

    void display() {
        cout << "Factorial = " << fact << endl;
    }
};

int main() {
    Factorial f;

    f.input();
    f.calculate();
    f.display();

    return 0;
}