#ifndef __NERVE__
#define __NERVE__

class Nerve {
public:
    virtual int sendMessage() = 0;
    virtual char *getMessage() = 0;
};

#endif
