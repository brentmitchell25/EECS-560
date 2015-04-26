#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "MinimumSpanningTree.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;

		// If no command line argument, open hard coded file
		if (argc > 1)
			myfile.open(argv[1]);
		else
			myfile.open("data.txt");
		string word;

		MinimumSpanningTree<int>* mst = new MinimumSpanningTree<int>();
		while (!myfile.eof()) {
			getline(myfile, word, ' ');
			mst->insert(atoi(word.c_str()));
		}
		myfile.close();


}
