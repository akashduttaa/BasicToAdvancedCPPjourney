#include <iostream>
using namespace std;

class Largest {
    int arr[100], n, largest;

public:
    void input() {
        cout << "Enter number of elements: ";
        cin >> n;

        cout << "Enter array elements:\n";
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }

    void findLargest() {
        largest = arr[0];

        for(int i = 1; i < n; i++) {
            if(arr[i] > largest) {
                largest = arr[i];
            }
        }
    }

    void display() {
        cout << "Largest Element = " << largest << endl;
    }
};

int main() {
    Largest obj;

    obj.input();
    obj.findLargest();
    obj.display();

    return 0;
}