#include <stdio.h>
#include <iostream>
using namespace std;
int main( int argc, const char* argv[] )
{
  cout << "\nPlease choose one of the following commands:\n";
  cout << "\n1 - insert\n";
  cout << "\n2 - delete\n";
  cout << "\n3 - print\n";
  cout << "\n4 - exit\n\n>";
  int input;
  cin >> input;
  if(input == 4) {
    return 0;
  }
}
