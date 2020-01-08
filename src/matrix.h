#ifndef __SERIAL__
#define __SERIAL__

#include <stdio.h>
#include <stdlib.h>
#include "calculus.h"
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

// Translates bidimensional indexes to a monodimensional one.
// |i| is the column index.
// |j| is the row index.
// |n| is the number of columns (length of the rows).
#define IDX(i, j, n) ((i) * (n) + (j))

namespace oort {
    // Matrices functions.
    void matMul(double* result,
                double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
                double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum);
    void hMatMul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize);
    void hMatMul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize);
    void scalMul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize);
    void scalMul(double* result, double value, double* matrix, uint32_t matrixSize);
    void sigmoidMat(double* result, double* matrix, uint32_t matrixSize);
}

#endif
