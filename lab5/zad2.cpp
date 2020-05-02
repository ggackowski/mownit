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





int main() {

    f = f3;
    n = 50;
    points = getPoints();

    print(5);
}