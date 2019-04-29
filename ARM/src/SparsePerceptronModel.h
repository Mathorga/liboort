#ifndef __SPARSE_PERCEPTRON_MODEL__
#define __SPARSE_PERCEPTRON_MODEL__

#include "WeightedModel.h"
#include "Perceptron.h"

class SparsePerceptronModel : public WeightedModel {
public:
    // Constructors.
    SparsePerceptronModel();

    void print();

};

#endif
