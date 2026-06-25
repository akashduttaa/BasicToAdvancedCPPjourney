#include <iostream>
using namespace std ;

int main(){

    int i , n ;
    bool isPrime =true ;

    cout << "Enter a number ";
    cin >> n ;

        if(n<= 1){
            isPrime = false ;
        }else{
            for (i =2 ; i <= n/2 ; i++){
                if (n%i == 0){
                    isPrime =false ; break;
                }
            }
        }

    if(isPrime)
     cout << "Prime Number" ;

        else 
        cout <<"Not Prime" ;


    return 0 ;
}