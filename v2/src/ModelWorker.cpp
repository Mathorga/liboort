#include "ModelWorker.h"

namespace oort {
    // Getters.
    Model* ModelWorker::getModel() {
        return this->model;
    }

    // Setters.
    void ModelWorker::setModel(Model* model) {
        this->model = model;
    }
}
