
#include "integral.cpp"
#include <cmath>
#include <ctime>
#include <cstdlib>

class MonteCarloIntegration : public Integral {
    private:
    double upperBound = 1000;
    double drand(double min, double max) {
        double scale = double(rand()) / RAND_MAX; 
        return min + scale * (max - min);  
    }

    public:
     MonteCarloIntegration(int precision) : Integral(precision) { srand(time(NULL)); };
     void setUpperBound(double up) {
         upperBound = up;
     }
     double integrate(double begin, double end, std::function<double(double)> f) {
         int up = 0;
         int down = 0;
         for (int i = 0; i < precision; ++i) {
            double x = drand(begin, end);
            double y = drand(0, upperBound);
            if (y <= f(x)) down++; else up++;
         }
         return double(down) / precision * upperBound * (end - begin);
     }

};