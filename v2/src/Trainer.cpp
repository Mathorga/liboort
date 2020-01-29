#include "Trainer.h"

namespace oort {
    // Getters.
    Model* Trainer::getModel() {
        return this->model;
    }

    // Setters.
    void Trainer::setModel(Model* model) {
        this->model = model;
    }
}
