#include "MinLeftistHeap.h"

#include <sstream>
#include <fstream>
#include "SkewHeap.h"
#include "Timer.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	for (long i = 50000; i <= 400000; i *= 2) {
		for (int j = 1; j < 6; j++) {

			MinLeftistHeap<long> *mlh1 = new MinLeftistHeap<long>();

			Timer t;
			cout << "MinLeftistHeap Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			int k = 0;
			for (k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;

				mlh1->insert(x);
			}

			t.printTime(t.stop());
			delete mlh1;

			MinLeftistHeap<long> *mlh2 = new MinLeftistHeap<long>();
			cout << "MinLeftistHeap Insert and Delete for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();
				for (int l = 1; l <= i / 10; l++) {
					double x = rand() / (double) RAND_MAX;
					if (x < 0.5)
						mlh2->deletemin();
					else {
						mlh2->insert(rand() % (4 * i));
					}
				}

			t.printTime(t.stop());

			delete mlh2;

			SkewHeap<long> *sh1 = new SkewHeap<long>();
			cout << "SkewHeap Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;
				sh1->insert(x);
			}
			t.printTime(t.stop());
			delete sh1;
			cout << "SkewHeap Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";

			SkewHeap<long> *sh2 = new SkewHeap<long>();
			t.start();
			for (int l = 1; l <= i / 10; l++) {
				double x = rand() / (double)RAND_MAX;
				long number = rand() % (4 * i);

				if (x < 0.5)
					sh2->deletemin();
				else {
					sh2->insert(number);
				}

			}
			t.printTime(t.stop());
			delete sh2;
		}
	}
	cout << "Done!";
	return 0;
}
