#ifndef __SPIKING_MODEL__
#define __SPIKING_MODEL__

#include "Model.h"
#include "SpikingNeuron.h"
#include "utils.h"

namespace Oort {
    class SpikingModel : public Model {
    public:
        SpikingModel();
        // SpikingModel(SpikingNeuron* neurons);

        void print();

        SpikingNeuron* getNeurons();
    };
}

#endif
