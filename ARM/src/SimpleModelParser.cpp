#include "SimpleModelParser.h"

void SimpleModelParser::readFile(char* fileName) {
    this->model = new SimpleModel();
    this->perceptronModel = new SparsePerceptronModel();

    rapidxml::file<> modelFile(fileName);
    rapidxml::xml_document<> doc;
    doc.parse<0>(modelFile.data());
    rapidxml::xml_node<>* node = doc.first_node();

    if (strcmp(node->name(), "network") == 0) {
        node = node->first_node();
        if (strcmp(node->name(), "neurons") == 0) {

            // Neurons metadata.
            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                if (strcmp(attr->name(), "num") == 0) {
                    this->model->setNeuronsNum(atoi(attr->value()));
                    this->perceptronModel->setNeuronsNum(atoi(attr->value()));
                } else if (strcmp(attr->name(), "inputs") == 0) {
                    this->model->setInputNum(atoi(attr->value()));
                    this->perceptronModel->setInputsNum(atoi(attr->value()));
                } else if (strcmp(attr->name(), "outputs") == 0) {
                    this->model->setOutputNum(atoi(attr->value()));
                    this->perceptronModel->setOutputsNum(atoi(attr->value()));
                }
            }

            this->model->setNeurons((SimpleModel::_Neuron*) malloc(this->model->getNeuronsNum() * sizeof(SimpleModel::_Neuron)));
            this->perceptronModel->setItems(new Perceptron[this->perceptronModel->getNeuronsNum()], this->perceptronModel->getNeuronsNum());


            // Neurons data.
            node = node->first_node();
            uint16_t position = 0;
            do {
                if (strcmp(node->name(), "neuron") == 0) {
                    // Neuron data.
                    for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                        if (strcmp(attr->name(), "type") == 0) {
                            this->model->getNeurons()[position].type = (SimpleModel::NeuronType) atoi(attr->value());
                        } else if (strcmp(attr->name(), "enabled") == 0) {
                            this->model->getNeurons()[position].enabled = (bool) atoi(attr->value());
                        }
                    }
                }
                position++;
                node = node->next_sibling();
            } while (node);

            if (position != this->model->getNeuronsNum()) {
                //TODO Error.
            }
        }
    }

    node = doc.first_node();
    if (strcmp(node->name(), "network") == 0) {
        node = node->first_node()->next_sibling();
        if (strcmp(node->name(), "synapses") == 0) {

            // Synapses metadata.
            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                if (strcmp(attr->name(), "num") == 0) {
                    this->model->setSynapsesNum(atoi(attr->value()));
                }
            }

            this->model->setSynapses((SimpleModel::_Synapse*) malloc(this->model->getSynapsesNum() * sizeof(SimpleModel::_Synapse)));

            // Synapses data.
            node = node->first_node();
            uint16_t position = 0;
            do {
                if (strcmp(node->name(), "synapse") == 0) {
                    // Synapse data.
                    for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                        if (strcmp(attr->name(), "input") == 0) {
                            this->model->getSynapses()[position].inputNeuron = atoi(attr->value());
                        } else if (strcmp(attr->name(), "output") == 0) {
                            this->model->getSynapses()[position].outputNeuron = atoi(attr->value());
                        } else if (strcmp(attr->name(), "weight") == 0) {
                            this->model->getSynapses()[position].weight = atof(attr->value());
                        } else if (strcmp(attr->name(), "enabled") == 0) {
                            this->model->getSynapses()[position].enabled = (bool) atoi(attr->value());
                        }
                    }
                }
                position++;
                node = node->next_sibling();
            } while (node);

            if (position != this->model->getSynapsesNum()) {
                //TODO Error.
            }
        }
    }
}

void SimpleModelParser::writeFile(char* fileName) {
    char buffer[12];
    rapidxml::xml_document<> doc;

    // Append declaration.
    rapidxml::xml_node<>* declaration = doc.allocate_node(rapidxml::node_declaration);
    declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(declaration);

    // Append network node.
    rapidxml::xml_node<>* networkNode = doc.allocate_node(rapidxml::node_element, "network");
    doc.append_node(networkNode);

    // Append neurons node.
    rapidxml::xml_node<>* neuronsNode = doc.allocate_node(rapidxml::node_element, "neurons");
    sprintf(buffer, "%d", this->model->getNeuronsNum());
    neuronsNode->append_attribute(doc.allocate_attribute("num", doc.allocate_string(buffer)));
    sprintf(buffer, "%d", this->model->getInputNum());
    neuronsNode->append_attribute(doc.allocate_attribute("inputs", doc.allocate_string(buffer)));
    sprintf(buffer, "%d", this->model->getOutputNum());
    neuronsNode->append_attribute(doc.allocate_attribute("outputs", doc.allocate_string(buffer)));
    networkNode->append_node(neuronsNode);

    // Append a node for each neuron.
    for (uint16_t i = 0; i < this->model->getNeuronsNum(); i++) {
        rapidxml::xml_node<>* neuronNode = doc.allocate_node(rapidxml::node_element, "neuron");
        sprintf(buffer, "%d", i);
        neuronNode->append_attribute(doc.allocate_attribute("num", doc.allocate_string(buffer)));
        sprintf(buffer, "%d", this->model->getNeurons()[i].type);
        neuronNode->append_attribute(doc.allocate_attribute("type", doc.allocate_string(buffer)));
        sprintf(buffer, "%d", this->model->getNeurons()[i].enabled);
        neuronNode->append_attribute(doc.allocate_attribute("enabled", doc.allocate_string(buffer)));
        neuronsNode->append_node(neuronNode);
    }

    // Append synapses node.
    rapidxml::xml_node<>* synapsesNode = doc.allocate_node(rapidxml::node_element, "synapses");
    sprintf(buffer, "%d", this->model->getSynapsesNum());
    synapsesNode->append_attribute(doc.allocate_attribute("num", doc.allocate_string(buffer)));
    networkNode->append_node(synapsesNode);

    // Append a node for each synapse.
    for (uint16_t i = 0; i < this->model->getSynapsesNum(); i++) {
        rapidxml::xml_node<>* synapseNode = doc.allocate_node(rapidxml::node_element, "synapse");
        sprintf(buffer, "%d", i);
        synapseNode->append_attribute(doc.allocate_attribute("num", doc.allocate_string(buffer)));
        sprintf(buffer, "%d", this->model->getSynapses()[i].inputNeuron);
        synapseNode->append_attribute(doc.allocate_attribute("input", doc.allocate_string(buffer)));
        sprintf(buffer, "%d", this->model->getSynapses()[i].outputNeuron);
        synapseNode->append_attribute(doc.allocate_attribute("output", doc.allocate_string(buffer)));
        sprintf(buffer, "%f", this->model->getSynapses()[i].weight);
        synapseNode->append_attribute(doc.allocate_attribute("weight", doc.allocate_string(buffer)));
        sprintf(buffer, "%d", this->model->getSynapses()[i].enabled);
        synapseNode->append_attribute(doc.allocate_attribute("enabled", doc.allocate_string(buffer)));
        synapsesNode->append_node(synapseNode);
    }

    // Save to file
    std::ofstream outputFile(fileName);
    // print(outputFile, doc, 0);
    outputFile << doc;
    outputFile.close();
    doc.clear();
}

SimpleModel* SimpleModelParser::getModel() {
    return this->model;
}

void SimpleModelParser::setModel(SimpleModel *inputModel) {
    this->model = inputModel;
}
