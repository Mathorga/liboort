#include "SerialNerve.h"

namespace Oort {
    uint8_t SerialNerve::tX(byte* data) {
        return this->send(data);
    }

    byte* SerialNerve::rX() {
        return this->receive();
    }

    uint8_t SerialNerve::send(byte* data) {
        //TODO
        return 0;
    }

    byte* SerialNerve::receive() {
        //TODO
        return nullptr;
    }
}
