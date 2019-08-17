#include "PiSerialNerve.h"

namespace Oort {
    uint8_t PiSerialNerve::tX(byte* data, uint32_t length) {
        return this->send(data, length);
    }

    uint8_t PiSerialNerve::tX(Vector<byte>* data, uint32_t length) {
        return this->send(data->getItems(), length);
    }

    byte* PiSerialNerve::rX() {
        return this->receive();
    }

    uint8_t PiSerialNerve::send(byte* data, uint32_t length) {
        //TODO
        int opened = serialOpen("/dev/tty0", 9600);
        return 0;
    }

    byte* PiSerialNerve::receive() {
        //TODO
        return nullptr;
    }
}
