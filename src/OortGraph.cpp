#include "utils.h"

using namespace Oort;

int main(int argc, char const *argv[]) {

    double* first = (double*) malloc(6 * sizeof(double));
    double* second = (double*) malloc(12 * sizeof(double));

    for (uint32_t i = 0; i < 6; i++) {
        first[i] = i + 1;
    }

    for (uint32_t i = 0; i < 12; i++) {
        second[i] = i + 1;
    }

    double* result = (double*) malloc(8 * sizeof(double));

    fMatMul(result,
            first, 2, 3,
            second, 3, 4);

    for (uint32_t i = 0; i < 8; i++) {
        printf("%f ", result[i]);
    }
    printf("\n");

    return 0;
}
