#include "SparsePerceptronModelParser.h"

// Read a Model from a file and store it in this->model.
void SparsePerceptronModelParser::readFile(char *fileName) {
    this->model = new SparsePerceptronModel();
    neurons_num_t neuronId = 0;
    Neuron::NeuronType neuronType = Neuron::typeInput;
    vector_size_t neuronPosition = 0;
    vector_size_t synapsePosition = 0;
    Perceptron* neuron = NULL;
    Perceptron* tmpNeuron(0);
    neurons_num_t synapseInput = 0;
    synapse_weight_t synapseWeight = 0.0;

    rapidxml::file<> modelFile(fileName);
    rapidxml::xml_document<> doc;
    doc.parse<0>(modelFile.data());
    rapidxml::xml_node<>* node = doc.first_node();
    rapidxml::xml_node<>* neuronsNode;
    rapidxml::xml_node<>* neuronNode;
    rapidxml::xml_node<>* synapseNode;

    if (strcmp(node->name(), "network") == 0) {
        node = node->first_node();
        if (strcmp(node->name(), "neurons") == 0) {

            // Neurons metadata.
            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                if (strcmp(attr->name(), "num") == 0) {
                    this->model->setNeuronsNum(atoi(attr->value()));
                } else if (strcmp(attr->name(), "inputs") == 0) {
                    this->model->setInputsNum(atoi(attr->value()));
                } else if (strcmp(attr->name(), "outputs") == 0) {
                    this->model->setOutputsNum(atoi(attr->value()));
                }
            }

            this->model->createNeurons();

            // Neurons data.
            neuronsNode = node->first_node();
            while (neuronsNode) {
                if (strcmp(neuronsNode->name(), "neuron") == 0) {
                    // Neuron data.
                    for (rapidxml::xml_attribute<>* attr = neuronsNode->first_attribute(); attr; attr = attr->next_attribute()) {
                        if (strcmp(attr->name(), "id") == 0) {
                            neuronId = atoi(attr->value());
                        } else if (strcmp(attr->name(), "type") == 0) {
                            neuronType = (Neuron::NeuronType) atoi(attr->value());
                        }
                    }

                    neuron = new Perceptron(neuronId, Perceptron::DEFAULT_VALUE, neuronType);

                    neuronNode = neuronsNode->first_node();
                    if (strcmp(neuronNode->name(), "synapses") == 0) {
                        // Synapses metadata.
                        for (rapidxml::xml_attribute<>* attr = neuronNode->first_attribute(); attr; attr = attr->next_attribute()) {
                            if (strcmp(attr->name(), "num") == 0) {
                                // Set synapses num.
                                // Not needed.
                            }
                        }
                    }
                    synapseNode = neuronNode->first_node();
                    while (synapseNode) {
                        if (strcmp(synapseNode->name(), "synapse") == 0) {
                            // Synapse data.
                            for (rapidxml::xml_attribute<>* attr = synapseNode->first_attribute(); attr; attr = attr->next_attribute()) {
                                if (strcmp(attr->name(), "input") == 0) {
                                    synapseInput = atoi(attr->value());
                                } else if (strcmp(attr->name(), "weight") == 0) {
                                    synapseWeight = atof(attr->value());
                                }
                            }
                        }
                        tmpNeuron = this->model->getNeuronById(synapseInput);
                        neuron->getSynapses()->addLast(new PerceptronSynapse(tmpNeuron, synapseWeight));
                        synapsePosition++;
                        synapseNode = synapseNode->next_sibling();
                    }
                }
                this->model->replaceNeuron(neuron);
                neuronPosition++;
                neuronsNode = neuronsNode->next_sibling();
            }

            if (neuronPosition != this->model->getNeuronsNum()) {
                //TODO Error.
            }
        }
    }
}

void SparsePerceptronModelParser::writeFile(char *fileName) {

}

SparsePerceptronModel* SparsePerceptronModelParser::getModel() {
    return this->model;
}

void SparsePerceptronModelParser::setModel(SparsePerceptronModel* inputModel) {
    this->model = inputModel;
}
