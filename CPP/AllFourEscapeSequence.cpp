#include <iostream> 
using namespace std;

int main() {

// Using \n for new lines

cout << "Student Report\n";

// Using \r to overwrite part of the line 
cout << "XXXXXXXXXXXXXX" << "\r--------------------------\n";

// Using \t for indentation 
cout << "Name\t: Rajib\n";

// Using \n to split "C Programming" into two lines 
cout << "Subject\t: C Programming\n";

// Using \b to remove an extra space before 90 
cout << "Marks\t: 9\b90\n";

return 0;

}