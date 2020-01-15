#include "utils.h"

namespace oort {
    double dRandBetween(double low, double high) {
        // Randomize seed.
        // srand(time(NULL));
        return ((double) rand() / RAND_MAX) * (high - low) + low;
    }

    int iRandBetween(int low, int high) {
        // Randomize seed.
        // srand(time(NULL));
        return rand() % high + low;
    }

    byte* uintToByteArray(uint32_t value, uint8_t depth) {
        // Check if depth is between 1 and 4.
        if (depth < 1) {
            depth = 1;
        } else if (depth > 4) {
            depth = 4;
        }

        byte* result = (byte*) malloc(depth);

        // Convert the value to a depth-long byte array.
        for (uint8_t i = 0; i < depth; i++) {
            result[(depth - 1) - i] = (value >> (8 * i));
        }

        return result;
    }

    uint32_t byteArrayToUint(byte* values, uint8_t depth) {
        uint32_t result = 0;

        // Check if depth is between 1 and 4.
        // (Is this necessary?)
        if (depth < 1) {
            depth = 1;
        } else if (depth > 4) {
            depth = 4;
        }

        // Convert byte array to unsigned integer.
        for (uint8_t i = 0; i < depth; i++) {
            result = (result << 8) + values[i];
        }

        return result;
    }

    byte* doubleToByteArray(double value, uint8_t depth) {
        return uintToByteArray(value * (((pow(2, 8 * depth)) - 1)), depth);
    }

    double byteArrayToDouble(byte* values, uint8_t depth) {
        // The value is calculated obtaining the same number interpreted as an unsigned integer of specified depth and
        // then dividing it by the maximum possible unsigned integer value of the same depth.
        // The "- 1" is used to take into account the correct maximum value, since otherwise 1.0 would never be
        // returned.
        return byteArrayToUint(values, depth) / ((pow(2, 8 * depth)) - 1);
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

    void print(const math::dtensor2d t) {
        printf("\nTENSOR2D\n");
        for (uint32_t i = 0; i < t.height; i++) {
            for (uint32_t j = 0; j < t.width; j++) {
                printf("%f\t", t.values[IDX2D(i, j, t.width)]);
            }
            printf("\n");
        }
    }
}
