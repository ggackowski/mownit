#include <vector>
#include <fstream>
#include "interpolation.h"

#ifndef _NEWTON_H_
#define _NEWTON_H_



class Newton : public Interpolation {
  

public:

  Newton(std::vector<std::pair<double, double>>, double (*) (double));
  
  double polyValue(double);


private:

  double (*f) (double);
  double dividedDiff(std::vector<std::pair<double, double>>);
  

};

#endif