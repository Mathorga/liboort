#include "DenseLayer.h"

namespace oort {
    DenseLayer::DenseLayer(const uint32_t inSize, const uint32_t outSize) : Layer(inSize, outSize) {
        math::alloc(&(this->weight), inSize, outSize);
        math::alloc(&(this->bias), outSize);
        math::alloc(&(this->composedValues), outSize);
        math::alloc(&(this->activatedValues), outSize);
    }

    void DenseLayer::step(math::dtensor input) {
        // Create a temporary flat input tensor.
        math::dtensor1d flatInput;
        math::alloc(&flatInput, this->inSize);

        // Copy input to flat.
        math::copy(flatInput, input);

        // Multiply input to weight to get composed values (without bias).
        math::mul(this->composedValues, this->weight, flatInput);

        // Add bias.
        math::add(this->composedValues, this->bias);

        // Activate layer.
        math::prim(this->activatedValues, this->composedValues, this->activationFunction);

        // Free temporary tensor.
        math::dealloc(flatInput);
    }

    void DenseLayer::print() {
        printf("Inputs %d Outputs %d\n", this->inSize, this->outSize);
        utils::print(this->composedValues);
    }
}
