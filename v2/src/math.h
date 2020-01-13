#include <math.h>
// Fixed size int types definitions.
#include <stdint.h>

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
#define IDX3D(i, j, k, m, n) (((i * m) + j) + (m * n * k))

namespace oort {
    typedef struct {
        uint32_t length;
        double* values;
    } vector;

    typedef struct {
        uint32_t width;
        uint32_t height;
        double* values;
    } matrix;

    typedef struct {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        double* values;
    } matrix3d;

    double sigmoid(const double value);
    double fsigmoid(const double value);
    double dsigmoid(const double value);
    double dfsigmoid(const double value);
    // Matrices functions.
    void matmul(double* result,
                double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
                double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum);
    void hmatmul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize);
    void hmatmul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize);
    void scalmul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize);
    void scalmul(double* result, double value, double* matrix, uint32_t matrixSize);
    void sigmoidmat(double* result, double* matrix, uint32_t matrixSize);
}
