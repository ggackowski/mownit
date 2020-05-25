#pragma once
#include <functional>

class Integral {
    public:
     int precision;
     Integral(int precision) {this->precision = precision; };
     void setPrecision(int precision) { this->precision = precision; }    
     virtual double integrate(double, double, std::function<double(double)>) = 0;
};