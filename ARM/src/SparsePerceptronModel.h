#ifndef __SPARSE_PERCEPTRON_MODEL__
#define __SPARSE_PERCEPTRON_MODEL__

#include "WeightedModel.h"
#include "Vector.h"
#include "Perceptron.h"

class SparsePerceptronModel : public WeightedModel, public Vector<Perceptron> {
public:
    // Constructors.
    SparsePerceptronModel();
    SparsePerceptronModel(neurons_num_t inputsNum, neurons_num_t outputsNum);

    void print();

    // Getters.
    Perceptron* getNeurons();
};

#endif
