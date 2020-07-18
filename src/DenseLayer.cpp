#include "DenseLayer.h"

namespace oort {
    DenseLayer::DenseLayer(const uint32_t inSize, const uint32_t outSize) : Layer(inSize, outSize) {
        // Allocate weight.
        math::alloc(&(this->weight), inSize, outSize);

        // Allocate bias.
        math::alloc(&(this->bias), outSize);

        // Allocate composed values.
        math::alloc(&(this->composedValues), outSize);

        // Allocate activated values.
        math::alloc(&(this->activatedValues), outSize);

        // Define activation function.
        this->activationFunction = new math::Sigmoid();

        // Randomly init weight and bias.
        math::rinit(this->weight, 1);
        math::rinit(this->bias, 1);
    }

    void DenseLayer::step(math::dtensor input) {
        // Create a temporary flat input tensor.
        math::dtensor1d flatInput;
        math::alloc(&flatInput, this->inSize);

        printf("\nHERE 1\n");

        // Copy input to flat.
        math::copy(flatInput, input);

        printf("\nHERE 2\n");

        // Multiply input to weight to get composed values (without bias).
        math::mul(this->composedValues, this->weight, flatInput);

        printf("\nHERE 3\n");
        utils::print(flatInput);
        utils::print(this->composedValues);

        // Add bias.
        math::add(this->composedValues, this->bias);

        printf("\nHERE 4\n");
        utils::print(this->bias);
        utils::print(this->composedValues);
        utils::print(this->activatedValues);

        // Activate layer.
        math::prim(this->activatedValues, this->composedValues, this->activationFunction);

        printf("\nHERE 5\n");

        // Free temporary tensor.
        math::dealloc(flatInput);

        printf("\nHERE 6\n");
    }

    void DenseLayer::print() {
        printf("Inputs %d Outputs %d\n", this->inSize, this->outSize);
        utils::print(this->composedValues);
    }

    void DenseLayer::setActivationFunction(math::DUnFunc* function) {
        delete this->activationFunction;
        this->activationFunction = function;
    }
}
