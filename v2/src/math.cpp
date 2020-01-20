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
        error add(const dtensor1d res, const dtensor1d t1, const dtensor1d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width) {
                for (uint32_t i = 0; i < res.width; i++) {
                    res.values[i] = t1.values[i] * t2.values[i];
                }
            }
            return err;
        }
        error add(const dtensor2d res, const dtensor2d t1, const dtensor2d t2) {
            error err = error::NO_ERROR;
            if (t1.width == t2.width && res.width == t2.width &&
                t1.height == t2.height && res.height == t2.height) {
                for (uint32_t i = 0; i < res.width * res.height; i++) {
                    res.values[i] = t1.values[i] * t2.values[i];
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
                    res.values[i] = t1.values[i] * t2.values[i];
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
        template <typename T>
        error alloc(tensor1d<T>* t, const uint32_t width) {
            t->width = width;
            t->values = (T*) malloc(width * sizeof(T));
            return error::NO_ERROR;
        }
        // template <typename T>
        // error alloc(tensor2d<T>* t, const uint32_t width, const uint32_t height) {
        //     t->width = width;
        //     t->height = height;
        //     t->values = (T*) malloc(width * height * sizeof(T));
        //     return error::NO_ERROR;
        // }
        template <typename T>
        error alloc(tensor3d<T>* t, const uint32_t width, const uint32_t height, const uint32_t depth) {
            t->width = width;
            t->height = height;
            t->depth = depth;
            t->values = (T*) malloc(width * height * depth * sizeof(T));
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

        double der(const double value, UnaryFunction* function, const double epsilon) {
            return ((*function)(value + epsilon) - (*function)(value - epsilon)) / (2 * epsilon);
        }
        double der(const double value, UnaryFunction* function) {
            return ((*function)(value + 0.01) - (*function)(value - 0.01)) / 0.02;
        }
        double prim(const double value, UnaryFunction* function) {
            return (*function)(value);
        }
    }
}
