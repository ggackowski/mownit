#include <ctime>
#include <cstdlib>
#include <cmath>

class PiCalculator {
    public:
        int precision;
        
        PiCalculator(int precision) {
             srand(time(NULL));
             this->precision = precision; 
        };
        
        double getPi() {
            int inCircle = 0;
            for (int i = 0; i < precision; ++i) {
                double x = double(rand()) / RAND_MAX; 
                double y = double(rand()) / RAND_MAX;
                if (std::sqrt(x*x + y*y) <= 1) inCircle++;
            }
            return 4 * double(inCircle) / precision;
        }
        
};