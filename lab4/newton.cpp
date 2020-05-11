#define _USE_MATH_DEFINES
#include "newton.h"
#include <cmath>

Newton::Newton(std::vector<std::pair<double, double>> points, double (*f) (double)) : Interpolation(points) {
  this->f = f;
}

double Newton::polyValue(double x) {
  double p = 0;
  double pi = 1;
  std::vector<double> diff;
  for (int i = 0; i < points.size(); ++i) {
    diff.push_back(points[i].first);
    double f = dividedDiff(diff);
    p += f * pi;
    pi *= (x - points[i].first);
  }
  return p;
}

double Newton::dividedDiff(std::vector<double> v) {
  double a;
  double sum = 0;
  for (int j = 0; j < v.size(); ++j) {
    a = f(v[j]);
    double denominator = 1;
    for (int k = 0; k < v.size(); ++k)
      if (k != j) 
        denominator *= (v[j] - v[k]); 
    a /= denominator;
    sum += a;
  }
  return sum;
}
