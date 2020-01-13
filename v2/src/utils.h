#ifndef __UTILS__
#define __UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// UNIX Standard Definitions.
#include <unistd.h>
// Error Number Definitions.
#include <errno.h>
#include "math.h"

#define byte unsigned char

namespace oort {
    double dRandBetween(double low, double high);
    int iRandBetween(int low, int high);
    // Big endian conversion.
    byte* uintToByteArray(uint32_t value, uint8_t depth);
    // Big endian conversion.
    uint32_t byteArrayToUint(byte* values, uint8_t depth);
    byte* doubleToByteArray(double value, uint8_t depth);
    double byteArrayToDouble(byte* values, uint8_t depth);
    double getTime();
    double getNanoTime();
}

#endif
