#ifndef __LAYERED_PERCEPTRON_MODEL__
#define __LAYERED_PERCEPTRON_MODEL__

#include "WeightedModel.h"
#include "Vector.h"
#include "Perceptron.h"

class LayeredPerceptronModel : public Model {
public:
    static vector_size_t defaultLayersNum;
    static vector_size_t defaultLayerSize;

    // Constructors.
    LayeredPerceptronModel();
    LayeredPerceptronModel(vector_size_t layersNum);
    LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize);

    void print();

    // Getters.
    Vector<Vector<Perceptron>>* getLayersVector();
    Vector<Perceptron>* getLayer(vector_size_t index);

private:
    vector_size_t outputLayersNum;
    Vector<Vector<Perceptron>>* layers;
};

#endif
