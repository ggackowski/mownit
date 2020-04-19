#define _USE_MATH_DEFINES
#include "lagrange.h"
#include <cmath>

Lagrange::Lagrange(std::vector<std::pair<double, double>> points) : Interpolation(points) {
  
}

double Lagrange::phi(int i, double x) {
  double v = 1.;
  for (int k = 0; k < size; ++k) {
    if (i != k)
      v *= (x - points[k].first);
  }
  return v;
}

double Lagrange::a(int i) {
  return points[i].second / phi(i, points[i].first);
}

double Lagrange::polyValue(double x) {
  double v = 0;
  for (int i = 0; i < size; ++i) {
    v += a(i) * phi(i, x);
  }
  return v;
}


