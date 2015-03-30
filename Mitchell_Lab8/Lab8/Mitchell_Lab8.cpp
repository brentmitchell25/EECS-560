#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "MinLefistHeap.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;

	// If no command line argument, open hard coded file
	if (argc > 1)
		myfile.open(argv[1]);
	else
		myfile.open("data.txt");
	string word;

	MinLeftistHeap<int>* mlh = new MinLeftistHeap<int>();
	while (!myfile.eof()) {
		getline(myfile, word, ' ');
		mlh->insert(atoi(word.c_str()));
	}
	myfile.close();


	while (true) {

		cout << "\nPlease choose one of the following commands:\n";
		cout << "\n1 - insert\n";
		cout << "\n2 - deletemin\n";
		cout << "\n3 - preorder\n";
		cout << "\n4 - inorder\n";
		cout << "\n5 - levelorder\n";
		cout << "\n6 - exit\n\n> ";

		int choice;
		int number;
		cin >> choice;
		if (choice == 1) {
			cout << "\nChoose a number to be inserted to the list:\n\n> ";
			cin >> number;
			mlh->insert(number);
		}  else if (choice == 2) {
			mlh->deletemin();
		} else if (choice == 3) {
			mlh->preorder();
		} else if (choice == 4) {
			mlh->inorder();
		} else if (choice == 5) {
			mlh->levelorder();
		} else {
			return 0;
		}

		cout << "\n\n---------------------------------------\n";
	}
	delete mlh;




	return 0;
}
