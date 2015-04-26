#include <sstream>
#include <fstream>
#include "SkewHeap.h"
#include "MinLeftistHeap.h"
#include "MinLeftistHeap.h"
#include "BinomialQueue.h"
#include "Timer.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	ofstream file;
	file.open("TimingCSV.csv");
	for (long i = 50000; i <= 400000; i *= 2) {
		for (int j = 1; j < 6; j++) {

			MinLeftistHeap<long> *mlh1 = new MinLeftistHeap<long>();

			Timer t;
			file << "MinLeftistHeap Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			cout << "MinLeftistHeap Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			int k = 0;
			for (k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;

				mlh1->insert(x);
			}

			double stop = t.stop();
			file << "," << stop << endl;
			t.printTime(stop);
			delete mlh1;

			MinLeftistHeap<long> *mlh2 = new MinLeftistHeap<long>();

			file << "MinLeftistHeap Insert and Delete for n = " << i
					<< " and Seed = " << j << " Time = ";
			cout << "MinLeftistHeap Insert and Delete for n = " << i
					<< " and Seed = " << j << " Time = ";
			t.start();
			for (int l = 1; l <= i / 10; l++) {
				double x = rand() / (double) RAND_MAX;
				if (x < 0.5)
					mlh2->deletemin();
				else {
					mlh2->insert(rand() % (4 * i));
				}
			}

			stop = t.stop();
			file << "," << stop << endl;
			t.printTime(stop);

			delete mlh2;

			SkewHeap<long> *sh1 = new SkewHeap<long>();
			file << "SkewHeap Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			cout << "SkewHeap Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;
				sh1->insert(x);
			}
			stop = t.stop();
			file << "," << stop << endl;
			t.printTime(stop);
			delete sh1;
			file << "SkewHeap Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";
			cout << "SkewHeap Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";

			SkewHeap<long> *sh2 = new SkewHeap<long>();
			t.start();
			for (int l = 1; l <= i / 10; l++) {
				double x = rand() / (double) RAND_MAX;
				long number = rand() % (4 * i);

				if (x < 0.5)
					sh2->deletemin();
				else {
					sh2->insert(number);
				}

			}
			stop = t.stop();
			file << "," << stop << endl;
			t.printTime(stop);
			delete sh2;

			BinomialQueue<long> *bq1 = new BinomialQueue<long>();
			file << "BinomialQueue Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			cout << "BinomialQueue Insert for n = " << i << " and Seed = " << j
					<< " Time = ";
			t.start();

			srand(j);
			for (int k = 0; k < i; k++) {
				long x = rand() % RAND_MAX;
				bq1->insert(x);
			}
			stop = t.stop();
			file << "," << stop << endl;
			t.printTime(stop);
			delete bq1;
			file << "BinomialQueue Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";
			cout << "BinomialQueue Insert and Delete for n = " << i << " and Seed = "
					<< j << " Time = ";

			BinomialQueue<long> *bq2 = new BinomialQueue<long>();
			t.start();
			for (int l = 1; l <= i / 10; l++) {
				double x = rand() / (double) RAND_MAX;
				long number = rand() % (4 * i);

				if (x < 0.5)
					bq2->deletemin();
				else {
					bq2->insert(number);
				}

			}
			stop = t.stop();
			file << "," << stop << endl;
			t.printTime(stop);
			delete bq2;
		}
	}
	cout << "Done!";
	return 0;
}
