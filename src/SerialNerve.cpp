#include "SerialNerve.h"

namespace Oort {
    // Code to simple serial communication is kindly provided by:
    // https://raspberry-projects.com/pi/programming-in-c/uart-serial-port/using-the-uart
    int8_t SerialNerve::init(char* fileName) {
        int32_t stream = -1;
        struct termios options;

        // Open stream in non blocking read/write mode.
        stream = open(fileName, O_RDWR | O_NOCTTY | O_NDELAY);

        // Check if opened correctly.
        if (stream != -1) {
            // Get default attributes from serial.
            tcgetattr(stream, &options);

            // Set baud rate.
            options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
            options.c_iflag = IGNPAR;
            options.c_oflag = 0;
            options.c_lflag = 0;
            tcflush(uart0_filestream, TCIFLUSH);
            tcsetattr(uart0_filestream, TCSANOW, &options);
        } else {
            printf("\n<SerialNerve::init()> Error: couldn't open serial communication to device %s\n", fileName);
        }
    }

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

    // int32_t SerialNerve::init(char* fileName) {
    //     int32_t device = open(fileName, O_RDWR | O_NOCTTY);
    // }
}
