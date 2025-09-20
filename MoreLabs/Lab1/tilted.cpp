#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
    string x;
    
    cout << "Enter 10 digits (no whitespaces): ";
    cin >> x;
    if (x.size() > 10){
        cout << "too many digits";
    }
    for(int i = 0; i < 5; i++){
        cout << "   " << x;
        reverse(x.begin(), x.end());
        cout << "   " << x;
        cout << "/n";
        reverse(x.begin(), x.end());
        
    }
    
    
    

}