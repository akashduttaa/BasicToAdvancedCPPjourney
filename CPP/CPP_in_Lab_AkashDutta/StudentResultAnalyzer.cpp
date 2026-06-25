
#include <iostream>
using namespace std;

int main() {
    int choice;
    int N;
    cout << "Enter number of students: ";
    cin >> N;
int marks[N], total = 0, highest = 0, lowest = 100, passed = 0;
  for (int i = 0; i < N; i++) {
        cout << "Enter marks for student " << i + 1 << ": ";
        cin >> marks[i];
        total += marks[i];       
        if (marks[i] > highest)
            highest = marks[i];
        if (marks[i] < lowest)
            lowest = marks[i];
        if (marks[i] >= 40)
            passed++;
    }
 float average = total / N;
  do {
      cout << "\nMenu:\n";
      cout << "1. Display Total and Average Marks\n";
      cout << "2. Find Highest and Lowest Marks\n";
      cout << "3. Count Students Who Passed\n";
      cout << "4. Exit\n";
      cout << "Enter your choice: ";
      cin >> choice;
        switch (choice) {
          case 1:
              cout << "Total Marks: " << total << "\n";
              cout << "Average Marks: " << average << "\n";
              break;
          case 2:
             cout << "Highest Marks: " << highest << "\n";
          cout << "Lowest Marks: " << lowest << "\n";
      break;
           case 3:
              cout << "Number of Students who Passed: " << passed << "\n";
             break;
         case 4:
             cout << "Exiting program.\n";
              break;
          default:
              cout << "Invalid choice.\n";
       }
  } while (choice != 4);
   return 0;

       }
   
   }

  cout << endl << "Total number of divisors: " << count << endl;
return 0; }
}