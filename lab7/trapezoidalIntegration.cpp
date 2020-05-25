#include "integral.cpp"

class TrapezoidalIntegration : public Integral {
    public:
     TrapezoidalIntegration(int precision) : Integral(precision) {};
     
     double integrate(double begin, double end, std::function<double(double)> f) {
        double dx = (end - begin) / precision;
        double part = (f(begin) + f(end)) / 2;
        double sum = part;
        for (int i = 1; i < precision; ++i) 
            sum += f(begin + i*dx);
        sum *= dx;
        return sum; 
     }

};