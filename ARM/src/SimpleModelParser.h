/*
********************************************************************************
ModelParser.h

This file defines a parser (reader and writer) of a Model object.
Assign a Model object using setModel() before writing it to a file.
Use getModel() after reading a file to get the parsed Model object.
Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __SIMPLE_MODEL_PARSER__
#define __SIMPLE_MODEL_PARSER__

#include "SimpleModel.h"
#include "SparsePerceptronModel.h"
#include "utils.h"
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"
#include "../lib/rapidxml-1.13/rapidxml_print.hpp"

class SimpleModelParser {
public:
    // Read a Model from a file and store it in this->model.
    void readFile(char *fileName);
    // Write this->model in a file.
    void writeFile(char *fileName);

    // Returns the Model object set using readFile() or setModel().
    SimpleModel *getModel();
    // Sets the Model object in order for it to be written to file or returned.
    void setModel(SimpleModel *inputModel);

private:
    SimpleModel *model;
    SparsePerceptronModel* perceptronModel;
};

#endif
