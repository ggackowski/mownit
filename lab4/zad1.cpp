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

  double begin = -4.;
  double end = 4.;
  double points = 24;
  auto type = Interpolation::PointsMode::Normal;

  //Interpolation * interpolation1 = new Newton(Interpolation::createPoints(f2, begin, end, points, type), f2);
  //Interpolation::fileWrite(g, interpolation1->getPlotData(begin,  end, 500) );

  Interpolation * interpolation2 = new Lagrange(Interpolation::createPoints(f2, begin, end, points, type));
  Interpolation::fileWrite(f, interpolation2->getPlotData(begin, end, 500) );

  std::cout << "blad: " << interpolation2->maxDifference(f2, -4., 4.) << std::endl;
  //for (int i = 2; i <= 40; ++i) {
  //  Interpolation * interpolation2 = new Lagrange(Interpolation::createPoints(f2, begin, end, i, type));
  //  std::cout << interpolation2->maxDifference(f2, begin, end) << std::endl;
  //}
}


