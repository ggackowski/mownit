
#include "integral.cpp"

class SimpsonsIntegration : public Integral {
    public:
     SimpsonsIntegration(int precision) : Integral(precision) {};
     
     double integrate(double begin, double end, std::function<double(double)> f) {
        double s  = 0, st = 0;
        double dx = (end - begin) / precision;
        for(int i = 1; i <= precision; i++) {
            double x = begin + i * dx;
            st += f(x - dx / 2);
            if(i < precision) 
                s += f(x);
        }
        return dx / 6 * (f(begin) + f(end) + 2 * s + 4 * st);
     }

};