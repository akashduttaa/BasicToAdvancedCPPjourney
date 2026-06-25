#include <iostream>
using namespace std;

class Number {
    int n, square, cube;

public:
    void input() {
        cout << "Enter a number: ";
        cin >> n;
    }

    void calculate() {
        square = n * n;
        cube = n * n * n;
    }

    void display() {
        cout << "Square = " << square << endl;
        cout << "Cube = " << cube << endl;
    }
};

int main() {
    Number obj;

    obj.input();
    obj.calculate();
    obj.display();

    return 0;
}