#include "aghMatrix.h"
#include <unistd.h>
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
    std::vector<std::vector<double>> init3 { { 5, 3, 2 }, 
                                             { 1, 2, 0 },
                                             { 3, 0, 4 }
                                             }; 
     std::vector<std::vector<double>> init4 { { 4, 12, -16 }, 
                                             { 12, 37, -43 },
                                             { -16, -43, 98 }
                                             }; 
    AGHMatrix<double> mat4(init1);
    AGHMatrix<double> mat5(init2);
    AGHMatrix<double> mat6(init3);
    AGHMatrix<double> mat7(init4);
    AGHMatrix<double> mat8(init1);
    std::cout << mat4 << std::endl;
    std::cout << mat5 << std::endl;
    std::cout << mat4 * mat5 << std::endl;
    std::cout << mat6.det();
    std::cout << mat4.transpose();
    std::cout << "\n\n";
    auto lu = mat6.LU();
    std::cout << lu.first << std::endl << lu.second << std::endl;
    std::cout << mat7.Cholesky() << std::endl;
    auto res = mat8.Jacobi(500);
    for (int i = 0; i < res.size(); ++i)
      std::cout << "x[" << i << "] = " << res[i] << std::endl; 
    std::cout << mat7.gauss();
    return 0;
}