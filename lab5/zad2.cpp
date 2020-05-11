#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <vector>

const double k = 1;
const double m = 2;

double f1(double x) {
    return std::sin(k * x / M_PI) * exp(-m * x / M_PI);
}

double f2(double x) {
    return std::exp(k * cos(m * x));
}

double f3(double x) {
    return std::sin(m * x) * std::exp(-m * x / M_PI);
}

double f4(double x) {
    return x * x - m * cos(M_PI * x / k);
}

double random_n() {
    return rand() / double(RAND_MAX);
}

std::vector<std::pair<double, double>> points;
double (*f) (double);
int n;


std::vector<std::pair<double, double>>
    getPoints() {
        std::vector<std::pair<double, double>> points;
        for (int i = 0; i < n; ++i) {
            double val = double(i * 2* M_PI) / n;
            points.push_back(std::make_pair(val, f(val)));
        }
        return points;
    }

double getA(int j) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += points[i].second * cos(j * points[i].first);
    }

    return 2 * sum / n;
}

double getB(int j) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += points[i].second * sin(j * points[i].first);
    }

    return 2 * sum / n;
}



void print(int k) {
    std::cout << getA(0) / 2 << " ";
    for (int j = 1; j <= k; ++j) {
        std::cout << "+ " << getA(j) << " * cos(" << j << "* x) + " << getB(j) << "* sin(" << j << "* x)"; 
    }
}

double value(int k, double x) {
    double v = 0;
    v += getA(0) / 2;
    for (int j = 0; j <= k; ++j) {
        v += getA(j) * std::cos(j * x) + getB(j) * std::sin(j * x);
    }
    return v;
}

double error2(int k)  {
    double err = 0;
    for (double i = 0; i <= points.size(); i++) {
        double p = std::pow(value(k, points[i].first) - points[i].second, 2);
        err += p;
    }
    return err;

}

double error3(int k)  {
    double err = 0;
    for (double i = 0; i <= 2 * M_PI; i += 2e-3) {
        double p = std::pow(value(k, i) - f(i), 2);
        err += p;
    }
    return err;

}




int main() {
    
    f = f4;
    n = 25;
    double a = 0.251327;
    std::vector<std::pair<double, double>> pts = {{0*a, 0.1}, {1*a, 0.4}, {2*a, 0.8}, {3*a, 0.9}, {4*a, 1.4}, {5*a, 2.1}, {6*a, 2.0}, {7*a, 1.8}, {8*a, 1.2}, {9*a, 0.8}, {10*a, 0.4}, {11*a, 0}, {12*a, -0.3}, {13*a, -0.9}, {14*a, -1.5}, {15*a, -2.5}, {16*a, -3.1}, {17*a, -3.9}, {18*a, -2.9}, {19*a, -2.1}, {20*a, -1.5}, {21*a, -0.8}, {22*a, -0.1}, {23*a, 0.4}, {24*a, 0.9}}; 
    points = pts;
    for (int i = 0; i < points.size(); ++i) {
        std::cout << points[i].first << " " << points[i].second << std::endl;
    }

    print(3);
    /*
    int min_st = 1;
    double min_err = 10000000;
    for (int i = 0; i < n; ++i) {
        auto err = error3(i);
        if (err < min_err) {
            min_err = err;
            min_st = i;
        }
    }

    print(min_st);
    std::cout << std::endl << min_err << std::endl;
    */
}