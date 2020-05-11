#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "lagrange.h"
#include "newton.h"

const double k = 2;
const double m = 3;

double f1(double x) {
  return std::sin(k * x / M_PI) * std::exp(-m * x / M_PI);
}

double f2(double x) {
  return std::exp(k * std::cos(m * x));
}


int main() {

  std::fstream f, g;

  f.open("dataL.txt", std::ios::out);
  g.open("dataN.txt", std::ios::out);


  Newton * newton = new Newton(Newton::createPoints(f2, -4.0, 4.0, 10, Newton::PointsMode::Chebyshev), f2);
  //std::cout << std::endl << newton->polyValue(4);
  Newton::fileWrite(g, newton->getPlotData(-4, 4, 500) );

  Lagrange * lagrange = new Lagrange(Lagrange::createPoints(f2, -4.0, 4.0, 10, Lagrange::PointsMode::Chebyshev));
  //std::cout << lagrange->polyValue(4);
  Lagrange::fileWrite(f, lagrange->getPlotData(-4, 4, 500) );


  
  
  

}


