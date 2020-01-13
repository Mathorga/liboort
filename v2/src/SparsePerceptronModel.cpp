#include "SparsePerceptronModel.h"

namespace Oort {
    SparsePerceptronModel::SparsePerceptronModel() {
        this->inputsNum = 0;
        this->hiddensNum = 0;
        this->outputsNum = 0;
        this->neuronsNum = 0;
        this->perceptrons = new Vector<Perceptron>();
    }

    SparsePerceptronModel::SparsePerceptronModel(vector_size_t inputsNum, vector_size_t outputsNum) {
        this->inputsNum = inputsNum;
        this->hiddensNum = 0;
        this->outputsNum = outputsNum;
        this->neuronsNum = this->inputsNum + this->hiddensNum + this->outputsNum;

        // Create neurons.
        this->perceptrons = new Vector<Perceptron>();
        for (vector_size_t i = 0; i < this->neuronsNum; i++) {
            this->perceptrons->addLast(new Perceptron(i, Perceptron::DEFAULT_VALUE, i < inputsNum ? Neuron::typeInput : Neuron::typeOutput));
        }
    }

    SparsePerceptronModel::SparsePerceptronModel(vector_size_t inputsNum, vector_size_t outputsNum, bool createSynapses) : SparsePerceptronModel(inputsNum, outputsNum) {
        if (createSynapses) {
            // Create synapses.
            for (vector_size_t i = this->inputsNum; i < this->neuronsNum; i++) {
                for (vector_size_t j = 0; j < this->inputsNum; j++) {
                    this->perceptrons->getItem(i)->getSynapses()->addLast(new PerceptronSynapse(&(this->perceptrons->getItems()[j]), PerceptronSynapse::DEFAULT_WEIGHT));
                    // this->items[i].getSynapses()->addLast(new PerceptronSynapse(&(this->items[j]), PerceptronSynapse::DEFAULT_WEIGHT));
                }
            }
        }
    }

    void SparsePerceptronModel::createNeurons() {
        if (this->perceptrons == NULL) {
            this->perceptrons = new Vector<Perceptron>();
        } else if (this->perceptrons->getSize() == 0) {
            for (vector_size_t i = 0; i < this->neuronsNum; i++) {
                this->perceptrons->addLast(new Perceptron(i, Perceptron::DEFAULT_VALUE, i < inputsNum ? Neuron::typeInput : Neuron::typeOutput));
            }
        } else {
            debugPrint("Error creating neurons: neurons alredy created");
        }
    }

    void SparsePerceptronModel::replaceNeuron(Perceptron* neuron) {
        for (vector_size_t i = 0; i < this->neuronsNum; i++) {
            if (this->perceptrons->getItem(i)->getId() == neuron->getId()) {
                this->perceptrons->replaceAt(neuron, i);
                return;
            }
        }
        printf("\nNeuron not present\n");
    }

    void SparsePerceptronModel::print() {
        printf("\n|------------SPARSE_PERCEPTRON_MODEL------------\n");
        printf("|Size %d\n", this->neuronsNum);
        printf("|-----------------------------------------------\n");

        for (vector_size_t i = 0; i < this->neuronsNum; i++) {
            this->perceptrons->getItem(i)->print();
            printf("|-----------------------------------------------\n");
        }
        printf("\n");
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

    Perceptron* SparsePerceptronModel::getPerceptron(vector_size_t id) {
        Perceptron* result = nullptr;

        for (vector_size_t i = 0; i < this->neuronsNum; i++) {
            if (this->perceptrons->getItem(i)->getId() == id) {
                result = this->perceptrons->getItem(i);
                break;
            }
        }
        return result;
    }
}
