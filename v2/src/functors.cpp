#include "functions.h"

namespace oort {
    double Sigmoid::operator() (const double value) {
        return 1 / (1 + exp(-value));
    }
    double FastSigmoid::operator() (const double value) {
        return 0.5 * value / (1 + abs(value)) + 0.5;
    }

    double der(const double value, UnaryFunction* function) {
        return ((*function)(value + 0.01) - (*function)(value - 0.01)) / 0.02;
    }
    double prim(const double value, UnaryFunction* function) {
        return (*function)(value);
    }
}
