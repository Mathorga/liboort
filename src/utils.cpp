#include "utils.h"

namespace Oort {
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

    void setPrintColor(const char *color) {
        printf("%s", color);
    }

    void debugPrint(const char* string) {
        printf("\n%s\n", string);
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

    std::vector<std::string> splitString(const std::string& inputString, char separator) {
        std::vector<std::string> elements;
        std::stringstream stream(inputString);
        std::string element;

        while(std::getline(stream, element, separator)) {
            elements.push_back(element);
        }
        return elements;
    }

    double sigmoid(double input) {
        return (1 / (1 + (pow(M_E, -(input)))));
    }

    double dSigmoid(double input) {
        return sigmoid(input) * (1 - sigmoid(input));
    }

    void printPercentage(uint32_t value, uint32_t maxValue) {
        if (value < maxValue) {
            if ((value * 100) / maxValue > ((value - 1) * 100) / maxValue) {
                printf("\r%d%%", (value * 100) / maxValue);
                fflush(stdout);
            }
        } else {
            //TODO Print error.
        }
    }

    // Vector<std::String> splitString(std::String inputString, char separator) {
    //     Vector<std:string> elements;
    //     std::stringstream stringStream(inputString);
    //     std::string element;
    //
    //     while(std::getline(stringStream, element, separator)) {
    //         elements.add_last(element);
    //     }
    //     return elements;
    // }

    // void dump(const uint8_t* image, unsigned int n, const char* filename) {
    //     printf("\n%s, %d\n", filename, n);
    //     FILE* out = fopen(filename, "w");
    //     if (out == NULL) {
    //         printf("Cannot open \"%s\"\n", filename);
    //         abort();
    //     }
    //     fprintf(out, "P6\n");
    //     fprintf(out, "%d %d\n", n, n);
    //     fprintf(out, "255\n");
    //     for (unsigned int x = 0; x < n; x++) {
    //         for (unsigned int y = 0; y < n; y++) {
    //             fprintf(out, "%c%c%c", image[IDX(x, y, n)], 0, 0);
    //         }
    //     }
    //     fclose(out);
    // }
    //
    // uint8_t* readImage(const char* filename, const uint8_t n) {
    //     FILE* in = fopen(filename, "r");
    //     uint16_t i = 0;
    //     uint16_t j = 0;
    //     uint8_t* bytes = (uint8_t*) malloc(n * n * sizeof(uint8_t));
    //     char ch;
    //
    //     for (uint16_t k = 0; k < n * n; k++) {
    //         bytes[k] = 0;
    //     }
    //
    //     if (in == NULL) {
    //         printf("Cannot open \"%s\"\n", filename);
    //         abort();
    //     }
    //
    //     while (i < 3) {//(ch = fgetc(in)) != EOF) {
    //         ch = fgetc(in);
    //         j++;
    //         if (ch == '\n') {
    //             i++;
    //         }
    //     }
    //     printf("\n%d %d\n", i, j);
    //     i = 0;
    //     j = 0;
    //     while (!feof(in)) {
    //         ch = fgetc(in) + 128;
    //         if (i % 3 == 0) {
    //             bytes[j] = ch;
    //             j++;
    //         }
    //         i++;
    //     }
    //     printf("\n%d %d %d\n", i, j, EOF);
    //     return bytes;
    // }



    void dMatMul(double* result,
                 double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
                 double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum) {
        for (uint32_t i = 0; i < firstRowsNum; i++) {
            for (uint32_t j = 0; j < secondColsNum; j++) {
                result[IDX(i, j, secondColsNum)] = 0.0;
                for (uint32_t k = 0; k < firstColsNum; k++) {
                    result[IDX(i, j, secondColsNum)] += firstMatrix[IDX(i, k, firstColsNum)] * secondMatrix[IDX(k, j, secondColsNum)];
                }
            }
        }
    }
    void dHMatMul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
}
