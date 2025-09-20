/*
 * CSEN 79 Lab Sample Code
 * Dakota Goldstein and Kayla Malloy
 * dagoldstein@scu.edu and krmalloy@scu.edu
 * Lab 3
 * file: roster.cxx
 * Description: Builds the functions using the class Roster 
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "roster.h"

using namespace std;
namespace csen79 {
	std::ostream& operator<<(std::ostream& os, const Student &t) {
		os << "Student Name: " << t.firstName << " " << t.lastName
		<< " ID: " << t.idn << endl;
		return os;
	}
	// state your pre-/post-conditions
	bool Roster::insert(T &rec) {
		if(index >= CAPACITY){
			cout << "roster full, cannot add more students." << endl;
			return false;
		}
		for(int i = 0; i < index; i++){
			if(students[i].getID() == rec.getID()){
				cout << "cannot insert student, ID already entered\n" << endl;
				return false;
			}
		}
		students[index] = rec;
		index++;
		return true;
	}

	// state your pre-/post-conditions
	void Roster::erase(Student::ID_t id) {
		for(int i = 0; i < index; i++){
			if(students[i].getID() == id){
				for(int j = i; j < index-2; j++){
					students[j] = students[j+1];
				}
				--index;
			}
		}
		return;
	}

	// rudimentary iterator
	Roster::T* Roster::begin(void) {
		iterator = 0;
		return nullptr;
	}

	Roster::T* Roster::end(void) {
		return nullptr;
	}

	// The next element for interation
	Roster::T* Roster::next(void) {
		return nullptr;
	}
}
