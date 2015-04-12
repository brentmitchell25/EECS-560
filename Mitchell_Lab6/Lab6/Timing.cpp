/*
 * Timing.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: brentmitchell
 */
#include "Tree23.h"

#include <sstream>
#include <fstream>
#include "Timer.cpp"
#include "BinarySearchTree.h"

int main(int argc, char* argv[]) {
	for (long i = 50000; i <= 400000; i += 50000) {
		for (int j = 1; j < 6; j++) {

			BinarySearchTree<long> *bst1 = new BinarySearchTree<long>();

			Timer t;
			cout << "BST Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;

				bst1->insert(x);
			}

			t.printTime(t.stop());
			delete bst1;

			BinarySearchTree<long> *bst2 = new BinarySearchTree<long>();
			cout << "BST Insert and Delete for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();
				for (int l = 1; l <= i / 10; l++) {
					double x = rand() / (double) RAND_MAX;
					if (x < 0.25)
						bst2->deletemin();
					else if (0.25 <= x && x < 0.5)
						bst2->deletemax();
					else if (0.5 <= x && x < 0.75)
						bst2->remove(rand() % (4 * i));
					else {
						bst2->insert(rand() % (4 * i));
					}
				}

			t.printTime(t.stop());

			delete bst2;

			Tree23<long> *tree231 = new Tree23<long>();
			cout << "2-3 Tree Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;
				tree231->insert(x);
			}
			t.printTime(t.stop());
			delete tree231;
			cout << "2-3 Tree Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";

			Tree23<long> *tree232 = new Tree23<long>();
			t.start();
			for (int l = 1; l <= i / 10; l++) {
				double x = rand() / (double)RAND_MAX;
				long number = rand() % (4 * i);

				if (x < 0.25)
					tree232->deletemin();
				else if (0.25 <= x && x < 0.5)
					tree232->deletemax();
				else if (0.5 <= x && x < 0.75)
					tree232->remove(number);
				else {
					tree232->insert(number);
				}

			}
			t.printTime(t.stop());
			delete tree232;
		}
	}
	cout << "Done!";
	return 0;
}
