#include <iostream>
using namespace std;

class Complex {
    int real, imag;

public:
    void input() {
        cout << "Enter real part: ";
        cin >> real;

        cout << "Enter imaginary part: ";
        cin >> imag;
    }

    void add(Complex c1, Complex c2) {
        real = c1.real + c2.real;
        imag = c1.imag + c2.imag;
    }

    void display() {
        cout << "Sum = " << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1, c2, c3;

    cout << "Enter first complex number:\n";
    c1.input();

    cout << "Enter second complex number:\n";
    c2.input();

    c3.add(c1, c2);

    c3.display();

    return 0;
}