#include <iostream>
using namespace std;

class Rectangle {
    float length, breadth, area;

public:
    void input() {
        cout << "Enter length: ";
        cin >> length;

        cout << "Enter breadth: ";
        cin >> breadth;
    }

    void calculate() {
        area = length * breadth;
    }

    void display() {
        cout << "Area of Rectangle = " << area << endl;
    }
};

int main() {
    Rectangle r;

    r.input();
    r.calculate();
    r.display();

    return 0;
}