#include "Layer.h"

namespace oort {
    Layer::Layer(const uint32_t inSize, const uint32_t outSize) {
        this->inSize = inSize;
        this->outSize = outSize;
    }
}