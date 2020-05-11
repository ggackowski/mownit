#include "aghMatrix.h"
#include <unistd.h>

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) 
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++) 
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) 
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const 
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const 
{
  return this->cols;
}



// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) 
{
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) 
  {
    for (unsigned j=0; j<new_cols; j++) 
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
  return this->matrix[row][col];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) 
{
   AGHMatrix<T> newMatrix(this->rows, rhs.cols, 0);
   std::cout << this->rows << " " << rhs.cols << std::endl;
    for (auto i = 0; i < this->matrix.size(); ++i)
        for (auto j = 0; j < this->matrix[i].size(); ++j)
            newMatrix.matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
    return newMatrix;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) 
{
   AGHMatrix<T> newMatrix(this->rows, rhs.cols, 0);
  
    for (auto i = 0; i < this->matrix.size(); ++i)
        for (auto j = 0; j < this->matrix[i].size(); ++j) 
          for (auto k = 0; k < this->cols; ++k)
            newMatrix.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
 
    return newMatrix;
}

// Printing matrix                                                                                                                        
template<typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) 
{
  for (int i=0; i<matrix.get_rows(); i++) 
  { 
    for (int j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
    stream << std::endl;
}

template <typename T>
bool AGHMatrix<T>::isSymetric() {
    if (cols != rows) return false;
    for (auto i = 0; i < matrix.size(); ++i) 
        for (auto j = 0; j < matrix[i].size(); ++j)
            if (matrix[i][j] != matrix[j][i])
                return false;
    return true;
}
template <typename T>
T AGHMatrix<T>::det() {
  if (rows != cols) return -1;
  return _det(rows, cols, matrix);
}

template <typename T>
AGHMatrix<T> AGHMatrix<T>::transpose() {
  AGHMatrix<T> newMatrix(this->cols, this->rows, 0);
  for (auto i = 0; i < this->rows; ++i)
    for (auto j = 0; j < this->cols; ++j) 
      newMatrix.matrix[j][i] = this->matrix[i][j];

  return newMatrix;
}

template <typename T>
std::pair<AGHMatrix<T>, AGHMatrix<T>> AGHMatrix<T>::LU() {
  AGHMatrix<T> L(rows, cols, 0);
  AGHMatrix<T> U(rows, cols, 0);
  for (int i = 0; i < cols; ++i)
    L.matrix[i][i] = 1;

  for (int i = 0; i < cols; ++i) {
    for (int j = i; j < rows; ++j) {
      T sum1 = 0;
      U.matrix[i][j] = matrix[i][j];
      for (int k = 0; k <= i - 1; ++k)
        sum1 += L.matrix[i][k] * U.matrix[k][j];
      U.matrix[i][j] -= sum1;
    }
    for (int j = i + 1; j < rows; ++j) {
        T sum2 = 0;
        L.matrix[j][i] = 1.0 / U.matrix[i][i];
        for (int k = 0; k <= i - 1; ++k)
            sum2 += L.matrix[j][k] * U.matrix[k][i];
        L.matrix[j][i] *= (matrix[j][i] - sum2);
    }
  }
  return std::make_pair(L, U);
}

template <typename T>
std::vector<T> AGHMatrix<T>::Jacobi(int iterations) {
  std::vector<T> res(rows);
  std::vector<T> res_old(rows);
  for (int i = 0; i < rows; ++i) {
    res_old[i] = 0;
  }
  for (int it = 0; it < iterations; ++it) {
    for (int w = 0; w < rows; ++w) {
      T sum = 0;
      for (int j = 0; j < rows; ++j) 
        if (w != j) {
          sum += matrix[w][j] * res_old[j];
        }
      for (int i = 0; i < rows; ++i) res_old[i] = res[i];
      res[w] = T(matrix[w][cols - 1] - sum) / matrix[w][w];
    }
  }
  return res;
}


template <typename T>
std::vector<T> AGHMatrix<T>::GaussSeidel(int iterations) {
  std::vector<T> res(rows);
  std::vector<T> res_old(rows);
  for (int i = 0; i < rows; ++i) {
    res_old[i] = 0;
  }
  for (int it = 0; it < iterations; ++it) {
    for (int w = 0; w < rows; ++w) {
      T sum = 0;
      T sum2 = 0;
      //res_old[w] = res[w];
      for (int j = w + 1; j < rows; ++j) 
        sum += matrix[w][j] * res_old[j];
    
      for (int j = 0; j < w; ++j) {
        sum += matrix[w][j] * res[j];
      }
        //std::cout << "sum: " << sum << std::endl;
      for (int i = 0; i < rows; ++i) res_old[i] = res[i];
      res[w] = T(matrix[w][cols - 1] - sum - sum2) / matrix[w][w];
     // std::cout << cols;
     // std::cout << matrix[0][3] << std::endl;
    }
  }
  return res;
}

template <typename T>
std::vector<T> AGHMatrix<T>::SOR(int iterations, double v) {
  std::vector<T> res(rows);
  std::vector<T> res_old(rows);
  for (int i = 0; i < rows; ++i) {
    res_old[i] = 0;
  }
  for (int it = 0; it < iterations; ++it) {
    for (int w = 0; w < rows; ++w) {
      T sum = 0;
      T sum2 = 0;
      //res_old[w] = res[w];
      for (int j = w + 1; j < rows; ++j) 
        sum += matrix[w][j] * res_old[j];
    
      for (int j = 0; j < w; ++j) {
        sum += matrix[w][j] * res[j];
      }
        //std::cout << "sum: " << sum << std::endl;
      for (int i = 0; i < rows; ++i) res_old[i] = res[i];
      res[w] = (1. - v) * res_old[w] + v * (matrix[w][cols - 1] - sum - sum2) / matrix[w][w];
     // std::cout << cols;
     // std::cout << matrix[0][3] << std::endl;
    }
  }
  return res;
}



template <typename T>
AGHMatrix<T> AGHMatrix<T>::gauss() {
  AGHMatrix<T> newmatrix(*this);
  for (int k = 0; k < rows - 1; ++k) {
    T pivot = newmatrix.matrix[k][k];
    
    for (int i = k + 1; i < rows; ++i) {
      T factor = newmatrix.matrix[i][k] / pivot;
      for (int j = 0; j < cols; ++j) {
        newmatrix.matrix[i][j] -= factor * newmatrix.matrix[k][j];
      }
    }
  }
  return newmatrix;
}

template <typename T>
AGHMatrix<T> AGHMatrix<T>::Cholesky() {
  AGHMatrix<T> L(rows, cols, 0);

for (int i = 0; i < rows; ++i) {
  for (int j = i; j < cols; ++j) {

    if (i != j) {
      T sum = 0;
      for (int k = 0; k < i; ++k) 
        sum += L.matrix[j][k] * L.matrix[i][k];
    
      L.matrix[j][i] = (matrix[j][i] - sum) / L.matrix[i][i];
    }

    else {
      T sum = 0;
    
      for (int k = 0; k < i; k++)
        sum += L.matrix[i][k] * L.matrix[i][k];

      L.matrix[i][i] = std::sqrt(matrix[i][i] - sum);
    }
  }
}
return L;
}

template  <typename T>
T _det(int rows, int cols, std::vector<std::vector<T>> matrix) {
  T det = 0;
  if (rows == 1) return matrix[0][0];
  else {
    for (int i = 0; i < rows; ++i) {
        std::vector<std::vector<T>> tmp;
          for (int k = 0; k < rows; ++k) {
            if (k != i)
              tmp.push_back(std::vector<T>());
            for (int l = 0; l < cols; ++l) {
              if (k != i && l != 0) {
                tmp[tmp.size() - 1].push_back(matrix[k][l]);
              }
            }
          }
       if (i % 2 == 0)
        det +=  matrix[i][0] * _det(rows - 1, cols - 1, tmp);
      else
        det -=  matrix[i][0] * _det(rows - 1, cols - 1, tmp);
    }
    return det;
  }
}
