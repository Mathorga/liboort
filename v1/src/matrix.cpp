#include "matrix.h"

namespace oort {
    void matMul(double* result,
                double* firstMatrix, uint32_t firstRowsNum, uint32_t firstColsNum,
                double* secondMatrix, uint32_t secondRowsNum, uint32_t secondColsNum) {
        for (uint32_t i = 0; i < firstRowsNum; i++) {
            for (uint32_t j = 0; j < secondColsNum; j++) {
                result[IDX(i, j, secondColsNum)] = 0.0;
                for (uint32_t k = 0; k < firstColsNum; k++) {
                    result[IDX(i, j, secondColsNum)] += firstMatrix[IDX(i, k, firstColsNum)] * secondMatrix[IDX(k, j, secondColsNum)];
                }
            }
        }
    }
    void hMatMul(uint32_t* result, uint32_t* firstMatrix, uint32_t* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
    void hMatMul(double* result, double* firstMatrix, double* secondMatrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = firstMatrix[i] * secondMatrix[i];
        }
    }
    void scalMul(uint32_t* result, uint32_t value, uint32_t* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = value * matrix[i];
        }
    }
    void scalMul(double* result, double value, double* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = value * matrix[i];
        }
    }
    void sigmoidMat(double* result, double* matrix, uint32_t matrixSize) {
        for (uint32_t i = 0; i < matrixSize; i++) {
            result[i] = sigmoid(matrix[i]);
        }
    }
}
