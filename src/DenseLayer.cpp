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

    void DenseLayer::backprop() {
        //TODO
    }

    void DenseLayer::print() {
        printf("Inputs %d Outputs %d\n", this->inSize, this->outSize);
        utils::print(this->activatedValues);
    }

    math::dtensor2d DenseLayer::getWeight() {
        return this->weight;
    }

    math::DUnFunc* DenseLayer::getActivationFunction() {
        return this->activationFunction;
    }

    void DenseLayer::setActivationFunction(math::DUnFunc* function) {
        delete this->activationFunction;
        this->activationFunction = function;
    }
}
