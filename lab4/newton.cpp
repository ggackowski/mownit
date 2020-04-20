#define _USE_MATH_DEFINES
#include "newton.h"
#include <cmath>

Newton::Newton(std::vector<std::pair<double, double>> points, double (*f) (double)) : Interpolation(points) {
  this->f = f;
}

double Newton::polyValue(double x) {
  double p = 0;
  double pi = 1;
  std::vector<std::pair<double, double>> diff;
  for (int i = 0; i < points.size(); ++i) {
    diff.push_back(points[i]);
    double f = dividedDiff(diff);
    p += f * pi;
    pi *= (x - points[i].first);
  }
  return p;
}

double Newton::dividedDiff(std::vector<std::pair<double, double>> v) {

  for (int et = 1; et < v.size(); ++et) {
    for (int i = 1; i <= v.size() - et; ++i) {
        v[i - 1].second = (v[i].second - v[i - 1].second) / (v[i + et - 1].first - v[i - 1].first);
    }
    
  }
  return v[0].second;
}
