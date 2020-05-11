#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


const double k = 2;
const double m = 3;

double f1(double x) {
  return std::sin(k * x / M_PI) * std::exp(-m * x / M_PI);
}

double f2(double x) {
  return std::exp(k * std::cos(m * x));
}

double df2(double x) {
  
}


int main() {

  std::fstream f, g;

  f.open("dataL.txt", std::ios::out);
  g.open("dataN.txt", std::ios::out);


  
  
  

}
