#ifndef _HERMITE_H_
#define _HERMITE_H_
#include "newton.h"

class Hermite : public Newton {
  public:
    Hermite(std::vector<std::pair<double, double>> points, double (*f) (double), double (*df) (double)) : Newton(points, f)
    {  this->df = df; }

    static std::vector<std::pair<double, double>> createPoints(
        double (double), double (double), double, double, int, PointsMode);
  
    
    double polyValue(double x);

    private:
      double (*df) (double);
      double dividedDiff(std::vector<std::pair<double, double>>);
};


#endif