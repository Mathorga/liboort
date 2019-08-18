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
#include "Vector.h"
#include "utils.h"

namespace Oort {
    class SerialNerve : public Nerve {
    public:
        // Constructor.
        SerialNerve();
        ~SerialNerve();

        // Initialize the serial stream.
        int8_t init(char* fileName);

        // Wrapper for sendData.
        // The wrapper is made in order to match the names used in serial communication.
        int32_t tX(byte* data, uint32_t length);

        int32_t tX(Vector<byte>* data, uint32_t length);

        // Wrapper for receiveData.
        // The wrapper is made in order to match the names used in serial communication.
        byte* rX();

        // Transmit data over serial.
        uint32_t send(byte* data, uint32_t length);

        // Receive daata over serial.
        byte* receive();

        int32_t closeStream();

    private:
        int32_t stream;
    };
}

#endif
