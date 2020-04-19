#include <vector>
#include <fstream>
#include "interpolation.h"

#ifndef _LAGRANGE_H_
#define _LaGRANGE_H_



class Lagrange : public Interpolation {
  

public:

  Lagrange(std::vector<std::pair<double, double>>);

  double polyValue(double);


private:

  double phi(int, double);

  double a(int);
  
};

#endif