#include <iostream>
#include "CRSMatrix.hpp"

using namespace std;

int main() {
  CRSMatrix A = CRSMatrix(3, 3);
  Triplet t;
  t.i = 2;
  t.j = 2;
  t.value = 1;
  A.insert(t);

  t.i = 1;
  t.j = 0;
  t.value = 34;
  A.insert(t);

  t.i = 0;
  t.j = 1;
  t.value = 777;
  A.insert(t);

  t.i = 0;
  t.j = 2;
  t.value = 4;
  A.insert(t);

  t.i = 0;
  t.j = 0;
  t.value = 4;
  A.insert(t);

  t.i = 1;
  t.j = 1;
  t.value = 100;
  A.insert(t);

  cout << A;
  return 0;
}
