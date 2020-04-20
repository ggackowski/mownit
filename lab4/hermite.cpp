#define _USE_MATH_DEFINES
#include "hermite.h"
#include <math.h>


std::vector<std::pair<double, double>> Hermite::createPoints
      (double (*f) (double), double (*df) (double), double begin, double end, int n, Interpolation::PointsMode p) {
        
        std::vector<std::pair<double, double>> result;
        
        switch (p) {
          
          case PointsMode::Normal:
          { 
            double delta = (end - begin) / n;
            
            for (int i = 0; i < n + 1; ++i) {
              result.push_back(std::make_pair(begin + i * delta, f(begin + i * delta)));
              result.push_back(std::make_pair(begin + i * delta, df(begin + i * delta)));
            }
            break;
          }
          case PointsMode::Chebyshev:
          {
              for (int i = 0; i < n + 1; ++i) {
              double value = std::cos(   (2. * i + 1) / (n + 1.) * M_PI / 2.   );
              double denormalizedValue = (end - begin) / 2 * value + (begin + end) / 2;
              result.push_back(std::make_pair(denormalizedValue, f(denormalizedValue)));
              result.push_back(std::make_pair(denormalizedValue, df(denormalizedValue)));
            }

            break;
          }
        }
        
        return result;
        
}

double Hermite::polyValue(double x) {
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

double Hermite::dividedDiff(std::vector<std::pair<double, double>> v) {
  for (int et = 1; et < v.size(); ++et) {
    for (int i = 1; i <= v.size() - et; ++i) {
      if (v[i + et - 1].first - v[i - 1].first == 0)
        v[i - 1].second = df(v[i - 1].first);
      else
        v[i - 1].second = (v[i].second - v[i - 1].second) / (v[i + et - 1].first - v[i - 1].first);
    }
    
  }
  return v[0].second;
}
