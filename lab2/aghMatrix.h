#pragma once 

#include <vector>
#include <iostream>
#include <cmath>

template <typename T> class AGHMatrix 
{
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;

public:
    AGHMatrix(const std::vector<std::vector<T>>& matrix);
    AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    AGHMatrix(const AGHMatrix<T>& rhs);
    virtual ~AGHMatrix() = default;

    // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
    AGHMatrix<T>& operator=(const AGHMatrix<T>& rhs);

    // Matrix mathematical operations                                                                                                                                                                                               
    AGHMatrix<T> operator+(const AGHMatrix<T>& rhs);
    AGHMatrix<T> operator*(const AGHMatrix<T>& rhs);

    // Access the individual elements                                                                                                                                                                                               
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;
    
    // Printing matrix
    std::ostream& operator<<(const AGHMatrix<T>& matrix);

    std::pair<AGHMatrix<T>, AGHMatrix<T>> LU();
    AGHMatrix<T> Cholesky();

    AGHMatrix<T> transpose();

    std::vector<T> Jacobi(int);
    // Access the row and column sizes                                                                                                                                                                                              
    unsigned get_rows() const;
    unsigned get_cols() const;
    bool isSymetric();
    AGHMatrix<T> gauss();
    T det();

};

template <typename T>
T _det(int cols, int rows, std::vector<std::vector<T>> matrix);

#include "aghMatrix.cpp"
