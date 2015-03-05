#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>

#define table_size 600011
using namespace std;

int main(int argc, char** argv) {
  
  for(double i = 0.2; i <= 0.6; i+=.1) {
    for(int j = 1; j < 6; j++) {
      ofstream file;
      file.open("LoadFactor.txt");
      file << table_size << " ";
      for(int k = 0; i < table_size; k++) {
	srand(j);
	long randomNumber = rand() % (int)(table_size * i);
	file << randomNumber << " ";
      }
      file.close();
    }
  }

  return 0;
}
