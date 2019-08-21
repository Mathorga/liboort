/*
********************************************************************************
Nerve.h

This file defines the interface for simple generic communication.

Copyright (C) 2019  Luka Micheletti
********************************************************************************
*/

#ifndef __NERVE__
#define __NERVE__

#include "utils.h"

namespace Oort {
    class Nerve {
    public:
        // Destructor.
        virtual ~Nerve() = default;

        // Transmit data.
        virtual int32_t send(byte* data, uint32_t length) = 0;

        // Receive data.
        virtual int32_t receive(byte* buffer, uint32_t length) = 0;
    };
}

#endif
