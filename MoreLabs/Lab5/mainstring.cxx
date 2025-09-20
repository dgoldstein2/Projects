
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "mystring.h"
#include "mystring.cxx"
using namespace coen79_lab5;
using std::cin;
using std::cout;
using std::endl;

int main(){
    char a = 'a';
    string source("Hello World");
    cout<< "Check constructor for source: ";
    std::cout<< source <<std::endl;
    string s("yelp");
    string h(a);
    string f;
    string e;
    char add[] = {'y','e','a','h','\0'};
    string adding(add);
    cout<< "Check constructor for s: ";
    cout<< s << endl;//yelp
    cout<< "Check length of source: ";
    cout<< source.length() << endl;//11
    cout<< "Check constructor for adding: ";
    cout<<adding<<endl;
    source += s;
    cout<< "Check += operator source + s: ";
    cout<<source<<endl;
    
    s += add;
    cout<< "Check += operator s + add: ";
    cout<< s << endl; //yelpyeah
    s += 'c'; 
    cout<< "Check += operator s + 'c': ";
    cout<< s << endl; //yelpyeahc
    s.reserve(25);
    f = s;
    h = s;
    cout<< "Check = operator f = s and h = s : "<<endl;
    cout<< f << endl; //yelpyeahc
    cout<< h << endl; //yelpyeahc
    s.insert(source, 4); 
    cout<< "Check insert source into s @ 4: ";
    cout<< s << endl; //yelpHello Worldyelpyeahc
    
    s.dlt(4,4);
    cout<< "Check delete 4 characters from s starting at 4: ";
    cout<< s << endl; //yelpo Worldyelpc
    s.replace('e', 3);
    cout<< "Check replace 'e' into s @ 3: ";
    cout<< s << endl; //yeleo Worldyelpyeahc
    source.replace(f, 2);
    cout<< "Check replace f into source @ 2: ";
    cout<< source << endl;  
    int index = source.search('h'); //9
    int indexerr = source.search('x'); //should throw error/-1 will print character not found as well
    int indexsearch = source.search(h); //Should return 2
    cout<<"Check searches of 'h', 'x' and string h in source: "<< endl;;
    cout<< index << endl;
    cout<< indexerr << endl;
    cout<< indexsearch << endl;
    cout<< s<<endl; //yeleo Worldyelpyeahc
    cout<<f<<endl; //yelpyeahc
    cout<< h<<endl; //yelpyeahc
    cout<< e<<endl; //Empty
    bool x = f==e;
    bool x2 = f==h;
    bool y = f!=s;
    bool z = f > s;
    bool k = f < s;
    bool l = f >= s;
    bool g = f <= s;
    cout<< "checks booleans: "<<endl;;
    cout<< "f==e: "<<x <<endl; //expect false
    cout<<"f==h: "<<x2<<endl; //True
    cout << "f!=s: "<<y << endl; //expect true
    cout << "f>s: "<<z << endl; //true
    cout << "f<s: "<<k << endl; //false
    cout << "f>=s: "<<l << endl; //true
    cout << "f<=s: "<<g << endl; //false

    return EXIT_SUCCESS;

}