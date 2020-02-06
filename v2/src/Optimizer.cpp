#include "Optimizer.h"

namespace oort {
    // Getters.
    Model* Optimizer::getModel() {
        return this->model;
    }

    // Setters.
    void Optimizer::setModel(Model* model) {
        this->model = model;
    }
}
