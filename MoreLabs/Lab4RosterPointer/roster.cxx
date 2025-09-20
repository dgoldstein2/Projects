/*
 * CSEN 79 Lab Sample Code
 * Dakota Goldstein and Kayla Malloy
 * dagoldstein@scu.edu and krmalloy@scu.edu
 * Lab 4
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
	
	//Pre: rec is a valid student
	//Post: inserts Student into the roster and returns true if it was successful
	bool Roster::insert(T &rec) {
		try{ //allocate new memory
		T* newStudents = new T[index + 1];
		copy(students, students+index, newStudents); //copy students and delete old record
		delete [] students;
                students = newStudents;
		} catch (const bad_alloc &e){
			cout << "Allocation failed." << endl;
			return false;
		}	       
		for(int i = 0; i < index; i++){  //ensures no duplicates
			if(students[i].getID() == rec.getID()){
				cout << "cannot insert student, ID already entered\n" << endl;
				return false;
			}
		}
		students[index++] = rec;
		return true;
	}

	
	//Pre condition: Valid student ID
	//Post:Deletes the information for the student if ID is found in the roster.
	void Roster::erase(Student::ID_t id) {
		for(int i = 0; i < index; i++){
			if(students[i].getID() == id){
				cout << students[i] << " removed.\n";
				for(int j = i; j < index-1; j++){
					students[j] = students[j+1];
				}
				index--;
				return;
			}
		}
		cout << "cannot remove student\n";
		return;
	}

	// rudimentary iterator
	Roster::T* Roster::begin(void) {
		T *i;
		i = students;
		iterator = 0;
		return i;
	}

	Roster::T* Roster::end(void) {
		return students + index;
	}

	// The next element for interation
	Roster::T* Roster::next(void) {
		if(iterator > index){
			throw out_of_range(string("cannot access data, out of range.\n"));
		}
		iterator++;
		return students+iterator;
	}



}
