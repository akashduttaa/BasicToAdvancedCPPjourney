#include <iostream>
using namespace std;

class Temperature {
    float celsius, fahrenheit;

public:
    void input() {
        cout << "Enter temperature in Celsius: ";
        cin >> celsius;
    }

    void convert() {
        fahrenheit = (celsius * 9 / 5) + 32;
    }

    void display() {
        cout << "Temperature in Fahrenheit = " << fahrenheit << endl;
    }
};

int main() {
    Temperature t;

    t.input();
    t.convert();
    t.display();

    return 0;
}      







