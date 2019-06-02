#include "SparsePerceptronModel.h"

SparsePerceptronModel::SparsePerceptronModel() {
    this->inputsNum = 0;
    this->hiddensNum = 0;
    this->outputsNum = 0;
    this->neuronsNum = 0;
    this->perceptrons = new Vector<Perceptron>();
}

SparsePerceptronModel::SparsePerceptronModel(neurons_num_t inputsNum, neurons_num_t outputsNum) {
    this->inputsNum = inputsNum;
    this->hiddensNum = 0;
    this->outputsNum = outputsNum;
    this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;

    // Create neurons.
    this->perceptrons = new Vector<Perceptron>();
    for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
        this->perceptrons->addLast(new Perceptron(i, Perceptron::DEFAULT_VALUE, i < inputsNum ? Neuron::typeInput : Neuron::typeOutput));
    }
}

SparsePerceptronModel::SparsePerceptronModel(neurons_num_t inputsNum, neurons_num_t outputsNum, bool createSynapses) : SparsePerceptronModel(inputsNum, outputsNum) {
    if (createSynapses) {
        // Create synapses.
        for (neurons_num_t i = this->inputsNum; i < this->neuronsNum; i++) {
            for (neurons_num_t j = 0; j < this->inputsNum; j++) {
                this->perceptrons->getItem(i)->getSynapses()->addLast(new PerceptronSynapse(&(this->perceptrons->getItems()[j]), PerceptronSynapse::defaultWeight));
                // this->items[i].getSynapses()->addLast(new PerceptronSynapse(&(this->items[j]), PerceptronSynapse::defaultWeight));
            }
        }
    }
}

void SparsePerceptronModel::createNeurons() {
    if (this->perceptrons == NULL) {
        this->perceptrons = new Vector<Perceptron>();
    } else if (this->perceptrons->getSize() == 0) {
        for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
            this->perceptrons->addLast(new Perceptron(i, Perceptron::DEFAULT_VALUE, i < inputsNum ? Neuron::typeInput : Neuron::typeOutput));
        }
    } else {
        debugPrint("Error creating neurons: neurons alredy created");
    }
}

void SparsePerceptronModel::replaceNeuron(Perceptron* neuron) {
    for (neurons_num_t i = 0; i < this->neuronsNum; i++) {
        if (this->perceptrons->getItem(i)->getId() == neuron->getId()) {
            this->perceptrons->replaceAt(neuron, i);
            return;
        }
    }
    printf("\nNeuron not present\n");
}

void SparsePerceptronModel::print() {
    printf("\n|------------SPARSE_PERCEPTRON_MODEL------------|");
    printf("\n|Size %d\t\t\t\t\t\t|\n", this->neuronsNum);

    for (vector_size_t i = 0; i < this->neuronsNum; i++) {
        this->perceptrons->getItem(i)->print();
    }
    printf("|_______________________________________________|\n\n");
}

Perceptron* SparsePerceptronModel::getNeurons() {
    return this->perceptrons->getItems();
}

Vector<Perceptron>* SparsePerceptronModel::getNeuronsVector() {
    return this->perceptrons;
}

Perceptron* SparsePerceptronModel::getNeuron(vector_size_t index) {
    return this->perceptrons->getItem(index);
}

Perceptron* SparsePerceptronModel::getNeuronById(neurons_num_t id) {
    for (vector_size_t i = 0; i < this->neuronsNum; i++) {
        if (this->perceptrons->getItem(i)->getId() == id) {
            return this->perceptrons->getItem(i);
        }
    }
    return NULL;
}
