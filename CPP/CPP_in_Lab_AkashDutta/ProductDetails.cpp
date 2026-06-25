#include <iostream>
using namespace std;

class Product {
    int productId;
    float price, discount, finalPrice;

public:
    void input() {
        cout << "Enter Product ID: ";
        cin >> productId;

        cout << "Enter Product Price: ";
        cin >> price;

        cout << "Enter Discount (%): ";
        cin >> discount;
    }

    void calculate() {
        finalPrice = price - (price * discount / 100);
    }

    void display() {
        cout << "\nProduct ID: " << productId << endl;
        cout << "Original Price: " << price << endl;
        cout << "Discount: " << discount << "%" << endl;
        cout << "Final Price: " << finalPrice << endl;
    }
};

int main() {
    Product p;

    p.input();
    p.calculate();
    p.display();

    return 0;
}