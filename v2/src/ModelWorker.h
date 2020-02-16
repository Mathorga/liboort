/*
********************************************************************************
ModelWorker.h

Definition of the general class for working on a Model.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __MODEL_WORKER__
#define __MODEL_WORKER__

#include "Model.h"

namespace oort {
    class ModelWorker {
    public:
        // Runs operations on the model.
        // The method needs to be implemented in child classes.
        virtual void run() = 0;

        // Getters.
        // Sets the model.
        Model* getModel();

        // Setters.
        // Returns the model.
        void setModel(Model* model);

    protected:
        Model* model;
    };
}

#endif
