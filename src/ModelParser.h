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

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"
#include "../lib/rapidxml-1.13/rapidxml_print.hpp"
#include "Parser.h"

namespace Oort {
    class ModelParser : public Parser {};
}

#endif
