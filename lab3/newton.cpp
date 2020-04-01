#include <iostream>
#include <limits.h>
#include <cmath>

double f1(double x) {
    return std::cos(x) * std::cosh(x) - 1;
}

double f2(double x) {
    return 1 / x - std::tan(x);
}

double f3(double x) {
    return std::pow(2, -x) + std::exp(x) + 2 * std::cos(x) - 6;
}

double (*f) (double);

double df(double x) {
    double h = 1e-7;
    return ((f(x + h) - f(x - h)) / (2 * h));
}

double dist(double a, double b) {
    return std::abs(a - b);
}

double newton(int it, double epsilon) {
    double x = 1;
    int i = 0;
    double xn = INT_MAX;
    do {
        i++;
        xn = x;
        x -= f(x) / df(x);
        

    } while (i < it && dist(xn, x) >= epsilon);
    return x;
}

int main() {
    f = f1;
    std::cout << newton(10, 1e-7) << std::endl;
    f = f2;
    std::cout << newton(10, 1e-7) << std::endl;
    f = f3;
    std::cout << newton(10, 1e-7) << std::endl;


}