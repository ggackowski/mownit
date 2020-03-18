
#include <cmath>
#include <iostream> 
#include <vector>
#include <sys/times.h>
#include <unistd.h>

double time_difference(clock_t start, clock_t stop) {
	double time_diff = (double)(stop - start) / sysconf(_SC_CLK_TCK);
	return time_diff;
}

float rec_sum(std::vector<float> & v, unsigned begin, unsigned end) {
    if (end - begin == 0) return v[begin];
    if (end - begin == 1) return v[end] + v[begin];
    unsigned div = (end + begin) / 2;
    return rec_sum(v, begin, div) + rec_sum(v, div + 1, end);
}

int main() {
    
	struct tms * tms_start = new tms; 
	struct tms * tms_stop = new tms;
	clock_t clock_start = 0;
	clock_t clock_stop = times(tms_stop);

    const auto N = 1e7;
    const auto value = 0.82345f;
    std::vector<float> vctr(N);

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
        *i = value;

    auto sum1 = 0.0f;
    auto sum2 = 0.0f;

    std::cout << "Sumowanie rekurencyjne" << std::endl;
    clock_start = times(tms_start);

    sum1 = rec_sum(vctr, 0, vctr.size() - 1);

    clock_stop = times(tms_stop);
	printf("real time: %f\n", time_difference(clock_start, clock_stop));
	printf("system time: %f\n", time_difference(tms_start->tms_stime, tms_stop->tms_stime));
	printf("user time: %f\n\n\n", time_difference(tms_start->tms_utime, tms_stop->tms_utime));

    std::cout << "Sumowanie zwykle" << std::endl;
    clock_start = times(tms_start);

    for (auto i = vctr.begin(); i != vctr.end(); ++i) 
       sum2 += *i;

     
    clock_stop = times(tms_stop);
	printf("real time: %f\n", time_difference(clock_start, clock_stop));
	printf("system time: %f\n", time_difference(tms_start->tms_stime, tms_stop->tms_stime));
	printf("user time: %f\n\n\n", time_difference(tms_start->tms_utime, tms_stop->tms_utime));
    
}