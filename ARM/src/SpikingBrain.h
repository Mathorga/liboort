#ifndef __SPIKING_BRAIN__
#define __SPIKING_BRAIN__

#include "SpikingModel.h"
#include "utils.h"

class SpikingBrain {
public:
    SpikingBrain(SpikingModel *inputModel);
    virtual void run() = 0;
};

#endif
