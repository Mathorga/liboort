/*
********************************************************************************
Trainer.h

Definition of the general class for training models.

Copyright (C) 2020  Luka Micheletti
********************************************************************************
*/

#ifndef __TRAINER__
#define __TRAINER__

#include "Model.h"

namespace oort {
    class Trainer {
    public:
        // Optimizes the model.
        // The method needs to be implemented in child classes.
        virtual void run() = 0;

        // Getters.
        // Sets the model.
        Model* getModel();

        // Setters.
        // Returns the model.
        void setModel(Model* model);

    private:
        Model* model;
    };
}

#endif
