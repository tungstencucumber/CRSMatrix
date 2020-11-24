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

Row_CRS::Row_CRS() {}

void Row_CRS::set_length(unsigned int l) { length = l; }
void Row_CRS::set_values(std::vector<int> v) {values = v;}
void Row_CRS::set_columns(std::vector<unsigned int> c) {columns = c;}
unsigned int Row_CRS::get_length() { return length; }
std::vector<int> Row_CRS::get_values() { return values; }
std::vector<unsigned int> Row_CRS::get_columns() {return columns; }

Row_CRS Row_CRS::operator+(Row_CRS& b)
{
  try
  {
    if(this->length != b.get_length()) throw 1;

    Row_CRS c;
    c.length = b.length;
    for(unsigned int k = 0; k < b.length; k++)
    {
      
    }
  }
  catch(int a)
  {
    Row_CRS c;
    cout << "Wrong row sizes" << endl;
    return c;
  }
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

  // debug cout code (just in case)
  /* cout << "values = [";
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
  cout << "]\n"; */
}

Row_CRS CRSMatrix::get_row(unsigned int row)
{
  try
  {
    if(row > this->m || row < 0) throw 1;

    std::vector<int> _values;
    std::vector<unsigned int> _columns;
    for(unsigned int k = this->rows_index[row]; k < this->rows_index[row + 1]; k++)
    {
      _values.push_back(this->values[k]);
      _columns.push_back(this->columns[k]);
    }
    Row_CRS r;
    r.set_values(_values);
    r.set_columns(_columns);
    r.set_length(this->m);
    return r;
  }
  catch(int a)
  {
    cout << "There is no row of such index in the matrix" << endl;
    Row_CRS r;
    return r;
  }
}

void CRSMatrix::fill(const std::vector<Triplet> &t)
{
  for(std::vector<Triplet>::const_iterator it = t.begin(); it != t.end(); ++it)
    this->insert(*it);
}

CRSMatrix CRSMatrix::operator=(const CRSMatrix& B)
{
  values = B.values;
  columns = B.columns;
  rows_index = B.rows_index;
  return std::move(*this);
}

/*
// auxillary function to use after inserting single value
void CRSMatrix::update_rows_index(unsigned int row)
{
  for(std::vector<unsigned int>::iterator it = this->rows_index.begin() + row;
      it != this->rows_index.end(); ++it)
        *it++;
}

CRSMatrix CRSMatrix::operator+(const CRSMatrix& B)
{
  try
  {
    if(n != B.n || m != B.m) throw 1; // checking if matrixes are of same size
    if(values.empty()) // just in case
      return std::move(B);
    if(B.values.empty())
      return std::move(*this);

    CRSMatrix C = *this; // return object
    // two pointers to the value to which we're inserting B values
    std::vector<int>::iterator c_value = C.values.begin();
    std::vector<unsigned int>::iterator c_col = C.columns.begin();
    // second pointer to the current insertable value
    // (first is to be declared in the cycle conitions)
    std::vector<unsigned int>::const_iterator b_col = B.columns.begin();
    // what C row we are in right now
    unsigned int c_row = 1;
    // what B row we are in right now
    unsigned int b_row = 1;
    // currently passed elements of C (including inserted values)
    unsigned int passed_count = 0;
    // currently inserted elements of B
    unsigned int ins_count = 0;

    for(std::vector<int>::const_iterator b_value = B.values.begin();
        b_value != B.values.end(); ++b_value)
    {
      // shifting to other row
      if(passed_count >= С.rows_index[с_row])
        while(passed_count >= С.rows_index[с_row])
          с_row++;
      if(ins_count >= B.rows_index[b_row])
        while(ins_count >= B.rows_index[b_row])
          b_row++;
      //if this row in C is not empty
      if (passed_count - C.rows_index[b_row] < 0)
      {
        // cause we're inserting b_value before c_value
        // we're shifting the c_value pointer till it's after b_value
        while(*c_col < *b_col && c_col != C.columns.end()) {
          ++c_value;
          ++c_col;
          passed_count++;
        }
        if(*c_col == *b_col) // if b_col in this row is already occupied
        // we just add b_value to it
        {
          *c_value += *b_value;
        }
        else // otherwise we just insert the b_value
        // and update the data about the elements in C
        {
          C.values.insert(c_value, *b_value);
          C.columns.insert(c_col, *b_col);
          C.update_rows_index(b_row);
          passed_count++;
        }
        ins_count++;
      }
      else //if it is empty
      {
        if(passed_count - C.rows_index[b_row] < 0)
      }
      ++b_col;
    }

    return std::move(C);
  }
  catch(int a)
  {
    cout << "Operands have different sizes";
    return std::move(*this);
  }
}
*/

CRSMatrix CRSMatrix::operator+(const CRSMatrix& B)
{
  if(n != B.n || m != B.m) throw 1; // checking if matrixes are of same size
  if(values.empty()) // just in case
    return std::move(B);
  if(B.values.empty())
    return std::move(*this);

  CRSMatrix C;
  Row_CRS a, b;
  for(unsigned int k = 0; k < this->m; k++)
  {
    a = this->get_row(k);
    b = B.get_row(k);
    C.append(a + b);
  }
  return C;
}

std::ostream& operator<<(std::ostream& os, CRSMatrix& A)
{
  cout << "values = [";
  for(unsigned int i = 0; i < A.values.size(); i++)
    cout << A.values[i] << ", ";
  cout << "]\n";
  cout << "columns = [";
  for(unsigned int i = 0; i < A.columns.size(); i++)
    cout << A.columns[i] << ", ";
  cout << "]\n";
  cout << "rows_index = [";
  for(unsigned int i = 0; i < A.rows_index.size(); i++)
    cout << A.rows_index[i] << ", ";
  cout << "]\n";

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
