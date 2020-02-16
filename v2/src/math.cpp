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

        double Sigmoid::operator() (const double value) {
            return 1 / (1 + exp(-value));
        }
        double FastSigmoid::operator() (const double value) {
            return 0.5 * value / (1 + abs(value)) + 0.5;
        }

        double der(const double x, DUnaryFunction* function, const double e) {
            return ((*function)(x + e) - (*function)(x - e)) / (2 * e);
        }
        double der(const double x, DUnaryFunction* function) {
            return ((*function)(x + 0.01) - (*function)(x - 0.01)) / 0.02;
        }
        double prim(const double x, DUnaryFunction* function) {
            return (*function)(x);
        }
        error prim(const dtensor1d res, const dtensor1d t, DUnaryFunction* function) {
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
        error prim(const dtensor2d res, const dtensor2d t, DUnaryFunction* function) {
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
        error prim(const dtensor3d res, const dtensor3d t, DUnaryFunction* function) {
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
    }
}
