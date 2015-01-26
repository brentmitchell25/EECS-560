#include <stdio.h>
#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, const char* argv[]) {
	ifstream myfile;
	  myfile.open (argv[1]);
string line;
while ( getline (myfile,line,' ') )
    {
      cout << line << '\n';
    }
	  myfile.close();

	while (true) {

		cout << "\nPlease choose one of the following commands:\n";
		cout << "\n1 - insert\n";
		cout << "\n2 - delete\n";
		cout << "\n3 - print\n";
		cout << "\n4 - exit\n\n> ";

		int input;
		cin >> input;
		if (input == 4) {
			return 0;
		}

		cout << "\n--------------------\n";
	}
}
