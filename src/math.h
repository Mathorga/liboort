#ifndef __MATH__
#define __MATH__

#include <math.h>
// Time functions and types, used for random seeds generation.
#include <time.h>
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
            WRONG_SIZE = 1,
            WRONG_DIMS = 2
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

        // Int tensors.
        // ND.
        struct itensor {
            uint32_t dimNum;
            uint32_t* dimSizes;
            uint32_t* values;
        };
        // 1D.
        struct itensor1d {
            uint32_t width;
            uint32_t* values;
        };
        // 2D.
        struct itensor2d {
            uint32_t width;
            uint32_t height;
            uint32_t* values;
        };
        // 3D.
        struct itensor3d {
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            uint32_t* values;
        };
        // 4D.
        struct itensor4d {
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            uint32_t length;
            uint32_t* values;
        };

        // Double tensors.
        // ND.
        struct dtensor {
            uint32_t dimNum;
            uint32_t* dimSizes;
            double* values;
        };
        // 1D.
        struct dtensor1d {
            uint32_t width;
            double* values;
        };
        // 2D.
        struct dtensor2d {
            uint32_t width;
            uint32_t height;
            double* values;
        };
        // 3D.
        struct dtensor3d {
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            double* values;
        };
        // 4D.
        struct dtensor4d {
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            uint32_t length;
            double* values;
        };

        // Functors definitions.
        struct DUnFunc {
        public:
            virtual double operator() (const double x) = 0;
            virtual ~DUnFunc() = 0;
        };
        struct Sigmoid : public DUnFunc {
        public:
            double operator() (const double x);
            ~Sigmoid();
        };
        struct FastSigmoid : public DUnFunc {
        public:
            double operator() (const double x);
            ~FastSigmoid();
        };
        struct ReLu : public DUnFunc {
        public:
            double operator() (const double x);
            ~ReLu();
        };
        struct HTan : public DUnFunc {
        public:
            double operator() (const double x);
            ~HTan();
        };
        struct Identity : public DUnFunc {
        public:
            double operator() (const double x);
            ~Identity();
        };
        struct BinStep : public DUnFunc {
        public:
            double operator() (const double x);
            ~BinStep();
        };
        struct DT1DBinFunc {
        public:
            virtual double operator() (const dtensor1d t1, const dtensor1d t2) = 0;
        };
        struct MSE : public DT1DBinFunc {
        public:
            double operator() (const dtensor1d t1, const dtensor1d t2);
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

        // Returns a random double number between <low> and <high>.
        double drand(double low, double high);
        // Returns a random integer number between <low> and <high>.
        uint32_t irand(const uint32_t low, const uint32_t high);

        // Calculates the derivative of the given function in x = <value>.
        // Default epsilon is 0.01.
        double der(const double x, DUnFunc* function);
        // Calculates the derivative of the given function in x = <value>, using the
        // given epsilon.
        double der(const double x, DUnFunc* function, const double e);
        // Calculates the given function in x = <value>.
        double prim(const double x, DUnFunc* function);
        error prim(const dtensor1d res, const dtensor1d t, DUnFunc* function);
        error prim(const dtensor2d res, const dtensor2d t, DUnFunc* function);
        error prim(const dtensor3d res, const dtensor3d t, DUnFunc* function);
        error der(const dtensor1d res, const dtensor1d t, DUnFunc* function);
        error der(const dtensor2d res, const dtensor2d t, DUnFunc* function);
        error der(const dtensor3d res, const dtensor3d t, DUnFunc* function);
        error der(const dtensor1d res, const dtensor1d t1, const dtensor1d t2, DT1DBinFunc* function);
        double der(const dtensor1d t1, const dtensor1d t2, const uint32_t i, DT1DBinFunc* function);
        double prim(const dtensor1d t1, const dtensor1d t2, DT1DBinFunc* function);

        // Tensor functions.
        error zero(const itensor1d t);
        error zero(const itensor2d t);
        error zero(const itensor3d t);
        //TODO
        error zero(const dtensor t);
        error zero(const dtensor1d t);
        error zero(const dtensor2d t);
        error zero(const dtensor3d t);
        // Initializes the given ND tensor <t> with incremental values, starting from 0 to the number of values it holds.
        error inc(const dtensor t);
        // Initializes the given ND tensor <t> with random values between 0 and <max>.
        error rinit(const dtensor t, const double max);
        error rinit(const dtensor1d t, const double max);
        error rinit(const dtensor2d t, const double max);
        error init(const dtensor t, const double value);
        error init(const dtensor1d t, const double value);
        error init(const dtensor2d t, const double value);
        error init(const dtensor3d t, const double value);
        error init(const itensor1d t, const uint32_t value);
        error init(const itensor2d t, const uint32_t value);
        error init(const itensor3d t, const uint32_t value);
        error cadd(const dtensor1d res, const dtensor1d t);
        // Performs the addition of tensor <t> to tensor <res>.
        //TODO
        error add(const dtensor res, const dtensor t);
        error add(const dtensor1d res, const dtensor1d t);
        error add(const dtensor2d res, const dtensor2d t);
        error add(const dtensor3d res, const dtensor3d t);
        // Computes the sum between tensor <t1> and tensor <t2>, storing the output in <res>.
        error add(const dtensor1d res, const dtensor1d t1, const dtensor1d t2);
        error add(const dtensor2d res, const dtensor2d t1, const dtensor2d t2);
        error add(const dtensor3d res, const dtensor3d t1, const dtensor3d t2);
        // Performs the dot product between 2D tensors <t1> and <t2>.
        error mul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2);
        // Performs the dot product between 2D tensor <t1> and 1D tensor <t2>.
        error mul(const dtensor1d res, const dtensor2d t1, const dtensor1d t2);
        // Performs the dot product between 1D tensor <t1> and 2D tensor <t2>.
        error mul(const dtensor1d res, const dtensor1d t1, const dtensor2d t2);
        error mul(const dtensor2d res, const dtensor1d t1, const dtensor1d t2);
        error hmul(const dtensor1d res, const dtensor1d t1, const dtensor1d t2);
        // Performs the Hadamard product between 2D tensors <t1> and <t2>.
        error hmul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2);
        error hmul(const dtensor3d res, const dtensor3d t1, const dtensor3d t2);
        // Performs the scalar product between scalar <value> and 2D tensor <t>.
        error smul(const dtensor2d res, const double value, const dtensor2d t);
        error sigmoid(const dtensor1d res, const dtensor1d t);
        // Calculates the sigmoid of every value of 2D tensor <t> and puts them in <res>.
        error sigmoid(const dtensor2d res, const dtensor2d t);
        error sigmoid(const dtensor3d res, const dtensor3d t);
        error mse(double* res, const dtensor1d t1, const dtensor1d t2);
        error mse(double* res, const dtensor2d t1, const dtensor2d t2);
        error mse(double* res, const dtensor3d t1, const dtensor3d t2);
        error normalize(const dtensor1d res, const dtensor1d t, const double mean, const double stddev);
        error normalize(const dtensor2d res, const dtensor2d t, const double mean, const double stddev);
        error normalize(const dtensor3d res, const dtensor3d t, const double mean, const double stddev);
        // Allocate an ND tensor given the number of dimensions and the size of each dimension.
        error alloc(dtensor* t, uint32_t* dimSizes, const uint32_t dimNum);
        // Allocate an ND tensor with a single dimension.
        error alloc(dtensor* t, uint32_t width);
        error alloc(dtensor1d* t, const uint32_t width);
        error alloc(dtensor2d* t, const uint32_t width, const uint32_t height);
        error alloc(dtensor3d* t, const uint32_t width, const uint32_t height, const uint32_t depth);
        error alloc(itensor1d* t, const uint32_t width);
        error alloc(itensor2d* t, const uint32_t width, const uint32_t height);
        error alloc(itensor3d* t, const uint32_t width, const uint32_t height, const uint32_t depth);
        error copy(const dtensor1d t1, const dtensor t2);
        error copy(const dtensor2d t1, const dtensor t2);
        error copy(const dtensor3d t1, const dtensor t2);
        error copy(const dtensor1d t1, const dtensor1d t2);
        error copy(const dtensor2d t1, const dtensor2d t2);
        error copy(const dtensor3d t1, const dtensor3d t2);
        error copy(const dtensor2d t1, const dtensor1d t2, const uint32_t index);
        error dealloc(const dtensor1d t);
        error dealloc(const dtensor2d t);
        error dealloc(const dtensor3d t);
        error reshape(dtensor t, uint32_t* sizes, const uint32_t numSizes);
        error flatten(const dtensor t);

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
// #include "tensor.cpp"

#endif
