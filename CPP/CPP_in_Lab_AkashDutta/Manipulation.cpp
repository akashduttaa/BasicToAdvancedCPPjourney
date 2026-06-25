#include <iostream>
#include <iomanip>

using namespace std ;


int main(){

        int num ;
        float b = 3.142536;
        cout << "Enter a number :";
        cin>> num ;


        cout << "Value of num in OCTA format using Setbase :" << setbase(8) << num<< endl ;
        cout << "Value of num in HEXA format using Setbase:" << setbase(16) << num<< endl ;


        cout << "Value of num in OCTA format (setw & setfill()used ):" <<setw(20) <<setfill('*') << oct <<num<< endl ;


        cout << "Value of num in OCTA format :" << oct<< num<< endl ;
        cout << "Value of num in Hexa format :" << hex << num<<  endl ;

    return 0 ;
}