#ifndef __SPARSE_PERCEPTRON_NETWORK__
#define __SPARSE_PERCEPTRON_NETWORK__

#define learning_rate_t uint16_t

class SparsePerceptronNetwork : public NeuralNetwork {
public:
    // Constructors.
    SparsePerceptronNetwork();
    SparsePerceptronNetwork(SparsePerceptronModel* model);

    void run();
    void correct();

protected:
    synapse_weight_t baseWeight;
    neuron_value_t baseValue;
    learning_rate_t learningRate;

    void computeValue();
    void computeError();
    void adjustWeights();
};

#endif
