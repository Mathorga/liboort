#ifndef __LAYERED_PERCEPTRON_MODEL__
#define __LAYERED_PERCEPTRON_MODEL__

#include "Model.h"
#include "Vector.h"
#include "Perceptron.h"

class LayeredPerceptronModel : public Model {
public:
    static const vector_size_t DEFAULT_LAYERS_NUM;
    static const vector_size_t DEFAULT_OUT_LAYERS_NUM;
    static const vector_size_t DEFAULT_LAYER_SIZE;

    // Constructors.
    LayeredPerceptronModel();
    LayeredPerceptronModel(vector_size_t layersNum);
    LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize);

    void print();

    // Getters.
    Vector<Vector<Perceptron>>* getLayersVector();
    Vector<Perceptron>* getLayer(vector_size_t index);

private:
    vector_size_t layersNum;
    vector_size_t outputLayersNum;
    Vector<Vector<Perceptron>>* layers;

    void defaultInit(vector_size_t layerSize);
};

#endif
