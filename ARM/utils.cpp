#include "utils.h"

double dRandBetween(double low, double high) {
    return ((double) rand() / RAND_MAX) * (high - low) + low;
}

void setPrintColor(const char *color) {
    printf("%s", color);
}

double getTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

double getNanoTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_nsec;//tv_sec + (double)ts.tv_nsec / 1e9;
}
