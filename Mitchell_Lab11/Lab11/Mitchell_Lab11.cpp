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
	MinimumSpanningTree mst;


	for (int i = 0; i < testCases; i++) {
		int j = 0;
		getline(myfile, word, '\n');
		nodes = atoi(word.c_str());

		int am[nodes*nodes];

		do {
			getline(myfile, word, '\n');
			istringstream iss(word);
			string s;
			for (int k = j * nodes; getline(iss, s, ' ');k++) {
				am[k] = atoi(s.c_str());
			}
			j++;
		} while (j < nodes);
		cout << "Graph" << i+1 << ":" << endl;
		mst.kruskal(am,nodes);
		mst.prim(am,nodes);
		cout << endl;
	}
	myfile.close();

}
