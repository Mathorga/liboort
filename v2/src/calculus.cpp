#include "calculus.h"

namespace oort {
    double sigmoid(double value) {
        return 1 / (1 + exp(-value));
    }
    double fSigmoid(double value) {
        return 0.5 * value / (1 + abs(value)) + 0.5;
    }
}
