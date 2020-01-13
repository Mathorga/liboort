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
    void matmul(double* result,
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
    void hmatmul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
    void hmatmul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
    void scalmul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = value * matrix[i];
        }
    }
    void scalmul(double* result, double value, double* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = value * matrix[i];
        }
    }
    void sigmoidmat(double* result, double* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = sigmoid(matrix[i]);
        }
    }
}
