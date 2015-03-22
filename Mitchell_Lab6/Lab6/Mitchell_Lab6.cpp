#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Tree23.h"

#include <sstream>
#include "Timer.cpp"
#include "BinarySearchTree.h"
using namespace std;

int main(int argc, char* argv[]) {

	ifstream myfile;

	// If no command line argument, open hard coded file
	if (argc > 1)
		myfile.open(argv[1]);
	else
		myfile.open("data.txt");
	string word;

	Tree23<long>* tree = new Tree23<long>();

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

/*
	for (long i = 50000; i <= 400000; i += 50000) {
	    for (int j = 1; j < 6; j++) {


	      BinarySearchTree<long> bst;
	      Tree23<long> tree23;
	      Timer t;
	      cout << "BST Insert for n = " << i << " and Seed = " << j << " Time = ";
	      t.start();


	      srand(j);
	      for (int k = 0; k < i; k++) {
	    	  long x = rand() % RAND_MAX;

	    	  bst.insert(x);
	      }

	      t.printTime(t.stop());

	      cout << "BST Insert and Delete for n = " << j << " Time = ";
	      t.start();
	      for (int k = 0; k < i; k++) {
	    	  for(int l = 1; l <= i / 10; l++) {
	    		  double x = rand() / (double)RAND_MAX;
	    		  if(x < 0.25)
	    			  bst.deletemin();
	    		  else if(0.25 <= x && x < 0.5)
	    			  bst.deletemax();
	    		  else if(0.5 <= x && x < 0.75)
	    			  bst.remove(rand() % (4 * i));
	    		  else {
	    			  bst.insert(rand() % (4 * i));
	    		  }
	    	  }
	      }
	      t.printTime(t.stop());


	      cout << "2-3 Tree Insert for n = " << j << " Time = ";
	      t.start();

	      srand(j);
	      for (int k = 0; k < i; k++) {
	    	  fstream file;
	    	  file.open("DumpFile.txt",fstream::in | fstream::out | fstream::app);
	    	  long x = rand() % RAND_MAX;
	    	      	  file << x << " ";
	    	      	  file.close();
	    	  tree23.insert(x);
	      }
	      t.printTime(t.stop());

	      cout << "2-3 Tree Insert and Delete for n = " << j << " Time = ";
	      t.start();
	      for (int k = 0; k < i; k++) {
	    	  for(int l = 1; l <= i / 10; i++) {
	    		  int x = rand() % RAND_MAX;
	    		  if(x < 0.25)
	    			  tree23.deletemin();
	    		  else if(0.25 <= x && x < 0.5)
	    			  tree23.deletemax();
	    		  else if(0.5 <= x  && x < 0.75)
	    			  tree23.remove(rand() % (4 * i));
	    		  else {
	    			  tree23.insert(rand() % (4 * i));
	    		  }
	    	  }
	      }
	      t.printTime(t.stop());

	    }
	  }
*/

	return 0;
}
