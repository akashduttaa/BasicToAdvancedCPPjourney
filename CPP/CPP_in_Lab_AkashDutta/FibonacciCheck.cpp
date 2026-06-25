#include <iostream>
using namespace std ;

int main(){

    int n , a = 0 , b = 1 , c ;

    cout<<"Enter val of n :";
    cin >> n ;

    if (n==0)
        cout <<"Fibonacci number = 0";

    else if (n==0)
        cout <<"Fibonacci number = 1";
     else {
         for(int i = 2 ; i <= n ; i++)
            c = a + b ;
            a = b ;
            b = c ;     }

    if (b  == n){ cout <<"Fibonacci ";}
        else {cout << "Not Fibonacci " ;}
         


    return 0 ;
}