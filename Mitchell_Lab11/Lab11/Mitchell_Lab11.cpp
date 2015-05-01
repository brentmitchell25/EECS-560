#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "MinimumSpanningTree.h"
#include "DisjointSet.h"
#include "SetNode.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream myfile;
/*
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
*/
		int numElements = 128;
            int numInSameSet = 16;

            DisjointSet<int> ds;
            for(int i = 0; i <= numElements;i++)
            	ds.makeSet(i);
            SetNode<int>* set1;
            SetNode<int>* set2;

            for( int k = 1; k < numInSameSet; k *= 2 )
            {
                for( int j = 0; j + k < numElements; j += 2 * k )
                {
                	SetNode<int> *temp = new SetNode<int>(j);
                	SetNode<int> *temp2 = new SetNode<int>(j+k);
                    set1 = ds.find( temp );
                    set2 = ds.find( temp2);
                    ds.unionSets(set1, set2);
                }
            }

            for( int i = 0; i < numElements; i++ )
            {
            	set1 = new SetNode<int>(i);
                cout << ds.find(set1)->key << "*";
                if( i % numInSameSet == numInSameSet - 1 )
                    cout << endl;
            }
            cout << endl;

}
