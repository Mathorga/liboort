#include "utils.h"

namespace Oort {
    double dRandBetween(double low, double high) {
        return ((double) rand() / RAND_MAX) * (high - low) + low;
    }

    int iRandBetween(int low, int high) {
        return rand() % high + low;
    }

    void setPrintColor(const char *color) {
        printf("%s", color);
    }

    void debugPrint(const char* string) {
        printf("\n%s\n", string);
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
}
