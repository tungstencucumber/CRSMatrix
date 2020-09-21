#include "CRSMatrix.hpp"

bool compareColumns(Triplet t1, Triplet t2)
{
  return t1.j < t2.j;
}

bool compareRows(Triplet t1, Triplet t2)
{
  return t1.i < t2.i;
}

bool compareValues(Triplet t1, Triplet t2)
{
  return t1.value < t2.value;
}


CRSMatrix::CRSMatrix(): m(0), n(0) {}

CRSMatrix::CRSMatrix(unsigned int _m, unsigned int _n): m(_m), n(_n)
{
  rows_index.resize(m + 1);
  for(unsigned int i = 0; i < m + 1; i++)
    rows_index[i] = 0;
}

CRSMatrix::~CRSMatrix() {}

void CRSMatrix::insert(const Triplet &t)
{
  unsigned short index = this->rows_index[t.i];
  if(values.empty())
  {
    this->values.push_back(t.value);
    this->columns.push_back(t.j);
  }
  else
  {
    for(unsigned int i = 0; i < rows_index[t.i + 1] - rows_index[t.i]; i++)
    {
      if(this->columns[index] >= t.j)
        break;
      index++;
    }

    if(columns[index] == t.j)
    {
      values[index] = t.value;
      return;
    }
    else
    {
      this->values.insert(this->values.begin() + index, t.value);
      this->columns.insert(this->columns.begin() + index, t.j);
    }
  }

  for(unsigned int k = t.i + 1; k < rows_index.size(); k++)
    this->rows_index[k]++;

  cout << "values = [";
  for(unsigned int i = 0; i < values.size(); i++)
    cout << values[i] << ", ";
  cout << "]\n";
  cout << "columns = [";
  for(unsigned int i = 0; i < columns.size(); i++)
    cout << columns[i] << ", ";
  cout << "]\n";
  cout << "rows_index = [";
  for(unsigned int i = 0; i < rows_index.size(); i++)
    cout << rows_index[i] << ", ";
  cout << "]\n";
}

/*
std::istream& operator>>(std::istream& is, CRSMatrix& A)
{
  sort(input.begin(), input.end(), compareColumns);
  sort(input.begin(), input.end(), compareRows);

  unsigned int rows_index_count = 0;
  for(vector<Triplet>::iterator it = input.begin(); it != input.end(); ++it)
  {
    A.values.push_back((*it).value);
    A.columns.push_back((*it).j);

    if (it == input.begin()) {
      A.rows_index_count.push_back(0);
    }
    else
    {
      if((*it).i == (*(it - 1)).i)
        rows_index_count++;
      else
      {
        A.rows_index.push_back(rows_index_count);
        rows_index_count = 1;
      }
    }

  }
  return is;
} */

std::ostream& operator<<(std::ostream& os, CRSMatrix& A)
{
  unsigned int cur_row = 0;
  for(unsigned int k = 0; k < A.values.size(); k++)
  {
    if(cur_row < A.n)
      if(k >= A.rows_index[cur_row + 1])
        while(k >= A.rows_index[cur_row + 1])
          cur_row++;
    cout << "A(" << cur_row << "," << A.columns[k] << ") = " << A.values[k] << ";\n";
  }
  return os;
}
