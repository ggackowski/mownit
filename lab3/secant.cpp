#include <iostream>
#include <math.h>


double f1(double x) {
    return std::cos(x) * std::cosh(x) - 1;
}

double f2(double x) {
    return 1 / x - std::tan(x);
}
double f3(double x) {
    return std::pow(2, -x) + std::exp(x) + 2 * std::cos(x) - 6;
}

double a, b;
double (*f) (double);


std::pair<double, int> secant(double epsilon, int it){
    double x0 = a;
    double x1 = b;
    int i = 0;
    while(abs(f(x1)) > epsilon && i < it){
        double t = x1;
        x1 = (f(x1) * x0 - f(x0) * x1) / (f(x1) - f(x0));
        x0 = t;
        i++;
    }
    return std::make_pair(x1, i);
}

int main() {
        f = f1;
        a = 1.5 * M_PI;
        b = 2 * M_PI;
    	auto aa = secant(1e-06, 100);
        std::cout << aa.first << " " << aa.second << std::endl;

        f = f2;
        a = 0.01;
        b = M_PI / 2.;
    	aa = secant(1e-06, 100);
        std::cout << aa.first << " " << aa.second << std::endl;

        f = f3;
        a = 1;
        b = 3;
    	aa = secant(1e-06, 100);
        std::cout << aa.first << " " << aa.second << std::endl;
}