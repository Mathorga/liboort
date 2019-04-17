#include "SpikingBrain.h"

SimpleBrain::SimpleBrain(SpikingModel *inputModel) {
    this->model = inputModel;
}

void SpikingBrain::run() {
    // Loop through neurons.
    for (uint32_t i = 0; i < this->model->getNeuronsNum(); i++) {
        // Compute value.
        for (uint8_t j = 0; j < this->model->getNeurons()[i].inputs.size; j++) {
            if (this->model->getNeurons()[this->model->getNeurons()[i].inputs[j]].outState) {
                // Increment neuron value.
                this->model->getNeurons()[i].value += 10;
            }
        }
        if (this->model->getNeurons()[i].value >= this->model->getNeurons()[i].threshold) {
            // Fire.
            this->model->getNeurons()[i].state = true;
        }
    }

    // Update neurons' activations.
    for (uint32_t i = 0; j < this->model->getNeuronsNum(); i++) {
        this->model->getSynapses()[j].outState = this->model->getSynapses()[j].state;
    }
}
