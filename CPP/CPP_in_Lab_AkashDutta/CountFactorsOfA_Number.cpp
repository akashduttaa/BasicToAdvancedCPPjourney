#include <iostream>
using namespace std;

int main() {
    int num, count = 0;
    cout << "Enter a number: ";
    cin >> num;

    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            cout << i << " ";
            count++;
        }
    }

    cout << endl << "Total number of divisors: " << count << endl;
    return 0;
}