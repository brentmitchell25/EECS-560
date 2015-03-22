#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Tree23.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;

	// If no command line argument, open hard coded file
	if (argc > 1)
		myfile.open(argv[1]);
	else
		myfile.open("data.txt");
	string word;

	Tree23<int>* tree = new Tree23<int>();

	while (!myfile.eof()) {
		getline(myfile, word, ' ');
		tree->insert(atoi(word.c_str()));
	}
	myfile.close();

	while (true) {

		cout << "\nPlease choose one of the following commands:\n";
		cout << "\n1 - insert\n";
		cout << "\n2 - remove\n";
		cout << "\n3 - deletemin\n";
		cout << "\n4 - deletemax\n";
		cout << "\n5 - levelorder\n";
		cout << "\n6 - exit\n\n> ";

		int choice;
		int number;
		cin >> choice;
		if (choice == 1) {
			cout << "\nChoose a number to be inserted to the list:\n\n> ";
			cin >> number;
			tree->insert(number);
		} else if (choice == 2) {
			cout << "\nChoose a number to be deleted to the list:\n\n> ";
			cin >> number;
			if (!tree->remove(number)) {
				cout << endl << number << " is not in the tree.";
			}
		} else if (choice == 3) {
			tree->deletemin();
		} else if (choice == 4) {
			tree->deletemax();
		} else if (choice == 5) {
			tree->levelorder();
		} else {
			return 0;
		}

		cout << "\n\n---------------------------------------\n";
	}
	delete tree;
	return 0;
}
