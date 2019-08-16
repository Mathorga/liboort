#include "SerialNerve.h"

namespace Oort {
    uint8_t SerialNerve::tX(byte* data, uint32_t length) {
        return this->send(data, length);
    }

    uint8_t SerialNerve::tX(Vector<byte>* data, uint32_t length) {
        return this->send(data->getItems(), length);
    }

    byte* SerialNerve::rX() {
        return this->receive();
    }

    uint8_t SerialNerve::send(byte* data, uint32_t length) {
        //TODO
        return 0;
    }

    byte* SerialNerve::receive() {
        //TODO
        return nullptr;
    }
}
