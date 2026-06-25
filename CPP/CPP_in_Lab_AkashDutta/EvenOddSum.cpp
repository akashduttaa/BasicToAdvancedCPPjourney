#include <iostream>
using namespace std;

int main() {
    int N, even_sum = 0, odd_sum = 0;
    cout << "Enter a number: ";
    cin >> N;

    for (int i = 1; i <= N; i++) {
        if (i % 2 == 0) {
            even_sum += i;
        } else {
            odd_sum += i;
        }
    }

    cout << "Sum of Even Numbers: " << even_sum << endl;
    cout << "Sum of Odd Numbers: " << odd_sum << endl;
    return 0;
}