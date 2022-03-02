#include <iostream>
#include <vector>
#include "Matrix.h"
#include "TEST.h"

using namespace std;


int main(){
  Test1();
  Test2();
  Test3();
  Test4();
  Matrix r(1,3);
  cin >> r;
  cout << Transposition(r);
  return 0;
}