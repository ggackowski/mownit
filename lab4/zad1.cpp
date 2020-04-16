#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

const double k = 2;
const double m = 3;

double f1(double x) {
  return std::sin(k * x / M_PI) * std::exp(-m * x / M_PI);
}

double f2(double x) {
  return std::exp(k * std::cos(m * x));
}

class Lagrange {
  

public:

  static std::vector<std::pair<double, double>> createPoints(
          double (double), double, double, int);

  static void fileWrite(std::fstream &, std::vector<std::pair<double, double>>);
  
  Lagrange(std::vector<std::pair<double, double>>);
  double polyValue(double);
  std::vector<std::pair<double, double>> getPlotData(double, double, int);

private:

  std::vector<std::pair<double, double>> points;

  int size;

  double phi(int, double);
  double a(int);
  

};


int main() {
  std::fstream f;
  f.open("data.txt", std::ios::out);
 
  Lagrange * lagrange = new Lagrange(Lagrange::createPoints(f2, -4.0, 4.0, 8));
  std::cout << lagrange->polyValue(4);
  Lagrange::fileWrite(f, lagrange->getPlotData(-4, 4, 500) );
  

}











Lagrange::Lagrange(std::vector<std::pair<double, double>> points) {
  this->points = points;
  size = points.size();
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

std::vector<std::pair<double, double>> Lagrange::createPoints
      (double (*f) (double), double begin, double end, int n) {
        double delta = (end - begin) / n;
        std::vector<std::pair<double, double>> result;
        for (int i = 0; i < n + 1; ++i) 
          result.push_back(std::make_pair(begin + i * delta, f(begin + i * delta)));
        return result;
}

void Lagrange::fileWrite(std::fstream & f, std::vector<std::pair<double, double>> data) {
  for (auto i = 0; i < data.size(); ++i) {
    f << data[i].first << " " << data[i].second << std::endl;
  }
}

std::vector<std::pair<double, double>> Lagrange::getPlotData(double begin, double end, int n) {
  double delta = (end - begin) / n;
        std::vector<std::pair<double, double>> result;
        for (int i = 0; i < n; ++i) 
          result.push_back(std::make_pair(begin + i * delta, polyValue(begin + i * delta)));
        return result;
}


