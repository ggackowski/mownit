#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cmath>
#include "hermite.h"


const double k = 2;
const double m = 3;

double f1(double x) {
  return std::sin(k * x / M_PI) * std::exp(-m * x / M_PI);
}

double f2(double x) {
  return std::exp(k * std::cos(m * x));
}

double df2(double x) {
  return -k * m * std::exp(k * std::cos(m*x))*sin(m * x);
}


int main() {

  std::cout << df2(3);

  std::fstream f;

  f.open("dataH.txt", std::ios::out);

  Hermite * hermite = new Hermite(Hermite::createPoints(f2, df2, -4, 4, 12, Interpolation::PointsMode::Normal), f2, df2);
  Interpolation::fileWrite(f, hermite->getPlotData(-4, 4, 500));
  




  
  
  

}
