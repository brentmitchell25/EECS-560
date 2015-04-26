#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "Timer.cpp"
#include "OpenHashTable.h"
#include "ClosedHashTable.h"

#define table_size 600011
using namespace std;

int main(int argc, char** argv) {

  for (double i = 0.2; i <= 0.6; i += .1) {
    for (int j = 1; j < 6; j++) {
      ofstream file;
      ostringstream s;
      s << i;

      srand(j);
      long number[table_size];
      for (int k = 0; k < table_size; k++) {
	number[k] = rand() % (long) (table_size * i);
      }

      Timer t;
      OpenHashTable *oht = new OpenHashTable(table_size);


      cout << "Open Hash Table: Load Factor = " << s.str() << " Seed = " << j << " Time = ";

      t.start();
      for(int l = 0; l < table_size;l++)
	oht->insert(number[l]);
      t.printTime(t.stop());
      delete oht;

      ClosedHashTable *cht = new ClosedHashTable(table_size);
      cout << "Closed Hash Table: Load Factor = " << s.str() << " Seed = " << j << " Time = ";

      t.start();
      for(int l = 0; l < table_size;l++)
	cht->insert(number[l]);
      t.printTime(t.stop());
      delete cht;

    }
  }

  return 0;
}
