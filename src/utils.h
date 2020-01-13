#ifndef __UTILS__
#define __UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// Standars C strings.
#include <string.h>
// C++ object strings.
#include <string>
// UNIX Standard Definitions.
#include <unistd.h>
#include <limits>
#include <iostream>
#include <fstream>
// C++ string stream.
#include <sstream>
#include <cstddef>
#include <cmath>
// File Control Definitions.
#include <fcntl.h>
// POSIX Terminal Control Definitions.
#include <termios.h>
#include <unistd.h>
// Error Number Definitions.
#include <errno.h>
// C++ standard vector.
#include <vector>

#define IDX(i, j, n) ((i) * (n) + (j))
// Translates bidimensional indexes to a monodimensional one.
// |i| is the row index.
// |j| is the column index.
// |n| is the number of columns (length of the rows).
#define IDX2D(i, j, n) ((i * n) + j)
// Translates tridimensional indexes to a monodimensional one.
// |i| is the index in the first dimension.
// |j| is the index in the second dimension.
// |k| is the index in the third dimension.
// |m| is the size of the first dimension.
// |n| is the size of the second dimension.
#define IDX3D(i, j, k, m, n) ((i * n + j) + m * n * k)
#define byte unsigned char
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREY    "\x1b[90m"
#define ANSI_COLOR_RESET   "\x1b[0m"

namespace Oort {
    double dRandBetween(double low, double high);
    int iRandBetween(int low, int high);
    void setPrintColor(const char* color);
    void debugPrint(const char* string);
    // Big endian conversion.
    byte* uintToByteArray(uint32_t value, uint8_t depth);
    // Big endian conversion.
    uint32_t byteArrayToUint(byte* values, uint8_t depth);
    byte* doubleToByteArray(double value, uint8_t depth);
    double byteArrayToDouble(byte* values, uint8_t depth);
    double getTime();
    double getNanoTime();
    std::vector<std::string> splitString(const std::string& inputString, char separator);
    double sigmoid(double input);
    double dSigmoid(double input);
    void printPercentage(uint32_t value, uint32_t maxValue);
    // Vector<std::string> splitString(const std::string& inputString, char separator);

    // void dump(const uint8_t* image, unsigned int n, const char* filename);
    // uint8_t* readImage(const char* filename, const uint8_t n);

    // Matrices functions.
    void dMatMul(double* result,
                 double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
                 double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum);
    void dHMatMul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize);
}

#endif
