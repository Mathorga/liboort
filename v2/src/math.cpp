#include "math.h"

namespace oort {
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
    void mul(double* result,
             double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
             double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum) {
        for (uint32_t i = 0; i < firstRowsNum; i++) {
            for (uint32_t j = 0; j < secondColsNum; j++) {
                result[IDX2D(i, j, secondColsNum)] = 0.0;
                for (uint32_t k = 0; k < firstColsNum; k++) {
                    result[IDX2D(i, j, secondColsNum)] += firstMatrix[IDX2D(i, k, firstColsNum)] * secondMatrix[IDX2D(k, j, secondColsNum)];
                }
            }
        }
    }
    void mul(const dtensor2d result, const dtensor2d t1, const dtensor2d t2) {
        if (t1.height == t2.width) {
            for (uint32_t i = 0; i < t1.height; i++) {
                for (uint32_t j = 0; j < t2.width; j++) {
                    result.values[IDX2D(i, j, t2.width)] = 0.0;
                    for (uint32_t k = 0; k < t1.width; k++) {
                        result.values[IDX2D(i, j, t2.width)] += t1.values[IDX2D(i, k, t1.width)] * t2.values[IDX2D(k, j, t2.width)];
                    }
                }
            }
        }
    }
    void hmul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
    void hmul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
    void hmul(const dtensor2d result, const dtensor2d t1, const dtensor2d t2) {
        if (t1.width == t2.width && result.width == t2.width &&
            t1.height == t2.height && result.height == t2.height) {
            for (uint32_t i = 0; i < result.width * result.height; i++) {
                result.values[i] = t1.values[i] * t2.values[i];
            }
        }
    }
    void smul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = value * matrix[i];
        }
    }
    void smul(double* result, double value, double* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = value * matrix[i];
        }
    }
    void smul(const dtensor2d result, const double value, const dtensor2d t) {
        for (uint32_t i = 0; i < t.width * t.height; i++) {
            result.values[i] = value * t.values[i];
        }
    }
    void sigmoid(double* result, double* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = sigmoid(matrix[i]);
        }
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
