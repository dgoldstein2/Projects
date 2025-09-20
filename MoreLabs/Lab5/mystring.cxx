/* 
 * Dakota Goldstein
 * Lab 5 
 * dagoldstein@scu.edu
 * File: mystring.cxx
 * Description: Builds all the functions that are named in mystring.h
 * to make a working string class to make strings add to them and delete from them.
 * Value Sematics:
 * Copy constructor can take in a string or an array of characters and build a string.
 * Assignment operator assigns a string to be the same as what it is being assigned to.
 * Need to overload this operator
 */

#include <cstring>
#include <cstdlib> 
#include <iostream>
#include "mystring.h"
#include <cassert>


using namespace coen79_lab5;
using std::cin;
using std::cout;
using std::endl;
//Pre: str length must not be 0
//Post: Constructs a string of elements from str[] and allocates memory to it
string::string(const char str[]){
    char* character = new char[strlen(str)+1];
    size_t len = strlen(str) +1;
    for(size_t i = 0; i < len-1; i++){
        character[i] = str[i];
    }
    character[len] = '\0';
    characters = character;
    allocated = len;
    current_length = len-1;

}
//Pre: c must exist
//Post: makes a string of length 2 and assigns the first value to c and the second to the null character
string::string(char c){
    current_length = 2;
    allocated = 2;
    char* character = new char[allocated];
    character[0] = c;
    character[1] = '\0';
    characters = character;
    
}

//Pre: Source cannot be length 0
//Post: makes a copy of string source
string::string(const string& source){
    assert(characters != NULL);
    char* newCharacters = new char[source.current_length];
    delete [] characters;
    characters = newCharacters;
    allocated = source.allocated;
    current_length = source.current_length;
    
}
string::~string(){
    delete [] characters;
}
//Post:Adds addend to a string
void string::operator +=(const string& addend){

    if(allocated< current_length + addend.current_length){
        reserve(addend.length() + length());
    }

    std::strncat(characters, addend.characters, addend.current_length);
    current_length = current_length + addend.length();
}
//Post:Adds addend to a string
void string::operator +=(const char addend[]){
    if(allocated< current_length + strlen(addend)){
        reserve(strlen(addend) + length()+2);
    }
    
    
    for(size_t i = 0;i < strlen(addend); i++){
        characters[current_length + i] = addend[i];
    }
    current_length = current_length + strlen(addend);
    
}
//Post:Adds addend to a string
void string::operator +=(char addend){
    
    if(allocated < current_length + 1){
        reserve(length() + 1);
    }
    characters[length()] = addend;
    current_length +=1;
}
//Pre: n cannot be smaller than the amount already allocated
//Post: Allocates more memory for the bag that is a string
void string::reserve(size_t n){
    if(n == allocated){
        return;
    }
    if(n<allocated){
        std::cout<< "cannot allocate less" <<std::endl;
        return;
    }
    if(n< current_length +1){
        n = current_length +1;
    }
   
    char* newChar = new char[n];
    
   if(characters != NULL){
        std::strncpy(newChar, characters, current_length);
        
        delete [] characters;
   }
    
    allocated = n + 1;
    characters = newChar;

}
//Post: assignment operator, copys over the string
string& string::operator =(const string& source){
    if (&source == this){
        return *this;
    }
    reserve(source.current_length);
    std::strncpy(characters, source.characters, allocated);
    current_length = source.current_length;
    return *this;
}
//Pre:position cannot be less than 0 or greater than length
//Post: inserts source into the string from position
void string::insert(const string& source, unsigned int position){
    assert(position <= length());
    char* newStr = new char[length() + source.length() +1];
    if(position + source.length() > length()){
        reserve(allocated + source.length() +1);
    }
    //First we shift

    strncpy (newStr, characters, position);
    strncat (newStr, source.characters, source.length());
    strncat (newStr, characters + position, current_length - position);
    delete [] characters;
    characters = newStr;
    current_length = source.length() + length() ;
    characters [current_length] = '\0';
}
void string::dlt(unsigned int position, unsigned int num){
    if((position + num) >= length()){
        std::cout<< "out of bounds" << std::endl;
        return;
    }
    size_t iterator = position;
    for(size_t j = position + num; j<current_length;j++){
        
        characters[iterator] = characters[j];
        iterator++;
    }
    current_length = current_length-num;
    characters[current_length] = '\0';
    
    
}
void string::replace(char c, unsigned int position){
    characters[position] = c;
}
void string::replace(const string& source, unsigned int position){
    if(allocated < source.current_length + position){
        reserve(source.current_length + position +1);
    }
    for(size_t i = 0; i<source.current_length;i++){
        characters[position + i] = source[i];
    }
}
char string::operator [](size_t position) const{
    
    //cout<< characters << endl;
    
    if(position > (length()-1)){
        std::cout << "Out of bounds" << std::endl;
        return '\0';
    }
    
    return characters[position];

}
//Post: returns the first index where c is found
int string::search(char c) const{
    for(size_t i = 0; i < length(); i++){
        if(characters[i] == c){
            return i;
        }
    }
    std::cout << "Character not Found" << std::endl;
    return -1;
}
//Post: Returns the index where the substring is found
int string::search(const string& substring) const{
    if(substring.current_length == 0){
        return -1;
    }
    for(size_t i = 0; i < (current_length - substring.length()); i++){
        if(characters[i + substring.length()-1] == '\0'){
            std::cout << "Not Found" << std::endl;
            return -1;
        }
        for (size_t j = 0; j < substring.current_length; j++){
            bool found = true;
            if (characters[i + j] != substring.characters[j]){
                found = false;
                break;
            }
            if(found){
                return i; 
            }
        }
        
    
    }
    return 0;

}
//Post: Returns the amount of char c is in the string
unsigned int string::count(char c) const{
    int count;
    for(size_t i = 0; i< length();i++){
        if(characters[i] == c){
            count++;
        }
    }
    return count;
}

std::ostream& coen79_lab5::operator <<(std::ostream& outs, const string& source){
    outs << source.characters;
    return outs;
}
bool coen79_lab5::operator ==(const string& s1, const string& s2){
    return (bool)(std::strcmp(s1.characters, s2.characters) == 0);
}
bool coen79_lab5::operator !=(const string& s1, const string& s2){
    return !(s1==s2);
}
bool coen79_lab5::operator > (const string& s1, const string& s2){
    return (bool)(std::strcmp(s1.characters, s2.characters)>0);
}
bool coen79_lab5::operator < (const string& s1, const string& s2){
    return (bool)(std::strcmp(s1.characters, s2.characters)<0);
}
bool coen79_lab5::operator >=(const string& s1, const string& s2){
    return !(s1<s2);
}
bool coen79_lab5::operator <=(const string& s1, const string& s2){
    return !(s1>s2);
}
string coen79_lab5::operator +(const string& s1, const string& s2){
    string copy(s1);
    copy += s2;
    return copy;
}
string coen79_lab5::operator +(const string& s1, const char addend[ ]){
    string copy(s1);
    copy += addend;
    return copy;
}
std::istream& coen79_lab5::operator >> (std::istream& ins, string& target){
    char maxInp[100];
    ins >> maxInp;
    target = maxInp;
    return ins;
}
