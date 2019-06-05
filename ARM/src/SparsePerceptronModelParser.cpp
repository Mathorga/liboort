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
    char buffer[12];
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* declaration;
    rapidxml::xml_node<>* networkNode;
    rapidxml::xml_node<>* neuronsNode;
    rapidxml::xml_node<>* neuronNode;
    rapidxml::xml_node<>* synapsesNode;
    rapidxml::xml_node<>* synapseNode;

    // Append declaration.
    declaration = doc.allocate_node(rapidxml::node_declaration);
    declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(declaration);

    // Append network node.
    networkNode = doc.allocate_node(rapidxml::node_element, "network");
    doc.append_node(networkNode);

    // Append neurons node.
    neuronsNode = doc.allocate_node(rapidxml::node_element, "neurons");
    sprintf(buffer, "%d", this->model->getNeuronsNum());
    neuronsNode->append_attribute(doc.allocate_attribute("num", doc.allocate_string(buffer)));
    sprintf(buffer, "%d", this->model->getInputsNum());
    neuronsNode->append_attribute(doc.allocate_attribute("inputs", doc.allocate_string(buffer)));
    sprintf(buffer, "%d", this->model->getOutputsNum());
    neuronsNode->append_attribute(doc.allocate_attribute("outputs", doc.allocate_string(buffer)));
    networkNode->append_node(neuronsNode);

    // Append a node for each neuron.
    for (neurons_num_t i = 0; i < this->model->getNeuronsNum(); i++) {
        neuronNode = doc.allocate_node(rapidxml::node_element, "neuron");
        sprintf(buffer, "%d", this->model->getNeuron(i)->getId());
        neuronNode->append_attribute(doc.allocate_attribute("id", doc.allocate_string(buffer)));
        sprintf(buffer, "%d", this->model->getNeuron(i)->getType());
        neuronNode->append_attribute(doc.allocate_attribute("type", doc.allocate_string(buffer)));
        neuronsNode->append_node(neuronNode);

        // Append synapses node.
        synapsesNode = doc.allocate_node(rapidxml::node_element, "synapses");
        sprintf(buffer, "%d", this->model->getNeuron(i)->getSynapses()->getSize());
        synapsesNode->append_attribute(doc.allocate_attribute("num", doc.allocate_string(buffer)));
        neuronNode->append_node(synapsesNode);

        // Append a node for each synapse of each neuron.
        for (vector_size_t j = 0; j <this->model->getNeuron(i)->getSynapses()->getSize(); j++) {
            synapseNode = doc.allocate_node(rapidxml::node_element, "synapse");
            sprintf(buffer, "%d", this->model->getNeuron(i)->getSynapse(j)->getInputNeuron()->getId());
            synapseNode->append_attribute(doc.allocate_attribute("input", doc.allocate_string(buffer)));
            sprintf(buffer, "%f", this->model->getNeuron(i)->getSynapse(j)->getWeight());
            synapseNode->append_attribute(doc.allocate_attribute("weight", doc.allocate_string(buffer)));
            neuronNode->append_node(synapseNode);
        }
    }

    // Save to file
    std::ofstream outputFile(fileName);
    // print(outputFile, doc, 0);
    outputFile << doc;
    outputFile.close();
    doc.clear();
}

SparsePerceptronModel* SparsePerceptronModelParser::getModel() {
    return this->model;
}

void SparsePerceptronModelParser::setModel(SparsePerceptronModel* inputModel) {
    this->model = inputModel;
}
