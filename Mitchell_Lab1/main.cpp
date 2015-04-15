#include "List.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;
int main(int argc, const char* argv[]) {
	ifstream myfile;

	// If no command line argument, open hard coded file
	if(argc > 1)
		myfile.open(argv[1]);
	else
		myfile.open("data.txt");
	string word;
	List l;
	
	// This assumes there are no hidden charcters at end of file
	// Found some text editors add hidden characters, which results
	// in the last item in the list not be able to be deleted.
	while (getline(myfile, word, ' ') && !word.empty()) {
	  l.insert(word);
	}
	myfile.close();

	while (true) {

		cout << "\nPlease choose one of the following commands:\n";
		cout << "\n1 - insert\n";
		cout << "\n2 - delete\n";
		cout << "\n3 - print\n";
		cout << "\n4 - exit\n\n> ";

		int choice;
		std::string number;
		cin >> choice;
		if (choice == 1) {
			cout << "\nChoose a number to be inserted to the list:\n\n> ";
			cin >> number;
			l.insert(number);
		} else if (choice == 2) {
			cout << "\nChoose a number to be deleted to the list:\n\n> ";
			cin >> number;
			if (!l.erase(number)) {
				cout << "\nThe number entered is not in the list.";
			}
		} else if (choice == 3) {
			l.print();
		} else {
			return 0;
		}

		cout << "\n\n---------------------------------------\n";
	}
}
