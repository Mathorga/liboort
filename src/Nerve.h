#ifndef __NERVE__
#define __NERVE__

namespace Oort {
    class Nerve {
    public:
        virtual int sendMessage() = 0;
        virtual char *getMessage() = 0;
    };
}

#endif
