/*
**************************************************************************
LayeredPerceptronModel.h

This class implements a fully connected layered perceptron model.
This model is not supposed to grow over time, so it does not expose
methods for changing its structure after its creation.
The model is made of at least one input layer and one output layer; the
number of hidden layers may vary from 0 to

Copyright (C) 2019  Luka Micheletti
**************************************************************************
*/

#ifndef __LAYERED_PERCEPTRON_MODEL__
#define __LAYERED_PERCEPTRON_MODEL__

#include "PerceptronModel.h"
#include "Vector.h"

namespace Oort {
    class LayeredPerceptronModel : public PerceptronModel {
    public:
        // Default layers number, used for empty constructor.
        static const vector_size_t DEFAULT_LAYERS_NUM;

        // Default layer size, used for fixed size constructors, when layer size is not specified.
        static const vector_size_t DEFAULT_LAYER_SIZE;

        // Constructors.
        // Fixed size constructors.
        // Layer sizes are constant throughout the network. If not specified, the default layer size is used.
        LayeredPerceptronModel();
        LayeredPerceptronModel(vector_size_t layersNum);
        LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize);

        // Variable size constructors.
        // Layer sizes are specified by an array of <layersNum> elements.
        LayeredPerceptronModel(vector_size_t layersNum, vector_size_t* layerSizes);
        // Layer sizes are specified by a Vector of size equal to layers number.
        LayeredPerceptronModel(Vector<vector_size_t>* layerSizes);

        void print();

        // Getters.
        // Returns the whole vector of layers of the model.
        Vector<Vector<Perceptron>>* getLayersVector();

        // Returns the index-th layer in the model.
        Vector<Perceptron>* getLayer(vector_size_t index);

        // Returns the first (input) layer in the model.
        Vector<Perceptron>* getInputLayer();

        // Returns the last (output) layer in the model.
        Vector<Perceptron>* getOutputLayer();

        // Returns the index-th hidden layer in the model, therefore index does not consider input layer.
        Vector<Perceptron>* getHiddenLayer(vector_size_t index);
        vector_size_t getLayersNum();
        Perceptron* getPerceptron(vector_size_t id);
        Perceptron* getNeurons();

    private:
        vector_size_t layersNum;
        Vector<Vector<Perceptron>>* layers;

        void createLayers(vector_size_t layerSize);
        // void createLayers(vector_size_t inputLayerSize, vector_size_t outputLayerSize, vector_size_t hiddenLayerSize);
        void createLayers(Vector<vector_size_t>* layerSizes);
    };
}

#endif
