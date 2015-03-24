#include <iostream>
#include <fstream>
#include "MinMaxHeap.h"
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

	MinMaxHeap<int>* mmh = new MinMaxHeap<int>();
	while (!myfile.eof()) {
		getline(myfile, word, ' ');
		mmh->insert(atoi(word.c_str()));
	}
	myfile.close();



	while (true) {

		cout << "\nPlease choose one of the following commands:\n";
		cout << "\n1 - insert\n";
		cout << "\n2 - deletemin\n";
		cout << "\n3 - deletemax\n";
		cout << "\n4 - levelorder\n";
		cout << "\n5 - exit\n\n> ";

		int choice;
		int number;
		cin >> choice;
		if (choice == 1) {
			cout << "\nChoose a number to be inserted to the list:\n\n> ";
			cin >> number;
			mmh->insert(number);
		}  else if (choice == 2) {
			mmh->deletemin();
		} else if (choice == 3) {
			mmh->deletemax();
		} else if (choice == 4) {
			mmh->print();
		} else {
			return 0;
		}

		cout << "\n\n---------------------------------------\n";
	}
	delete mmh;




	return 0;
}
