#ifndef __SPARSE_PERCEPTRON_MODEL__
#define __SPARSE_PERCEPTRON_MODEL__

#include "Model.h"
#include "Vector.h"
#include "Perceptron.h"

class SparsePerceptronModel : public Model {//, public Vector<Perceptron> {
public:
    // Constructors.
    SparsePerceptronModel();
    SparsePerceptronModel(vector_size_t inputsNum, vector_size_t outputsNum);
    SparsePerceptronModel(vector_size_t inputsNum, vector_size_t outputsNum, bool createSynapses);

    void print();
    void createNeurons();
    void replaceNeuron(Perceptron* neuron);

    // Getters.
    Vector<Perceptron>* getNeuronsVector();
    Perceptron* getNeurons();
    Perceptron* getNeuron(vector_size_t index);
    Perceptron* getNeuronById(vector_size_t id);

private:
    Vector<Perceptron>* perceptrons;
};

#endif
