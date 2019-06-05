/*
********************************************************************************
ModelParser.h

This file defines a parser (reader and writer) of a Model object.
Assign a Model object using setModel() before writing it to a file.
Use getModel() after reading a file to get the parsed Model object.
Copyright (C) 2019  Luka Micheletti

********************************************************************************
*/

#ifndef __MODEL_PARSER__
#define __MODEL_PARSER__

#include "utils.h"
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"
#include "../lib/rapidxml-1.13/rapidxml_print.hpp"

class ModelParser {
public:
    // Read a Model from a file and store it in this->model.
    virtual void readFile(char *fileName) = 0;
    // Write this->model in a file.
    virtual void writeFile(char *fileName) = 0;
};

#endif