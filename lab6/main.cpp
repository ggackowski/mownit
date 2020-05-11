#include "aghMatrix.h"
#include <unistd.h>
#include <iostream>



int main() 
{
    std::vector<std::vector<double>> v1 = {{2, 1, 11},
                                            {5, 7, 13},
                                          };
    
    std::vector<std::vector<double>> v2 = {{10, -1, 2, 0, 6},
                                           {-1, 11, -1, 3, 25},
                                           {2, -1, 10, -1, -11},
                                           {0, 3, -1, 8, 15}};
    
    AGHMatrix<double> mat8(v2);

    //std::cout << mat8.gauss();
    int n = 10;
    auto res = mat8.Jacobi(n);
    std::cout << std::endl;
    auto res2 = mat8.GaussSeidel(n);
    auto res3 = mat8.SOR(n, 0.5);
    for (int i = 0; i < res.size(); ++i)
      std::cout << "x[" << i << "] = " << res[i] << "||" << res2[i] << "||" << res3[i] << std::endl; 
    return 0;
}