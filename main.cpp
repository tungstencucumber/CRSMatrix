#include <iostream>
#include "CRSMatrix.hpp"

using namespace std;

int main() {
  CRSMatrix A = CRSMatrix(5, 5);
  std::vector<Triplet> t;
  for(unsigned int i = 0; i < 5; i++)
    t.push_back(Triplet(i, i, 2*i));
  A.fill(t);
  cout << A << endl;
  auto row1 = A.get_row(4);
  cout << row1.get_values() << endl;
  /* CRSMatrix B = CRSMatrix(5, 5);
  B.insert(Triplet(1, 2, 1));
  CRSMatrix C = A + B;
  cout << C; */
  return 0;
}
