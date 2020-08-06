#include "utils.h"

namespace oort {
    namespace utils {
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

        void printDim(const uint32_t dim, uint32_t* index, const math::dtensor t) {
            if (dim == 0) {
                // Print values.
                for (uint32_t i = 0; i < t.dimSizes[dim]; i++) {
                    printf(" %.8f ", t.values[(*index)++]);
                }
            } else {
                for (uint32_t i = 0; i < t.dimSizes[dim]; i++) {
                    printf("[");
                    printDim(dim - 1, index, t);
                    printf("]");
                }
            }
        }

        void print(const math::dtensor t) {
            uint32_t index = 0;
            printf("\nDTENSOR\n");
            printf("[");
            printDim(t.dimNum - 1, &index, t);
            printf("]");
            printf("\n");
        }

        void print(const math::dtensor1d t) {
            printf("\nDTENSOR1D\n");
            for (uint32_t i = 0; i < t.width; i++) {
                printf("%.8f\t", t.values[i]);
            }
            printf("\n");
        }
        void print(const math::dtensor2d t) {
            printf("\nDTENSOR2D\n");
            for (uint32_t j = 0; j < t.height; j++) {
                for (uint32_t i = 0; i < t.width; i++) {
                    printf("%.8f\t", t.values[IDX2D(i, j, t.width)]);
                }
                printf("\n");
            }
        }
        void print(const math::dtensor3d t) {
            printf("\nITENSOR3D %dx%dx%d\n", t.width, t.height, t.depth);
            for (uint32_t k = 0; k < t.depth; k++) {
                for (uint32_t j = 0; j < t.height; j++) {
                    for (uint32_t i = 0; i < t.width; i++) {
                        printf("%.8f\t", t.values[IDX3D(i, j, k, t.width, t.height)]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        void print(const math::itensor1d t) {
            printf("\nITENSOR1D %d\n", t.width);
            for (uint32_t i = 0; i < t.width; i++) {
                printf("%d\t", t.values[i]);
            }
            printf("\n");
        }
        void print(const math::itensor2d t) {
            printf("\nITENSOR2D %dx%d\n", t.width, t.height);
            for (uint32_t j = 0; j < t.height; j++) {
                for (uint32_t i = 0; i < t.width; i++) {
                    printf("%d\t", t.values[IDX2D(i, j, t.width)]);
                }
                printf("\n");
            }
        }
        void print(const math::itensor3d t) {
            printf("\nITENSOR3D %dx%dx%d\n", t.width, t.height, t.depth);
            for (uint32_t k = 0; k < t.depth; k++) {
                for (uint32_t j = 0; j < t.height; j++) {
                    for (uint32_t i = 0; i < t.width; i++) {
                        printf("%d\t", t.values[IDX3D(i, j, k, t.width, t.height)]);
                    }
                    printf("\n");
                }
            }
        }
    }
}
