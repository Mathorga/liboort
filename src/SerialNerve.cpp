#include "SerialNerve.h"

namespace Oort {
    SerialNerve::SerialNerve() {
        // Set stream value to -1 in order to get ready for the initialization.
        this->stream = -1;
    }

    SerialNerve::~SerialNerve() {
        this->closeStream();
    }

    // Code to simple serial communication is kindly provided by:
    // https://raspberry-projects.com/pi/programming-in-c/uart-serial-port/using-the-uart
    int8_t SerialNerve::init(char* fileName) {
        struct termios options;

        // Open stream in non blocking read/write mode.
        this->stream = open(fileName, O_RDWR | O_NOCTTY | O_NDELAY);

        // Check if opened correctly.
        if (this->stream != -1) {
            // Get default attributes from serial.
            tcgetattr(this->stream, &options);

            // Set baud rate.
            options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
            options.c_iflag = IGNPAR;
            options.c_oflag = 0;
            options.c_lflag = 0;
            tcflush(this->stream, TCIFLUSH);
            tcsetattr(this->stream, TCSANOW, &options);
        } else {
            printf("\n<SerialNerve::init()> Error: couldn't open serial communication to device %s\n", fileName);
        }
        return this->stream;
    }

    int32_t SerialNerve::tX(byte* data, uint32_t length) {
        return this->send(data, length);
    }

    int32_t SerialNerve::tX(Vector<byte>* data, uint32_t length) {
        return this->send(data->getItems(), length);
    }

    byte* SerialNerve::rX() {
        return this->receive();
    }

    uint32_t SerialNerve::send(byte* data, uint32_t length) {
        int32_t count;

        if (this->stream != -1) {
            count = write(this->stream, data, length);
            if (count < 0) {
                printf("\n<SerialNerve::send()> Error: couldn't send data\n");
            }
        } else {
            printf("\n<SerialNerve::send()> Error: stream is not open\n");
        }
        return count;
    }

    byte* SerialNerve::receive() {
        byte* data = (byte*) malloc(256);
        int32_t length = 0;

        if (this->stream != -1) {
            // Read up to 255 characters from the port if they are there.
            length = read(this->stream, (void*) data, 255);

            if (length < 0) {
                printf("\n<SerialNerve::receive()> Error: could not receive data\n");
            } else if (length == 0) {
                printf("\n<SerialNerve::receive()> Error: there is no data\n");
            } else {
                // Bytes received.
                printf("\n%d bytes read\n", length);
            }
        } else {
            printf("\n<SerialNerve::receive()> Error: stream is not open\n");
        }

        return data;
    }

    int32_t SerialNerve::closeStream() {
        return close(this->stream);
    }
}
