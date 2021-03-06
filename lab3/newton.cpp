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
double a;
double b;

std::pair<int, double> newton(int it, double epsilon) {
    double x = (a + b) / 2;
    int i = 0;
    double xn = INT_MAX;
    do {
        i++;
        xn = x;
        x -= f(x) / df(x);
        

    } while (i < it && dist(xn, x) >= epsilon);
    if (i == it) 
        return std::make_pair(i, -1);
    return std::make_pair(i, x);
}

int main() {
    f = f1;
    a = 3 / 2 * M_PI;
    b = 2 * M_PI;
    auto res = newton(100, 1e-33);
    std::cout << res.first << " " << res.second << std::endl;
    f = f2;
    a = 0;
    b = M_PI / 2;
    res = newton(100, 1e-33);
    std::cout << res.first << " " << res.second << std::endl;
    f = f3;
    a = 1;
    b = 3;
    res = newton(100, 1e-33);
    std::cout << res.first << " " << res.second << std::endl;
}