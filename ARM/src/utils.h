#ifndef __UTILS__
#define __UTILS__
#define IDX(i, j, n) ((i) * (n) + (j))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <iostream>
#include <cmath>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREY    "\x1b[90m"
#define ANSI_COLOR_RESET   "\x1b[0m"

double dRandBetween(double low, double high);
int iRandBetween(int low, int high);
void setPrintColor(const char* color);
void debugPrint(const char* string);
double getTime();
double getNanoTime();
void dump(const uint8_t* image, unsigned int n, const char* filename);
uint8_t* readImage(const char* filename, const uint8_t n);

#endif
