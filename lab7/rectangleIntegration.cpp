
#include "integral.cpp"

class RectangleIntegration : public Integral {
    public:
     RectangleIntegration(int precision) : Integral(precision) {};
     
     double integrate(double begin, double end, std::function<double(double)> f) {
        double dx = (end - begin) / precision;
        double sum = 0;
        for (int i = 1; i <= precision; ++i) 
            sum += f(begin + i * dx);
        sum *= dx;
        return sum; 
     }

};