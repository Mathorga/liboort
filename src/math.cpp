#include "math.h"

namespace oort {
    namespace math {
        double sigmoid(const double value) {
            return (1 / (1 + (exp(-value))));
        }
        double fsigmoid(const double value) {
            return 0.5 * value / (1 + abs(value)) + 0.5;
        }
        double dsigmoid(const double value) {
            return sigmoid(value) * (1 - sigmoid(value));
        }
        double dfsigmoid(const double value) {
            return 1 / (2 * pow((1 + abs(value)), 2));
        }
        double drand(const double low, const double high) {
            // Randomize seed.
            // srand(time(NULL));
            return ((double) rand() / RAND_MAX) * (high - low) + low;
        }

        // Initialization functions.
        uint32_t irand(const uint32_t low, const uint32_t high) {
            // Randomize seed.
            // srand(time(NULL));
            return rand() % high + low;
        }
        error zero(const itensor1d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width; i++) {
                t.values[i] = 0;
            }
            return err;
        }
        error zero(const itensor2d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                t.values[i] = 0;
            }
            return err;
        }
        error zero(const itensor3d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height * t.depth; i++) {
                t.values[i] = 0;
            }
            return err;
        }
        error zero(const dtensor1d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width; i++) {
                t.values[i] = 0.0;
            }
            return err;
        }
        error zero(const dtensor2d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                t.values[i] = 0.0;
            }
            return err;
        }
        error zero(const dtensor3d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height * t.depth; i++) {
                t.values[i] = 0.0;
            }
            return err;
        }
        error inc(const dtensor t) {
            // Get the total size of the tensor.
            uint32_t size = 0;
            for (uint32_t i = 0; i < t.dimNum; i++) {
                if (size <= 0) {
                    size = t.dimSizes[i];
                } else {
                    size *= t.dimSizes[i];
                }
            }

            for (uint32_t i = 0; i < size; i++) {
                t.values[i] = i;
            }

            return error::NO_ERROR;
        }
        error rinit(const dtensor t, const double max) {
            // Get the total size of the tensor.
            uint32_t size = 0;
            for (uint32_t i = 0; i < t.dimNum; i++) {
                if (size <= 0) {
                    size = t.dimSizes[i];
                } else {
                    size *= t.dimSizes[i];
                }
            }

            srand(time(NULL));

            for (uint32_t i = 0; i < size; i++) {
                t.values[i] = drand(0, max);
            }

            return error::NO_ERROR;
        }
        error rinit(const dtensor1d t, const double max) {
            srand(time(NULL));

            for (uint32_t i = 0; i < t.width; i++) {
                t.values[i] = drand(0, max);
            }

            return error::NO_ERROR;
        }
        error rinit(const dtensor2d t, const double max) {
            srand(time(NULL));

            for (uint32_t i = 0; i < t.width * t.height; i++) {
                t.values[i] = drand(0, max);
            }

            return error::NO_ERROR;
        }
        error init(const dtensor t, const double value) {
            // Get the total size of the tensor.
            uint32_t size = 0;
            for (uint32_t i = 0; i < t.dimNum; i++) {
                if (size <= 0) {
                    size = t.dimSizes[i];
                } else {
                    size *= t.dimSizes[i];
                }
            }

            for (uint32_t i = 0; i < size; i++) {
                t.values[i] = value;
            }

            return error::NO_ERROR;
        }
        error init(const dtensor1d t, const double value) {
            for (uint32_t i = 0; i < t.width; i++) {
                t.values[i] = value;
            }
            return error::NO_ERROR;
        }
        error init(const dtensor2d t, const double value) {
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                t.values[i] = value;
            }
            return error::NO_ERROR;
        }
        error init(const dtensor3d t, const double value) {
            for (uint32_t i = 0; i < t.width * t.height * t.depth; i++) {
                t.values[i] = value;
            }
            return error::NO_ERROR;
        }
        error init(const itensor1d t, const uint32_t value) {
            for (uint32_t i = 0; i < t.width; i++) {
                t.values[i] = value;
            }
            return error::NO_ERROR;
        }
        error init(const itensor2d t, const uint32_t value) {
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                t.values[i] = value;
            }
            return error::NO_ERROR;
        }
        error init(const itensor3d t, const uint32_t value) {
            for (uint32_t i = 0; i < t.width * t.height * t.depth; i++) {
                t.values[i] = value;
            }
            return error::NO_ERROR;
        }

        // Operation functions.
        error cadd(const dtensor1d res, const dtensor1d t) {
            double sum = 0.0;
            for (uint32_t i = 0; i < t.width; i++) {
                sum += t.values[i];
            }

            for (uint32_t i = 0; i < res.width; i++) {
                res.values[i] += sum;
            }
            return error::NO_ERROR;
        }
        error add(const dtensor1d res, const dtensor1d t) {
            error err = error::NO_ERROR;
            if (res.width == t.width) {
                for (uint32_t i = 0; i < res.width; i++) {
                    res.values[i] += t.values[i];
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error add(const dtensor2d res, const dtensor2d t) {
            error err = error::NO_ERROR;
            if (res.width == t.width &&
                res.height == t.height) {
                for (uint32_t i = 0; i < res.width * res.height; i++) {
                    res.values[i] += t.values[i];
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error add(const dtensor3d res, const dtensor3d t) {
            error err = error::NO_ERROR;
            if (res.width == t.width &&
                res.height == t.height &&
                res.depth == t.depth) {
                for (uint32_t i = 0; i < res.width * res.height * res.depth; i++) {
                    res.values[i] += t.values[i];
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error add(const dtensor1d res, const dtensor1d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width) {
                for (uint32_t i = 0; i < res.width; i++) {
                    res.values[i] = t1.values[i] + t2.values[i];
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error add(const dtensor2d res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width &&
                t1.height == t2.height && res.height == t2.height) {
                for (uint32_t i = 0; i < res.width * res.height; i++) {
                    res.values[i] = t1.values[i] + t2.values[i];
                }
            }
            return err;
        }
        error add(const dtensor3d res, const dtensor3d t1, const dtensor3d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width &&
                t1.height == t2.height && res.height == t2.height &&
                t1.depth == t2.depth && res.depth == t2.depth) {
                for (uint32_t i = 0; i < res.width * res.height * res.depth; i++) {
                    res.values[i] = t1.values[i] + t2.values[i];
                }
            }
            return err;
        }
        error mul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.height &&
                res.height == t1.height &&
                res.width == t2.width) {
                for (uint32_t i = 0; i < t1.height; i++) {
                    for (uint32_t j = 0; j < t2.width; j++) {
                        res.values[IDX2D(i, j, t2.width)] = 0.0;
                        for (uint32_t k = 0; k < t1.width; k++) {
                            res.values[IDX2D(i, j, t2.width)] += t1.values[IDX2D(i, k, t1.width)] * t2.values[IDX2D(k, j, t2.width)];
                        }
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error mul(const dtensor1d res, const dtensor2d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width &&
                res.width == t1.height) {
                for (uint32_t i = 0; i < t1.height; i++) {
                    res.values[i] = 0.0;
                    for (uint32_t j = 0; j < t2.width; j++) {
                        res.values[i] += t1.values[IDX2D(i, j, t1.width)] * t2.values[j];
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error mul(const dtensor1d res, const dtensor1d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.height &&
                res.width == t2.width) {
                for (uint32_t i = 0; i < t2.width; i++) {
                    res.values[i] = 0.0;
                    for (uint32_t j = 0; j < t1.width; j++) {
                        res.values[i] += t1.values[j] * t2.values[IDX2D(j, i, t2.width)];
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error mul(const dtensor2d res, const dtensor1d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;

            if (res.width == t2.width &&
                res.height == t1.width) {
                for (uint32_t i = 0; i < t1.width; i++) {
                    for (uint32_t j = 0; j < t2.width; j++) {
                        res.values[IDX2D(i, j, res.width)] = t1.values[i] * t2.values[j];
                    }
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error hmul(const dtensor1d res, const dtensor1d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width) {
                for (uint32_t i = 0; i < res.width; i++) {
                    res.values[i] = t1.values[i] * t2.values[i];
                }
            }
            return err;
        }
        error hmul(const dtensor2d res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width &&
                t1.height == t2.height && res.height == t2.height) {
                for (uint32_t i = 0; i < res.width * res.height; i++) {
                    res.values[i] = t1.values[i] * t2.values[i];
                }
            }
            return err;
        }
        error hmul(const dtensor3d res, const dtensor3d t1, const dtensor3d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width &&
                t1.height == t2.height && res.height == t2.height &&
                t1.depth == t2.depth && res.depth == t2.depth) {
                for (uint32_t i = 0; i < res.width * res.height * res.depth; i++) {
                    res.values[i] = t1.values[i] * t2.values[i];
                }
            }
            return err;
        }
        error smul(const dtensor2d res, const double value, const dtensor2d t) {
            error err = error::NO_ERROR;
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                res.values[i] = value * t.values[i];
            }
            return err;
        }
        error sigmoid(const dtensor1d res, const dtensor1d t) {
            for (uint32_t i = 0; i < t.width; i++) {
                res.values[i] = sigmoid(t.values[i]);
            }
            return error::NO_ERROR;
        }
        error sigmoid(const dtensor2d res, const dtensor2d t) {
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                res.values[i] = sigmoid(t.values[i]);
            }
            return error::NO_ERROR;
        }
        error sigmoid(const dtensor3d res, const dtensor3d t) {
            for (uint32_t i = 0; i < t.width * t.height * t.depth; i++) {
                res.values[i] = sigmoid(t.values[i]);
            }
            return error::NO_ERROR;
        }
        error mse(double* res, const dtensor1d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;
            (*res) = 0.0;

            if (t1.width == t2.width) {
                // Sum all squared errors.
                for (uint32_t i = 0; i < t1.width; i++) {
                    (*res) += pow(t1.values[i] - t2.values[i], 2);
                }

                // Compute the mean error.
                (*res) /= t1.width;
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error mse(double* res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            (*res) = 0.0;

            if (t1.width == t2.width &&
                t1.height == t2.height) {
                // Sum all squared errors.
                for (uint32_t i = 0; i < t1.width * t1.height; i++) {
                    (*res) += pow(t1.values[i] - t2.values[i], 2);
                }

                // Compute the mean error.
                (*res) /= (t1.width * t1.height);
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error mse(double* res, const dtensor3d t1, const dtensor3d t2) {
            error err = error::NO_ERROR;
            (*res) = 0.0;

            if (t1.width == t2.width &&
                t1.height == t2.height &&
                t1.depth == t2.depth) {
                // Sum all squared errors.
                for (uint32_t i = 0; i < t1.width * t1.height * t1.depth; i++) {
                    (*res) += pow(t1.values[i] - t2.values[i], 2);
                }

                // Compute the mean error.
                (*res) /= (t1.width * t1.height * t1.depth);
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error normalize(const dtensor1d res, const dtensor1d t, const double mean, const double stddev) {
            for (uint32_t i = 0; i < t.width; i++) {
                res.values[i] = (t.values[i] - mean) / stddev;
            }
            return error::NO_ERROR;
        }
        error normalize(const dtensor2d res, const dtensor2d t, const double mean, const double stddev) {
            for (uint32_t i = 0; i < t.width * t.height; i++) {
                res.values[i] = (t.values[i] - mean) / stddev;
            }
            return error::NO_ERROR;
        }
        error normalize(const dtensor3d res, const dtensor3d t, const double mean, const double stddev) {
            for (uint32_t i = 0; i < t.width * t.height * t.depth; i++) {
                res.values[i] = (t.values[i] - mean) / stddev;
            }
            return error::NO_ERROR;
        }

        // Allocation functions.
        error alloc(dtensor* t, uint32_t* dimSizes, const uint32_t dimNum) {
            // Keep track of the overall size of the tensor.
            uint32_t size = 0;
            t->dimNum = dimNum;
            t->dimSizes = (uint32_t*) malloc(dimNum * sizeof(uint32_t));

            // Loop through dimensions to set their size.
            for (uint32_t i = 0; i < dimNum; i++) {
                t->dimSizes[i] = dimSizes[i];

                // Update the overall size at each loop.
                if (size <= 0) {
                    size = dimSizes[i];
                } else {
                    size *= dimSizes[i];
                }
            }

            // Allocate the tensor based on the overall size.
            t->values = (double*) malloc(size * sizeof(double));

            return error::NO_ERROR;
        }
        error alloc(dtensor* t, uint32_t width) {
            // Set the number of dimensions.
            t->dimNum = 1;

            // Allocate dimension sizes.
            t->dimSizes = (uint32_t*) malloc(sizeof(uint32_t));
            t->dimSizes[0] = width;

            // Allocate values.
            t->values = (double*) malloc(width * sizeof(double));

            return error::NO_ERROR; 
        }
        error alloc(dtensor1d* t, const uint32_t width) {
            t->width = width;
            t->values = (double*) malloc(width * sizeof(double));
            return error::NO_ERROR;
        }
        error alloc(dtensor2d* t, const uint32_t width, const uint32_t height) {
            t->width = width;
            t->height = height;
            t->values = (double*) malloc(width * height * sizeof(double));
            return error::NO_ERROR;
        }
        error alloc(dtensor3d* t, const uint32_t width, const uint32_t height, const uint32_t depth) {
            t->width = width;
            t->height = height;
            t->depth = depth;
            t->values = (double*) malloc(width * height * depth * sizeof(double));
            return error::NO_ERROR;
        }
        error alloc(itensor1d* t, const uint32_t width) {
            t->width = width;
            t->values = (uint32_t*) malloc(width * sizeof(uint32_t));
            return error::NO_ERROR;
        }
        error alloc(itensor2d* t, const uint32_t width, const uint32_t height) {
            t->width = width;
            t->height = height;
            t->values = (uint32_t*) malloc(width * height * sizeof(uint32_t));
            return error::NO_ERROR;
        }
        error alloc(itensor3d* t, const uint32_t width, const uint32_t height, const uint32_t depth) {
            t->width = width;
            t->height = height;
            t->depth = depth;
            t->values = (uint32_t*) malloc(width * height * depth * sizeof(uint32_t));
            return error::NO_ERROR;
        }
        error copy(const dtensor1d t1, const dtensor t2) {
            error err = error::NO_ERROR;

            // Size of the ND tensor.
            uint32_t size = 0;

            // Loop through actual dimensions to multiply their sizes.
            for (uint32_t i = 0; i < t2.dimNum; i++) {
                // Update the overall size at each loop.
                if (size <= 0) {
                    size = t2.dimSizes[i];
                } else {
                    size *= t2.dimSizes[i];
                }
            }

            if (size != t1.width) {
                // The overall size of t2 does not match the width of t1.
                err = error::WRONG_SIZE;
            } else {
                // Sizes match, so copy.
                for (uint32_t i = 0; i < t1.width; i++) {
                    t1.values[i] = t2.values[i];
                }
            }
            return err;
        }
        error copy(const dtensor2d t1, const dtensor t2) {
            error err = error::NO_ERROR;

            // Size of the ND tensor.
            uint32_t size = 0;

            // Loop through actual dimensions to multiply their sizes.
            for (uint32_t i = 0; i < t2.dimNum; i++) {
                // Update the overall size at each loop.
                if (size <= 0) {
                    size = t2.dimSizes[i];
                } else {
                    size *= t2.dimSizes[i];
                }
            }

            if (size != t1.width * t1.height) {
                // The overall size of t2 does not match the size of t1.
                err = error::WRONG_SIZE;
            } else {
                // Sizes match, so copy.
                for (uint32_t i = 0; i < t1.width; i++) {
                    t1.values[i] = t2.values[i];
                }
            }
            return err;
        }
        error copy(const dtensor1d t1, const dtensor1d t2) {
            for (uint32_t i = 0; i < t1.width; i++) {
                t1.values[i] = t2.values[i];
            }
            return error::NO_ERROR;
        }
        error copy(const dtensor2d t1, const dtensor2d t2) {
            for (uint32_t i = 0; i < t1.width * t1.height; i++) {
                t1.values[i] = t2.values[i];
            }
            return error::NO_ERROR;
        }
        error copy(const dtensor3d t1, const dtensor3d t2) {
            for (uint32_t i = 0; i < t1.width * t1.height * t1.depth; i++) {
                t1.values[i] = t2.values[i];
            }
            return error::NO_ERROR;
        }
        error copy(const dtensor2d t1, const dtensor1d t2, const uint32_t index) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width) {
                for (uint32_t i = 0; i < t1.width; i++) {
                    t1.values[IDX2D(i, index, t1.width)] = t2.values[i];
                }
            } else {
                err = error::WRONG_SIZE;
            }
            return err;
        }
        error dealloc(const dtensor1d t) {
            free(t.values);
            return error::NO_ERROR;
        }
        error dealloc(const dtensor2d t) {
            free(t.values);
            return error::NO_ERROR;
        }
        error dealloc(const dtensor3d t) {
            free(t.values);
            return error::NO_ERROR;
        }
        error reshape(dtensor t, uint32_t* dimSizes, const uint32_t dimNum) {
            error err = error::NO_ERROR;
            // Keep track of the overall actual and given sizes in order to compare them.
            uint32_t actualSize = 0;
            uint32_t givenSize = 0;

            // Loop through actual dimensions to multiply their sizes.
            for (uint32_t i = 0; i < t.dimNum; i++) {
                // Update the overall size at each loop.
                if (actualSize <= 0) {
                    actualSize = t.dimSizes[i];
                } else {
                    actualSize *= t.dimSizes[i];
                }
            }

            // Loop through given dimensions to multiply their sizes.
            for (uint32_t i = 0; i < dimNum; i++) {
                // Update the overall size at each loop.
                if (givenSize <= 0) {
                    givenSize = dimSizes[i];
                } else {
                    givenSize *= dimSizes[i];
                }
            }

            // Reshape only if sizes match.
            if (givenSize == actualSize) {
                t.dimNum = dimNum;
                t.dimSizes = dimSizes;
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error flatten(const dtensor t) {
            // Keep track of the overall size of the tensor.
            uint32_t sizes[1];
            sizes[0] = 0;

            // Loop through dimensions to multiply their sizes.
            for (uint32_t i = 0; i < t.dimNum; i++) {
                // Update the overall size at each loop.
                if (sizes[0] <= 0) {
                    sizes[0] = t.dimSizes[i];
                } else {
                    sizes[0] *= t.dimSizes[i];
                }
            }

            // Reshape the tensor with the given 1D (flat) shape.
            reshape(t, sizes, 1);

            return error::NO_ERROR;
        }

        // Functors.
        DUnFunc::~DUnFunc(){}
        double Sigmoid::operator() (const double value) {
            return 1 / (1 + exp(-value));
        }
        Sigmoid::~Sigmoid() {}
        double FastSigmoid::operator() (const double value) {
            return 0.5 * value / (1 + abs(value)) + 0.5;
        }
        FastSigmoid::~FastSigmoid() {}
        double ReLu::operator() (const double value) {
            return value > 0.0 ? value : 0.0;
        }
        ReLu::~ReLu(){}
        double HTan::operator() (const double value) {
            return tanh(value);
        }
        HTan::~HTan(){}
        double Identity::operator() (const double value) {
            return value;
        }
        Identity::~Identity(){}
        double BinStep::operator() (const double value) {
            return value >= 0.0 ? 1.0 : 0.0;
        }
        BinStep::~BinStep(){}
        double MSE::operator() (const dtensor1d t1, const dtensor1d t2) {
            double res = 0.0;

            // Sum all squared errors.
            for (uint32_t i = 0; i < t1.width; i++) {
                res += pow(t1.values[i] - t2.values[i], 2);
            }

            // Compute the mean error.
            res /= t1.width;

            return res;
        }

        // Functor operations.
        double der(const double x, DUnFunc* function, const double e) {
            return ((*function)(x + e) - (*function)(x - e)) / (2 * e);
        }
        double der(const double x, DUnFunc* function) {
            return ((*function)(x + 0.01) - (*function)(x - 0.01)) / 0.02;
        }
        double prim(const double x, DUnFunc* function) {
            return (*function)(x);
        }
        error prim(const dtensor1d res, const dtensor1d t, DUnFunc* function) {
            error err = error::NO_ERROR;

            if (t.width == res.width) {
                for (uint32_t i = 0; i < t.width; i++) {
                    res.values[i] = (*function)(t.values[i]);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error prim(const dtensor2d res, const dtensor2d t, DUnFunc* function) {
            error err = error::NO_ERROR;

            if (t.width == res.width &&
                t.height == res.height) {
                for (uint32_t i = 0; i < (t.width * t.height); i++) {
                    res.values[i] = (*function)(t.values[i]);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error prim(const dtensor3d res, const dtensor3d t, DUnFunc* function) {
            error err = error::NO_ERROR;

            if (t.width == res.width &&
                t.height == res.height &&
                t.depth == res.depth) {
                for (uint32_t i = 0; i < (t.width * t.height * t.depth); i++) {
                    res.values[i] = (*function)(t.values[i]);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error der(const dtensor1d res, const dtensor1d t, DUnFunc* function) {
            error err = error::NO_ERROR;

            if (t.width == res.width) {
                for (uint32_t i = 0; i < t.width; i++) {
                    res.values[i] = der(t.values[i], function);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error der(const dtensor2d res, const dtensor2d t, DUnFunc* function) {
            error err = error::NO_ERROR;

            if (t.width == res.width &&
                t.height == res.height) {
                for (uint32_t i = 0; i < (t.width * t.height); i++) {
                    res.values[i] = der(t.values[i], function);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error der(const dtensor3d res, const dtensor3d t, DUnFunc* function) {
            error err = error::NO_ERROR;

            if (t.width == res.width &&
                t.height == res.height &&
                t.depth == res.depth) {
                for (uint32_t i = 0; i < (t.width * t.height * t.depth); i++) {
                    res.values[i] = der(t.values[i], function);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        error der(const dtensor1d res, const dtensor1d t1, const dtensor1d t2, DT1DBinFunc* function) {
            error err = error::NO_ERROR;

            // Check if sizes are correct
            if (res.width == t1.width && t1.width == t2.width) {
                for (uint32_t i = 0; i < res.width; i++) {
                    res.values[i] = der(t1, t2, i, function);
                }
            } else {
                err = error::WRONG_SIZE;
            }

            return err;
        }
        double der(const dtensor1d t1, const dtensor1d t2, const uint32_t i, DT1DBinFunc* function) {
            dtensor1d tLess;
            dtensor1d tMore;
            alloc(&tLess, t1.width);
            alloc(&tMore, t1.width);
            copy(tLess, t1);
            copy(tMore, t1);
            tLess.values[i] -= 0.001;
            tMore.values[i] += 0.001;
            // printf("\nTLESS %f\n", tLess.values[i]);
            // printf("\nTMORE %f\n", tMore.values[i]);
            return ((*function)(tMore, t2) - (*function)(tLess, t2)) / 0.002;
        }
        double prim(const dtensor1d t1, const dtensor1d t2, DT1DBinFunc* function) {
            return (*function)(t1, t2);
        }
    }
}
