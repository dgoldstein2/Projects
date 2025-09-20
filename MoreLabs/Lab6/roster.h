/*
 * CSEN 79 Lab Sample Code
 * Lab 3
 * Dakota Goldstein and Kayla Malloy
 * dagoldstein@scu.edu and krmalloy@scu.edu
 * file: roster.h
 * Description: File builds the class of roster and student to be used in the files.
 * Setters and getters are defined in this file that can be used to access and change the private variables.
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
		Student(ID_t n, std::string fn, std::string ln){
			idn = n;
			firstName = fn;
			lastName = ln;
		}
		std::string getFirstName(){return firstName;};//I added
		std::string getLastName(){return lastName;};//I added
		void setFirstName(std::string newFName){firstName = newFName;}
		void setLastName(std::string newLName){lastName = newLName;}
		void setID(ID_t nid){idn = nid;}

		ID_t getID(){return idn;};//I added
	friend std::ostream& operator<<(std::ostream& os, const Student &);
	private: //This whole thing I added
		std::string firstName;
		std::string lastName;
		ID_t idn;
	};

	class Roster {
	public:
		using T = Student;
		Roster(): index{0}, iterator{0} {};
		static const int CAPACITY=30;
		bool insert(T &);
		void erase(Student::ID_t);
		T* begin(void);
		T* end(void);
		T* next(void);
	private:
		T students[CAPACITY];
		int index;
		int iterator;
	};
}
#endif // ROSTER_H