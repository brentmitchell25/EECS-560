//============================================================================
// Name        : Mitchell_Lab9.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "BinomialQueue.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;

		// If no command line argument, open hard coded file
		if (argc > 1)
			myfile.open(argv[1]);
		else
			myfile.open("data.txt");
		string word;

		BinomialQueue<int>* bq = new BinomialQueue<int>();
		//SkewHeap<int> *bq = new SkewHeap<int>();
		while (!myfile.eof()) {
			getline(myfile, word, ' ');
			bq->insert(atoi(word.c_str()));
		}
		myfile.close();


		while (true) {

			cout << "\nPlease choose one of the following commands:\n";
			cout << "\n1 - insert\n";
			cout << "\n2 - deletemin\n";
			cout << "\n3 - levelorder\n";
			cout << "\n4 - exit\n\n> ";

			int choice;
			int number;
			cin >> choice;
			if (choice == 1) {
				cout << "\nChoose a number to be inserted to the list:\n\n> ";
				cin >> number;
				bq->insert(number);
			}  else if (choice == 2) {
				bq->deletemin();
			} else if (choice == 3) {
				bq->levelorder();
			} else {
				return 0;
			}

			cout << "\n\n---------------------------------------\n";
		}
		delete bq;
}
