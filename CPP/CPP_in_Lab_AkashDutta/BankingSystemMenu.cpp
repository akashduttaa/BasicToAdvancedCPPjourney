#include <iostream>
using namespace std;

int main() {
    int choice;
    float balance = 1000.1000, amount;

    do {
        cout << "\n--- Banking Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                balance += amount;
                cout << "Updated Balance = " << balance;
                break;

            case 2:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if(amount <= balance) {
                    balance -= amount;
                    cout << "Updated Balance = " << balance;
                } else {
                    cout << "Insufficient balance!";
                }
                break;

            case 3:
                cout << "Current Balance = " << balance;
                break;

            case 4:
                cout << "Exiting...";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while(choice != 4);

    return 0;
}



