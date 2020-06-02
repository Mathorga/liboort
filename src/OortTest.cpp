#include "Model.h"
#include "GradientDescender.h"
#include "Knowledge.h"

using namespace oort;

int main(int argc, char const *argv[]) {

    tensor::dtensor t0;
    uint32_t dims[] = {2, 2, 2, 2};
    tensor::alloc(&t0, dims, 4);
    tensor::rinit(t0, 1000.0);

    print(t0);

    return 0;
}
