/*
**************************************************************************
LayeredPerceptronModelParser.h

Implementation for parser of Layered Model files (.mdl + .mdl.lyr).
The Model Layer file is necessary for LayeredPerceptronModels, in order to
separate the weights of the synapses (inside the .mdl file) and the layer
structure of the model (inside the .mdl.lyr file).
In order to be parsed from file, a LayeredPerceptronModel needs to be
saved in two files with the same name: one with .mdl extension and the
other with .mdl.lyr extension.
Model Layer files (.mdl.lyr) specification defines a header made of four
bytes, which define the number of layers for the model.
The header is followed by a number of layer sizes equal to its value.
Each size is four bytes long and directly represents a layer size.
Model files use big-endian encoding for values.
For example, let's take a file containing the following bytes:
00    00    00    03    00    00    05    10    00    00    00    0A
00    00    00    03
The file contains a layer specification that defines a model with three
layers, respectively of size 00000510 (1296), 0000000A (10) and 00000003
(3).

Copyright (C) 2019  Luka Micheletti
**************************************************************************
*/

#ifndef __LAYERED_PERCEPTRON_MODEL_PARSER__
#define __LAYERED_PERCEPTRON_MODEL_PARSER__

#include "ModelParser.h"
#include "LayeredPerceptronModel.h"

namespace Oort {
    class LayeredPerceptronModelParser : public ModelParser {
    public:
        // Read a Model from a file and store it in this->model.
        void readFile(char* fileName);
        // Write this->model in a file.
        void writeFile(char* fileName);

        // Getters.
        // Returns the Model object set using readFile() or setModel().
        LayeredPerceptronModel* getModel();

        // Getters.
        // Sets the Model object in order for it to be written to file or returned.
        void setModel(LayeredPerceptronModel* inputModel);

    private:
        LayeredPerceptronModel* model;
    };
}

#endif
