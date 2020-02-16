#ifndef __MATH__
#define __MATH__

#include <math.h>
// Fixed size int types definitions.
#include <stdint.h>
// Debug.
#include <stdio.h>

// Translate an id wrapping it to the provided size (pacman effect).
// [i] is the given index.
// [n] is the size over which to wrap.
#define IDX(i, n) (i < 0 ? (i % n) : (n + (i % n)))
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
    namespace math {
        // Error definitions.
        enum error {
            NO_ERROR = 0,
            WRONG_SIZE = 1
        };
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
        struct itensor {
            uint32_t dimNum;
            uint32_t* dimSizes;
            uint32_t* values;
        };
        struct itensor1d {
            uint32_t width;
            uint32_t* values;
        };
        struct itensor2d {
            uint32_t width;
            uint32_t height;
            uint32_t* values;
        };
        struct itensor3d {
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            uint32_t* values;
        };
        struct dtensor {
            uint32_t dimNum;
            uint32_t* dimSizes;
            double* values;
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

        // Functors definitions.
        class DUnaryFunction {
        public:
            virtual double operator() (const double x) = 0;
        };
        class Sigmoid : public DUnaryFunction {
        public:
            double operator() (const double x);
        };
        class FastSigmoid : public DUnaryFunction {
        public:
            double operator() (const double x);
        };
        class DTensor1DFunction {
        public:
            virtual double operator() (const dtensor1d x) = 0;
        };
        class MSE : public DTensor1DFunction {
        public:
            double operator() (const dtensor1d x);
        };

        // Functions definitions.
        // Calculates the sigmoid of the given value.
        double sigmoid(const double value);
        // Calculates the fast sigmoid of the given value.
        double fsigmoid(const double value);
        // Calculates the derivative sigmoid of the given value.
        double dsigmoid(const double value);
        // Calculates the derivative fast sigmoid of the given value.
        double dfsigmoid(const double value);

        // Calculates the derivative of the given function in x = <value>.
        // Default epsilon is 0.01.
        double der(const double x, DUnaryFunction* function);
        // Calculates the derivative of the given function in x = <value>, using the
        // given epsilon.
        double der(const double x, DUnaryFunction* function, const double e);
        // Calculates the given function in x = <value>.
        double prim(const double x, DUnaryFunction* function);
        double prim(const double x, DTensor1DFunction* function);
        error prim(const dtensor1d res, const dtensor1d t, DUnaryFunction* function);
        error prim(const dtensor2d res, const dtensor2d t, DUnaryFunction* function);
        error prim(const dtensor3d res, const dtensor3d t, DUnaryFunction* function);


        // Tensor functions.
        error zero(const dtensor1d t);
        error zero(const dtensor2d t);
        error zero(const dtensor3d t);
        error init(const dtensor1d t, const double value);
        error init(const dtensor2d t, const double value);
        error init(const dtensor3d t, const double value);
        error init(const itensor1d t, const uint32_t value);
        error init(const itensor2d t, const uint32_t value);
        error init(const itensor3d t, const uint32_t value);
        error add(const dtensor1d res, const dtensor1d t1, const dtensor1d t2);
        error add(const dtensor2d res, const dtensor2d t1, const dtensor2d t2);
        error add(const dtensor3d res, const dtensor3d t1, const dtensor3d t2);
        // Performs the dot product between 2D tensors <t1> and <t2>.
        error mul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2);
        // Performs the dot product between 2D tensor <t1> and 1D tensor <t2>.
        error mul(const dtensor1d res, const dtensor2d t1, const dtensor1d t2);
        // Performs the dot product between 1D tensor <t1> and 2D tensor <t2>.
        error mul(const dtensor1d res, const dtensor1d t1, const dtensor2d t2);
        // Performs the Hadamard product between 2D tensors <t1> and <t2>.
        error hmul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2);
        // Performs the scalar product between scalar <value> and 2D tensor <t>.
        error smul(const dtensor2d res, const double value, const dtensor2d t);
        error sigmoid(const dtensor1d res, const dtensor1d t);
        // Calculates the sigmoid of every value of 2D tensor <t> and puts them in
        // <res>.
        error sigmoid(const dtensor2d res, const dtensor2d t);
        error sigmoid(const dtensor3d res, const dtensor3d t);
        error mse(double* res, const dtensor1d t1, const dtensor1d t2);
        error mse(double* res, const dtensor2d t1, const dtensor2d t2);
        error mse(double* res, const dtensor3d t1, const dtensor3d t2);
        error normalize(const dtensor1d res, const dtensor1d t, const double mean, const double stddev);
        error normalize(const dtensor2d res, const dtensor2d t, const double mean, const double stddev);
        error normalize(const dtensor3d res, const dtensor3d t, const double mean, const double stddev);
        error alloc(dtensor1d* t, const uint32_t width);
        error alloc(dtensor2d* t, const uint32_t width, const uint32_t height);
        error alloc(dtensor3d* t, const uint32_t width, const uint32_t height, const uint32_t depth);
        error alloc(itensor1d* t, const uint32_t width);
        error alloc(itensor2d* t, const uint32_t width, const uint32_t height);
        error alloc(itensor3d* t, const uint32_t width, const uint32_t height, const uint32_t depth);
        error copy(const dtensor1d t1, const dtensor1d t2);
        error copy(const dtensor2d t1, const dtensor2d t2);
        error copy(const dtensor3d t1, const dtensor3d t2);
        error copy(const dtensor2d t1, const dtensor1d t2, const uint32_t index);
        error dealloc(const dtensor1d t);
        error dealloc(const dtensor2d t);
        error dealloc(const dtensor3d t);
        // Template functions.
        template <typename T>
        error alloc(tensor1d<T>* t, const uint32_t width) {
            t->width = width;
            t->values = (T*) malloc(width * sizeof(T));
            return error::NO_ERROR;
        }
        template <typename T>
        error alloc(tensor2d<T>* t, const uint32_t width, const uint32_t height) {
            t->width = width;
            t->height = height;
            t->values = (T*) malloc(width * height * sizeof(T));
            return error::NO_ERROR;
        }
        template <typename T>
        error alloc(tensor3d<T>* t, const uint32_t width, const uint32_t height, const uint32_t depth) {
            t->width = width;
            t->height = height;
            t->depth = depth;
            t->values = (T*) malloc(width * height * depth * sizeof(T));
            return error::NO_ERROR;
        }
    }
}

// Add definitions for template functions.
// #include "math.cpp"

#endif
