/*
 * CSEN 79 Lab Sample Code
 * Dakota Goldstein and Kayla Malloy
 * dagoldstein@scu.edu and krmalloy@scu.edu
 * Lab 3
 * file: rostermain.cxx
 * Description: Runs the fuctions and the classes using test students from an input file
 */
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "roster.h"
#include "rosterlist.h"

using namespace std;
using namespace csen79;

// Test code for class roster
// Input file: <CMD> [ID] [FIRST LAST]
// CMD : A | X | L
// ID: 7-digit unsigned integer
// FIRST, LAST: string
int main() {
	RosterList r;
	Student::ID_t id;
	string cmd, first, last;

	// Read cmd first, then branch accordingly
	while (cin >> cmd) {
		if (cmd == "A") {
			cin >> id >> first >> last;
			Student newStud = Student(id, first, last);
			r.insert(newStud);
		} else if (cmd == "X") {
			
			cin >> id;
			r.erase(id);
			
		} else if (cmd == "L") {
			// this should just work, if you did your begin/end/next correctly
			cout<< "Lists"<<endl;
			int i = 1;
			for (auto st = r.begin(); st != r.end(); ++st, i++)
				cout << i << ": " << *st << endl;
		} 
	}
	return EXIT_SUCCESS;
}

