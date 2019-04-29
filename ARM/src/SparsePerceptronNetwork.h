#ifndef __SPARSE_PERCEPTRON_NETWORK__
#define __SPARSE_PERCEPTRON_NETWORK__

class SparsePerceptronNetwork : public NeuralNetwork {
public:
    // Constructors.
    SparsePerceptronNetwork();
    SparsePerceptronNetwork(SparsePerceptronModel* model);

    void run();
    void correct();

protected:
    void computeValue();
    void computeError();
    void adjustWeights();
    synapse_weight_t baseWeight;
    neuron_value_t baseValue;
};

#endif
