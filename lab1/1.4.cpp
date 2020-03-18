#include <cmath>
#include <iostream> 
#include <vector> 

float rec_sum(std::vector<float> & v, unsigned begin, unsigned end) {
    if (end - begin == 0) return v[begin];
    if (end - begin == 1) return v[end] + v[begin];
    unsigned div = (end + begin) / 2;
    return rec_sum(v, begin, div) + rec_sum(v, div + 1, end);
}
