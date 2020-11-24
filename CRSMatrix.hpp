#ifndef CRS_H
#define CRS_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Triplet and auxillary functions

class Triplet
{
public:
  unsigned int i;
  unsigned int j;
  int value;

  Triplet(unsigned int _i, unsigned int _j, unsigned int _v): i(_i), j(_j), value(_v) {}
};

bool compareColumns(Triplet t1, Triplet t2);
bool compareRows(Triplet t1, Triplet t2);
bool compareValues(Triplet t1, Triplet t2);

// auxillary classes for CRS rows and columns
class Row_CRS
{
private:
  unsigned int length = 0;
public:
  std::vector<int> values;
  std::vector<unsigned int> columns;
  
  Row_CRS();

  void set_length(unsigned int l);
  void set_values(std::vector<int> v);
  void set_columns(std::vector<unsigned int> c);
  unsigned int get_length();
  std::vector<int> get_values();
  std::vector<unsigned int> get_columns();

  Row_CRS operator+(Row_CRS& b);
};
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

  void insert(const Triplet &t);
  void fill(const std::vector<Triplet> &t);
//  void update_rows_index(unsigned int row);
  Row_CRS get_row(unsigned int row);

  CRSMatrix operator=(const CRSMatrix& B);
  CRSMatrix operator+(const CRSMatrix& B);
  CRSMatrix operator-(const CRSMatrix& B);
  CRSMatrix operator*(const CRSMatrix& B);
  CRSMatrix operator*(double lambda);

  friend std::ostream& operator<<(std::ostream& os, CRSMatrix& A);
};

// ыstd::istream& operator>>(std::istream& is, CRSMatrix& A);


CRSMatrix operator*(double lambda, const CRSMatrix& A);

#endif
