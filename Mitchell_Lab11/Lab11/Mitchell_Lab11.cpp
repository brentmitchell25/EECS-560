#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "MinimumSpanningTree.h"
#include "DisjointSet.h"
#include "SetNode.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;

	// If no command line argument, open hard coded file
	if (argc > 1)
		myfile.open(argv[1]);
	else
		myfile.open("data.txt");
	string word;
	getline(myfile, word, '\n');
	int testCases = atoi(word.c_str());
	int nodes = 0;
	MinimumSpanningTree<int>* mst = new MinimumSpanningTree<int>();

	for (int i = 0; i < testCases; i++) {
		int j = 0;
		getline(myfile, word, '\n');
		nodes = atoi(word.c_str());
		do {
			getline(myfile, word, '\n');
			//mst->insert(atoi(word.c_str()));
			istringstream iss(word);
			string s;
			while (getline(iss, s, ' ')) {
				cout << s << endl;
			}
			j++;
		} while (j <= nodes);

	}
	myfile.close();

}
