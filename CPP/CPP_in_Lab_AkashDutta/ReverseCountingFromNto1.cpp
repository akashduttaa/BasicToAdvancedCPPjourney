#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Enter a number: ";
    cin >> N;

    for (int i = N; i >= 1; i--) {
        cout << i << " ";
    }
    return 0;
}