#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;

	// If no command line argument, open hard coded file
	if (argc > 1)
		myfile.open(argv[1]);
	else
		myfile.open("data.txt");
	string word;

	BinarySearchTree<int>* bst = new BinarySearchTree<int>();
	;

	while (!myfile.eof()) {
		getline(myfile, word, ' ');
		bst->insert(atoi(word.c_str()));
	}
	myfile.close();

	while (true) {

		cout << "\nPlease choose one of the following commands:\n";
		cout << "\n1 - insert\n";
		cout << "\n2 - remove\n";
		cout << "\n3 - deletemin\n";
		cout << "\n4 - deletemax\n";
		cout << "\n5 - preorder\n";
		cout << "\n6 - inorder\n";
		cout << "\n7 - levelorder\n";
		cout << "\n8 - exit\n\n> ";

		int choice;
		int number;
		cin >> choice;
		if (choice == 1) {
			cout << "\nChoose a number to be inserted to the list:\n\n> ";
			cin >> number;
			bst->insert(number);
		} else if (choice == 2) {
			cout << "\nChoose a number to be deleted to the list:\n\n> ";
			cin >> number;
			if (!bst->remove(number)) {
				cout << endl << number << " is not in the tree.";
			}
		} else if (choice == 3) {
			bst->deletemin();
		} else if (choice == 4) {
			bst->deletemax();
		} else if (choice == 5) {
			bst->preorder();
		} else if (choice == 6) {
			bst->inorder();
		} else if (choice == 7) {
			bst->levelorder();
		} else {
			return 0;
		}

		cout << "\n\n---------------------------------------\n";
	}
	delete bst;
	return 0;
}
