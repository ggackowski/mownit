#include <vector>
#include <fstream>

#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

class Interpolation { 

public:

  enum PointsMode {
    Normal, Chebyshev
  };

  Interpolation(std::vector<std::pair<double, double>>);

  static std::vector<std::pair<double, double>> createPoints(
          double (double), double, double, int, PointsMode);
  
  static void fileWrite(std::fstream &, std::vector<std::pair<double, double>>);
  
  std::vector<std::pair<double, double>> getPlotData(double, double, int);
  
  virtual double polyValue(double) = 0;

  double maxDifference(double (*f) (double), double b, double e);


protected:

  std::vector<std::pair<double, double>> points;

  int size;

};

#endif