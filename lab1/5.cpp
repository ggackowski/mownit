#include <iostream>
#include <cmath>

int main() {
  float a, b, c;
  a = 0.1e1;
  b = -0.2e11;
  c = 0.2e01;
  std::cout << a << " " << b << " " << c << std::endl;
  float delta = b * b - 4 * a * c;
  float res1 = (-b + sqrt(delta)) / (2 * a);
  float res2 = (-b - sqrt(delta)) / (2 * a);
  std::cout << res1 << " " << res2 << std::endl;
}
