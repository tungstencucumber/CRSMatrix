#ifndef CRS_H
#define CRS_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Triplet and auxillary functions

struct Triplet {
  unsigned int i;
  unsigned int j;
  int value;
};

bool compareColumns(Triplet t1, Triplet t2);
bool compareRows(Triplet t1, Triplet t2);
bool compareValues(Triplet t1, Triplet t2);

//CRS Matrixes

class CRSMatrix
{
private:
  unsigned int m, n;
  std::vector<int> values;
  std::vector<unsigned int> columns;
  std::vector<unsigned int> rows_index;
public:
  CRSMatrix();
  CRSMatrix(unsigned int _m, unsigned int _n);
  ~CRSMatrix();

  CRSMatrix operator+(const CRSMatrix& B);
  CRSMatrix operator-(const CRSMatrix& B);
  CRSMatrix operator*(const CRSMatrix& B);
  CRSMatrix operator*(double lambda);

  void insert(const Triplet &t);

  friend std::ostream& operator<<(std::ostream& os, CRSMatrix& A);
};

// ыstd::istream& operator>>(std::istream& is, CRSMatrix& A);


CRSMatrix operator*(double lambda, const CRSMatrix& A);

#endif
