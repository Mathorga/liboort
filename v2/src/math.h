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
    // Types definitions.
    template <typename T>
    struct tensor {
        uint32_t dimNum;
        uint32_t* dimSizes;
        T* values;
    };
    template <typename T>
    struct tensor1d {
        uint32_t width;
        T* values;
    };
    template <typename T>
    struct tensor2d {
        uint32_t width;
        uint32_t height;
        T* values;
    };
    template <typename T>
    struct tensor3d {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        T* values;
    };
    struct dtensor1d {
        uint32_t width;
        double* values;
    };
    struct dtensor2d {
        uint32_t width;
        uint32_t height;
        double* values;
    };
    struct dtensor3d {
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        double* values;
    };

    struct str {};

    // Functors definitions.
    class UnaryFunction {
    public:
        virtual ~UnaryFunction() {};
        virtual double operator() (const double value) = 0;
    };
    class Sigmoid : public UnaryFunction {
    public:
        Sigmoid() {};
        ~Sigmoid() {};
        double operator() (const double value);
    };
    class FastSigmoid : public UnaryFunction {
    public:
        FastSigmoid() {};
        ~FastSigmoid() {};
        double operator() (const double value);
    };

    // Functions definitions.
    double sigmoid(const double value);
    double fsigmoid(const double value);
    double dsigmoid(const double value);
    double dfsigmoid(const double value);
    // Matrices functions.
    void mul(double* result,
             double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
             double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum);
    void mul(const dtensor2d result, const dtensor2d t1, const dtensor2d t2);
    void hmul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize);
    void hmul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize);
    void hmul(const dtensor2d result, const dtensor2d t1, const dtensor2d t2);
    void smul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize);
    void smul(double* result, double value, double* matrix, uint32_t matrixSize);
    void smul(const dtensor2d result, const double value, const dtensor2d matrix);
    void sigmoid(double* result, double* matrix, uint32_t matrixSize);

    double der(const double value, UnaryFunction* function, const double epsilon);
    double der(const double value, UnaryFunction* function);
    double prim(const double value, UnaryFunction* function);
}
