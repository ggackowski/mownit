#define _USE_MATH_DEFINES
#include "interpolation.h"
#include <cmath>

Interpolation::Interpolation(std::vector<std::pair<double, double>> points) {
  this->points = points;
  size = points.size();
}

std::vector<std::pair<double, double>> Interpolation::createPoints
      (double (*f) (double), double begin, double end, int n, Interpolation::PointsMode p) {
        
        std::vector<std::pair<double, double>> result;
        
        switch (p) {
          
          case PointsMode::Normal:
          { 
            double delta = (end - begin) / n;
            for (int i = 0; i < n + 1; ++i) 
              result.push_back(std::make_pair(begin + i * delta, f(begin + i * delta)));
            break;
          }
          case PointsMode::Chebyshev:
          {
            for (int i = 0; i < n + 1; ++i) {
              double value = std::cos(   (2. * i + 1) / (n + 1.) * M_PI / 2.   );
              double denormalizedValue = (end - begin) / 2 * value + (begin + end) / 2;
              result.push_back(std::make_pair(denormalizedValue, f(denormalizedValue)));
            }
            break;
          }
        }
        
        return result;
        
}

void Interpolation::fileWrite(std::fstream & f, std::vector<std::pair<double, double>> data) {
  for (auto i = 0; i < data.size(); ++i) {
    f << data[i].first << " " << data[i].second << std::endl;
  }
}

std::vector<std::pair<double, double>> Interpolation::getPlotData(double begin, double end, int n) {
  double delta = (end - begin) / n;
        std::vector<std::pair<double, double>> result;
        for (int i = 0; i < n; ++i) 
          result.push_back(std::make_pair(begin + i * delta, polyValue(begin + i * delta)));
        return result;
}

double Interpolation::maxDifference(double (*f) (double), double b, double e) {
  double diff = 0;
  int cnt = 0;
  for (double i = b; i <= e; i += 0.015625) {
    cnt++;
    double dist = std::abs(f(i) - polyValue(i));
    diff += dist;
  }
  return diff / cnt;
}