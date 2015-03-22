/*
 * Timing.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: brentmitchell
 */
#include "Tree23.h"

#include <sstream>
#include "Timer.cpp"
#include "BinarySearchTree.h"

int main(int argc, char* argv[]) {
	for (long i = 50000; i <= 400000; i += 50000) {
		for (int j = 1; j < 6; j++) {

			BinarySearchTree<long> bst;
			Tree23<long> tree23;
			Timer t;
			cout << "BST Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;

				bst.insert(x);
			}

			t.printTime(t.stop());

			cout << "BST Insert and Delete for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();
			for (int k = 0; k < i; k++) {
				for (int l = 1; l <= i / 10; l++) {
					double x = rand() / (double) RAND_MAX;
					if (x < 0.25)
						bst.deletemin();
					else if (0.25 <= x && x < 0.5)
						bst.deletemax();
					else if (0.5 <= x && x < 0.75)
						bst.remove(rand() % (4 * i));
					else {
						bst.insert(rand() % (4 * i));
					}
				}
			}
			t.printTime(t.stop());

			cout << "2-3 Tree Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;
				tree23.insert(x);
			}
			t.printTime(t.stop());

			cout << "2-3 Tree Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";
			t.start();
			for (int l = 1; l <= i / 10; l++) {
				int x = rand() % RAND_MAX;
				if (x < 0.25)
					tree23.deletemin();
				else if (0.25 <= x && x < 0.5)
					tree23.deletemax();
				else if (0.5 <= x && x < 0.75)
					tree23.remove(rand() % (4 * i));
				else {
					tree23.insert(rand() % (4 * i));
				}

			}
			t.printTime(t.stop());

		}
	}
	return 0;
}
