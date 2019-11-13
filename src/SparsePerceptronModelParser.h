#ifndef __SPARSE_PERCEPTRON_MODEL_PARSER__
#define __SPARSE_PERCEPTRON_MODEL_PARSER__

#include "ModelParser.h"
#include "SparsePerceptronModel.h"

namespace Oort {
    class SparsePerceptronModelParser : public ModelParser {
    public:
        // Read a Model from a file and store it in this->model.
        void readFile(char* fileName);
        // Write this->model in a file.
        void writeFile(char* fileName);

        // Getters.
        // Returns the Model object set using readFile() or setModel().
        SparsePerceptronModel* getModel();

        // Getters.
        // Sets the Model object in order for it to be written to file or returned.
        void setModel(SparsePerceptronModel* inputModel);

    private:
        SparsePerceptronModel* model;
    };
}

#endif
