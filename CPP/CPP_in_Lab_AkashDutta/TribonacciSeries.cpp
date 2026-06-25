#include <iostream>
using namespace std;

int main() {
    int N;
    cout << "Enter the number of terms: ";
    cin >> N;

    int t1 = 0, t2 = 1, t3 = 2;
    cout << t1 << " " << t2 << " " << t3 << " ";

    for (int i = 3; i < N; i++) {
        int nextTerm = t1 + t2 + t3;
        cout << nextTerm << " ";
        t1 = t2;
        t2 = t3;
        t3 = nextTerm;
    }
    cout << endl;
    return 0;
}

