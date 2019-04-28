#ifndef __WEIGHTED_MODEL__
#define __WEIGHTED_MODEL__

#include "Model.h"
#include "Synapse.h"

class WeightedModel : public Model {
public:
    Synapse* getSynapses();

private:
    Synapse* synapses;
};

#endif
