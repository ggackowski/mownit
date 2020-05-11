#include "aghMatrix.h"
#include <unistd.h>
#include <iostream>


double diff(std::vector<double> res, std::vector<double>v) {
  double d = 0;
  for (int i = 0; i < v.size(); ++i) {
    d += fabs(res[i] - v[i]);
  }
  return d;
}


int main() 
{
    std::vector<std::vector<double>> v1 = {
                                           {4, 1, -1, 3},
                                           {2, 7, 1, 19},
                                           {1, -3, 12, 31}
                                          };
    
    std::vector<std::vector<double>> v2 = {{10, -1, 2, 0, 6},
                                           {-1, 11, -1, 3, 25},
                                           {2, -1, 10, -1, -11},
                                           {0, 3, -1, 8, 15}};
    
    std::vector<std::vector<double>> v3 = {{5, -2, 3, -1},
                                           {-3, 9, 1, 2},
                                           {2, -1, -7, 3}
                                           
                                           };

    std::vector<std::vector<double>> v4 = {
                                           {3, -1, -4},
                                           {2, 5, 2},
                                          };

    std::vector<std::vector<double>> v5 = {
                                           {4, 2, -1, -1},
                                           {3, -5, 1, 3},
                                           {1, 0, 2, -4}
                                          };

    std::vector<std::vector<double>> v6 = {
                                           {7, -1, 6},
                                           {1, -5, -4},
                                          };
    AGHMatrix<double> mat8(v2);

    //std::cout << mat8.gauss();
    int n = 50;
    auto res = mat8.Jacobi(n);
    std::cout << std::endl;
    auto res2 = mat8.GaussSeidel(n);
    auto res3 = mat8.SOR(n, 0.5);
    
    auto dc = mat8.GaussSeidel(100);
    for (int i = 1; i < 20; ++i) {
      auto r = mat8.SOR(i, 1.5);
      std::cout << diff(r, dc) << std::endl;
    }
    
    return 0;
}