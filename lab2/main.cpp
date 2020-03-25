#include "aghMatrix.h"
#include <iostream>


int main() 
{
    // initialize matrices using init value
    AGHMatrix<double> mat1(5, 5, 1.2);
    AGHMatrix<double> mat2(5, 5, 2.8);

    // Uncomment when implemented
     AGHMatrix<double> mat3 = mat1 * mat2;
     std::cout << mat3;

   //  initialize matrix using specified values
    std::vector<std::vector<double>> init1 { { 1.0, 1.0, 1.0 }, 
                                            { 1.0, 1.0, 1.0 } 
                                             }; 

    std::vector<std::vector<double>> init2 { { 1.0, 1.0 }, 
                                            { 1, 1.0},
                                             {1, 1}}; 
    std::vector<std::vector<double>> init3 { { 1.0, 2.0 }, 
                                            { 3, 1.0},
                                             }; 
    AGHMatrix<double> mat4(init1);
    AGHMatrix<double> mat5(init2);
    AGHMatrix<double> mat6(init3);
    std::cout << mat4 << std::endl;
    std::cout << mat5 << std::endl;
    std::cout << mat4 * mat5 << std::endl;
    std::cout << mat6.isSymetric();
    return 0;
}