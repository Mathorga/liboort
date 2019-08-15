/*
********************************************************************************
SerialNerve.h

This file defines the interface for simple serial communication.

Copyright (C) 2019  Luka Micheletti
********************************************************************************
*/

#ifndef __SERIAL_NERVE__
#define __SERIAL_NERVE__

#include "Nerve.h"

namespace Oort {
    class SerialNerve : public Nerve {
    public:
        // Wrapper for sendData.
        // The wrapper is made in order to match the names used in serial communication.
        uint8_t tX(byte* data);

        // Wrapper for receiveData.
        // The wrapper is made in order to match the names used in serial communication.
        byte* rX();

        // Transmit data over serial.
        uint8_t send(byte* data);

        // Receive daata over serial.
        byte* receive();
    };
}

#endif
