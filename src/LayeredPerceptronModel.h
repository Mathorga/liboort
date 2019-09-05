/*
**************************************************************************
LayeredPerceptronModel.h

This class implements a fully connected layered perceptron model.
This model is not supposed to grow over time, so it does not expose
methods for changing its structure after its creation.

Copyright (C) 2019  Luka Micheletti
**************************************************************************
*/

#ifndef __LAYERED_PERCEPTRON_MODEL__
#define __LAYERED_PERCEPTRON_MODEL__

#include "Model.h"
#include "Vector.h"
#include "Perceptron.h"

namespace Oort {
    class LayeredPerceptronModel : public Model {
    public:
        static const vector_size_t DEFAULT_LAYERS_NUM;

        // Output layers can be more than one, so a default output layers number is defined.
        static const vector_size_t DEFAULT_OUT_LAYERS_NUM;
        static const vector_size_t DEFAULT_LAYER_SIZE;

        // Constructors.
        // Fixed size constructors: layer sizes are constant throughout the network. If not specified, the default layer
        // size is used.
        LayeredPerceptronModel();
        LayeredPerceptronModel(vector_size_t layersNum);
        LayeredPerceptronModel(vector_size_t layersNum, vector_size_t layerSize);
        LayeredPerceptronModel(vector_size_t layersNum, vector_size_t outputLayersNum, vector_size_t layerSize);

        // Variable size constructors: layer sizes are specified by a Vector of size equal to layers number.
        LayeredPerceptronModel(vector_size_t layersNum, Vector<vector_size_t>* layerSizes);
        LayeredPerceptronModel(vector_size_t layersNum, vector_size_t outputLayersNum, Vector<vector_size_t>* layerSizes);

        void print();

        // Getters.
        Vector<Vector<Perceptron>>* getLayersVector();
        Vector<Perceptron>* getLayer(vector_size_t index);
        vector_size_t getLayersNum();
        vector_size_t getOutputLayersNum();

    private:
        vector_size_t layersNum;
        vector_size_t outputLayersNum;
        Vector<Vector<Perceptron>>* layers;

        void createLayers(vector_size_t layerSize);
        void createLayers(vector_size_t inputLayerSize, vector_size_t outputLayerSize, vector_size_t hiddenLayerSize);
        void createLayers(Vector<vector_size_t>* layerSizes);
    };
}

#endif
