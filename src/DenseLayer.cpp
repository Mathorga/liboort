#include "DenseLayer.h"

namespace oort {
    DenseLayer::DenseLayer(const uint32_t inSize, const uint32_t outSize) {
        math::alloc(&(this->weight), inSize, outSize);
        math::alloc(&(this->bias), outSize);
        math::alloc(&(this->composedValues), );
    }
    void DenseLayer::step(math::dtensor input) {
        math::dtensor flat;
        math::flatten(flat, input);
    }
}
