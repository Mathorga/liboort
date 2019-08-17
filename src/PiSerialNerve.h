#ifndef __PI_SERIAL_NERVE__
#define __PI_SERIAL_NERVE__

#include "SerialNerve.h"
#include <wiringSerial.h>

namespace Oort {
    class PiSerialNerve : public SerialNerve {
    public:
        // Wrapper for sendData.
        // The wrapper is made in order to match the names used in serial communication.
        uint8_t tX(byte* data, uint32_t length);

        uint8_t tX(Vector<byte>* data, uint32_t length);

        // Wrapper for receiveData.
        // The wrapper is made in order to match the names used in serial communication.
        byte* rX();

        // Transmit data over serial.
        uint8_t send(byte* data, uint32_t length);

        // Receive daata over serial.
        byte* receive();
    };
}

#endif
