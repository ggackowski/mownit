#define _GLIBCXX_USE_CXX11_ABI 0

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

std::vector<std::pair<double, double>>
    getRandomPoints(double begin, double end, double (*f) (double), int n) {
        std::vector<std::pair<double, double>> points;
        for (int i = 0; i < n; ++i) {
            double val = random_n() * (end - begin) + begin;
            points.push_back(std::make_pair(val, f(val)));
        }
        return points;
}

std::vector<std::vector<double>> 
    generateMatrix(std::vector<std::pair<double, double>> points, int m) {
        int n = points.size();
        std::vector<std::vector<double>> matrix(m + 1);
        for (int i = 0; i <= m; ++i) {

            for (int k = 0; k <= m; ++k) {
                double s = 0;
                for (int j = 0; j < n; ++j) 
                    s += std::pow(points[j].first, k + i);

                matrix[i].push_back(s);
            }

            double s = 0;
            for (int j = 0; j < n; ++j) 
                s += points[j].second * std::pow(points[j].first, i);

            matrix[i].push_back(s);
        }      
        return matrix;
    
}

std::vector<double> getCoefficiens(std::vector<std::vector<double>> matrix) {
    int n = matrix.size();
    //std::vector<double> sigmaX(2*degree+1, 0);
    //std::vector<double> sigmaY(degree+1, 0);
    std::vector<double> coefficients(n, 0);
    //double normalMatrix[degree + 1 // n][degree + 2 //n + 1];
    for (int i = 0; i < n - 1; i++)
        for (int k = i + 1; k < n; k++){
            double tmp = matrix[k][i] / matrix[i][i];
            for (int j = 0; j <= n; j++)
                matrix[k][j] -= tmp * matrix[i][j];
        }

    for (int i = n - 1; i >= 0; i--){
        coefficients.at(i) = matrix[i][n];
        for (int j = 0; j < n; j++)
            if (j != i)
                coefficients.at(i) -= matrix[i][j] * coefficients.at(j);
        coefficients.at(i) /= matrix[i][i];
    }

    return coefficients;
}

double value(double x, std::vector<double> coeff) {
    double sum = 0;
    for (int i = 0; i < coeff.size(); ++i) 
        sum += coeff[i] * std::pow(x, i);
    return sum;
}

double error(double (*f) (double), std::vector<double> coeff, std::vector<std::pair<double, double>> pts)  {
    double err = 0;
    for (int i = 0; i < pts.size(); ++i) {
        //std::cout << err << std::endl;
        err += std::pow(value(pts[i].first, coeff) - pts[i].second, 2);
        //std::cout << pts[i].first;
        //std::cout << value(pts[i].first, coeff) << " " << pts[i].second << std::endl;
    }
    return err;
    
}

double error2(double (*f) (double), std::vector<double> coeff, std::vector<std::pair<double, double>> pts)  {
    double err = 0;
    for (double i = pts[0].first; i <= pts[pts.size() - 1].first; i += 2e-6) {
        //std::cout << err << std::endl;
        std::cout << f(i) << " " << value(i, coeff);
        err += std::pow(value(i, coeff) - f(i), 2);
        //std::cout << pts[i].first;
        //std::cout << value(pts[i].first, coeff) << " " << pts[i].second << std::endl;
    }
    return err;

}

void show(std::vector<std::pair<double, double>> pts, int n) {
    auto matrix = generateMatrix(pts, n);
    auto c = getCoefficiens(matrix);
    std::string s = "";
    for (int i = 0; i < c.size(); ++i) {
        s += std::to_string(c[i]);
        s += " ";
    }
    s = "python3 plot.py " + s;
    system(s.c_str());
}

int main() {
    srand(time(NULL));
    int begin = -3;
    int end = 3;
    int pts_size = 40;
    double (*f) (double) = f2;
   
    auto pts = getRandomPoints(begin, end, f, pts_size);
    
    for (int i = 0; i < pts.size(); ++i) {
        std::cout << pts[i].first << " " << pts[i].second << std::endl;
    }

    const int num = 8;
    std::vector<std::vector<double>> matrix[num];
    std::vector<double> coeff[num];
    std::string s = "";

  //  for (int i = 0; i < num; ++i) 
  //      show(pts, i + 3);
       
    
    double min_err = 10000;
    double min = 2;
    for (int i = 2; i  < pts_size; ++i) {
        std::vector<std::vector<double>> m;
        std::vector<double> c;

        m = generateMatrix(pts, i);
        c = getCoefficiens(m);
        auto err = error2(f2, c, pts);
        std::cout << "err " << err << std::endl;

        if (err < min_err) {
            std::cout << "nowe min: " << i << std::endl;
            min = i;
            min_err = err;
        }
        

    }

    std::cout << min << std::endl << std::endl;
    show(pts, min);
    std::cout << error(f2, getCoefficiens(generateMatrix(pts, min)), pts);


    

   // for (int i = 0; i < matrix.size(); ++i) {
   //     for (int j = 0; j < matrix[i].size(); ++j)
   //         std::cout << matrix[i][j] << " ";
   //     std::cout << std::endl;
   // }



    

}