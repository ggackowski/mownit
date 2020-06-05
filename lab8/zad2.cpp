#include <iostream>
#include <complex>
#include <vector>
#include <sys/times.h>
#include <unistd.h>

class DFT {
    public:
        DFT(std::vector<std::complex<double>> inpt) {
            input = inpt;
        }

        std::vector<std::complex<double>> get() {
            std::vector<std::complex<double>> result(input.size());
            for (int i = 0; i < input.size(); ++i) {
                result[i] = 0;
                for (int j = 0; j < input.size(); ++j) {
                    result[i] += input[j] * std::complex<double>((cos((-2.0 * M_PI)/input.size() * i * j)), (sin((-2. * M_PI) / input.size() * i * j)));
                }

            }
            return result;
        }

    private:
        std::vector<std::complex<double>> input;
};

class FFT {
    public:
        FFT(std::vector<std::complex<double>> inpt) {
            input = inpt;
        }

        void _get(std::vector<std::complex<double>> & x) {
            if (x.size() <= 4) {
                DFT * dft = new DFT(x);
                x = dft->get();
            }
            else {
                std::vector<std::complex<double>> odd;
                std::vector<std::complex<double>> even;
                for (int i = 0; i < x.size(); ++i) {
                    if (!(i % 2))
                        even.push_back(x[i]);
                    else
                        odd.push_back(x[i]);
                }
                _get(even);
                _get(odd);
                for (int i = 0; i < x.size() / 2; ++i) {
                   std::complex<double> factor = 
                                std::complex<double>(cos((-2.0 * M_PI * i) / x.size()), 
                                sin((-2.0 * M_PI * i) / x.size())) * odd[i];
                   x[i] = even[i] + factor;
                   x[i + (x.size() / 2)] = even[i] - factor;
                }

            }
        }

        std::vector<std::complex<double>> get() {
            _get(input);
            return input;
        }

    private:
        std::vector<std::complex<double>> input;
};

double tm(int begin, int end) {
    return double(end - begin) / sysconf(_SC_CLK_TCK);
}


int main() {


    for (int n = 32; n < 10000; n *= 2) {
        std::cout << "rozmiar " << n << std::endl;
        std::vector<std::complex<double>> input(n);
        for (int i = 0; i < n; ++i)
            input[i] = std::complex<double>(rand() % 1000 - 500, rand() % 1000 - 500);
        FFT * fft = new FFT(input);
        DFT * dft = new DFT(input);
        int begin = times(NULL);
        auto output = fft->get();
        int end = times(NULL);
        std::cout << tm(begin, end);
        begin = times(NULL);
        output = dft->get();
        end = times(NULL);
        std::cout << std::endl << tm(begin, end);
        std::cout << std::endl;

    }

    std::cout << "A\n";
    std::vector<std::complex<double>> input(100000);
    
    for (int i = 0; i < 100000; ++i)
            input[i] = std::complex<double>(rand() % 1000 - 500, rand() % 1000 - 500);

    FFT * fft = new FFT(input);

    int begin = times(NULL);
    auto output = fft->get();
    int end = times(NULL);
    std::cout << tm(begin, end);    

    return 0;
}