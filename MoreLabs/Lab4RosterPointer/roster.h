/*
 * CSEN 79 Lab Sample Code
 * Lab 4
 * Dakota Goldstein and Kayla Malloy
 * dagoldstein@scu.edu and krmalloy@scu.edu
 * file: roster.h
 * Description: File builds the class of roster and student to be used in the files.
 * getters are defined in this file that can be used to access and change the private variables.
 * Sets up the array used throughout the code.
 * 
 */
#ifndef ROSTER_H
#define ROSTER_H

#include <vector>
// Class declaration for roster
namespace csen79 {
	// base data for the roster
	class Student {
	public:
		using ID_t = unsigned int;	// really should be a 7-digit unsigned int
		Student(): Student(0, "", "") {};
		Student(ID_t n, std::string fn, std::string ln){ //Creates a student with a last name, first name and an ID
			idn = n;
			firstName = fn;
			lastName = ln;
		}

		ID_t getID(){return idn;}; //Returns the ID
	friend std::ostream& operator<<(std::ostream& os, const Student &);
	private: 
		std::string firstName;
		std::string lastName;
		ID_t idn;
	};

	class Roster {
	public:
		using T = Student;
		Roster(): students{nullptr}, index{0}, iterator{0} {};
		~Roster() { delete [] students; } //destroys array
		static const int CAPACITY=30;
		bool insert(T &);
		void erase(Student::ID_t);
		T* begin(void);
		T* end(void);
		T* next(void);
	private:
		T* students; //Creates an array that is used to hold students 
		int index; //Keeps track of how many elements are in roster
		int iterator; //Keeps track of where the pointer should be for the list
	};
}

#endif // ROSTER_H
