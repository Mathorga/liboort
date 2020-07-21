#include "Layer.h"

namespace oort {
    Layer::Layer(const uint32_t inSize, const uint32_t outSize) {
        this->inSize = inSize;
        this->outSize = outSize;
    }

    uint32_t Layer::getInSize() {
        return this->inSize;
    }

    uint32_t Layer::getOutSize() {
        return this->outSize;
    }
}