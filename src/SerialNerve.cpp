#include "SerialNerve.h"

namespace Oort {
    const uint32_t SerialNerve::DEFAULT_RX_LENGTH = 256;
    const uint32_t SerialNerve::DEFAULT_WAIT_TIME = 3000000;

    SerialNerve::SerialNerve() {
        // Set stream value to -1 in order to get ready for the initialization.
        this->stream = -1;
    }

    SerialNerve::SerialNerve(char* fileName) : SerialNerve(fileName, true, DEFAULT_WAIT_TIME) {}

    SerialNerve::SerialNerve(char* fileName, bool wait) : SerialNerve(fileName, wait, DEFAULT_WAIT_TIME) {}

    SerialNerve::SerialNerve(char* fileName, bool wait, uint32_t waitTime) : SerialNerve() {
        this->openStream(fileName);
        this->init();
        if (wait) {
            // Wait default wait time.
            usleep(waitTime);
        }
    }

    SerialNerve::~SerialNerve() {
        this->closeStream();
    }

    // Code for simple serial communication is kindly provided by:
    // https://raspberry-projects.com/pi/programming-in-c/uart-serial-port/using-the-uart
    // After the initialization a little wait time is needed in order to successfully send and receive data.
    int32_t SerialNerve::init() {
        struct termios options;

        // Check if stream is open.
        if (this->stream != -1) {
            // Get default attributes from serial.
            tcgetattr(this->stream, &options);

            // Turn on blocking for reads.
            // fcntl(this->stream, F_SETFL, 0);

            // Set baud rate.
            options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
            options.c_iflag = IGNPAR;
            options.c_oflag = 0;
            options.c_lflag = 0;
            tcflush(this->stream, TCIFLUSH);
            tcsetattr(this->stream, TCSANOW, &options);
        } else {
            printf("\n<SerialNerve::init()> Error: stream is not open\n");
        }
        return this->stream;
    }

    int32_t SerialNerve::tX(byte* data, uint32_t length) {
        return this->send(data, length);
    }

    int32_t SerialNerve::tX(Vector<byte>* data, uint32_t length) {
        return this->send(data->getItems(), length);
    }

    int32_t SerialNerve::rX(byte* buffer) {
        return this->receive(buffer);
    }

    int32_t SerialNerve::rX(byte* buffer, uint32_t length) {
        return this->receive(buffer, length);
    }

    int32_t SerialNerve::send(byte* data, uint32_t length) {
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

    int32_t SerialNerve::receive(byte* buffer) {
        return this->receive(buffer, DEFAULT_RX_LENGTH);
    }

    int32_t SerialNerve::receive(byte* buffer, uint32_t length) {
        int32_t count = 0;

        if (this->stream != -1) {
            // Read up to 255 characters from the port if they are there.
            count = read(this->stream, (void*) buffer, length);

            if (count < 0) {
                printf("\n<SerialNerve::receive()> Error: could not receive data\n");
            } else if (count == 0) {
                printf("\n<SerialNerve::receive()> Error: there is no data\n");
            }
        } else {
            printf("\n<SerialNerve::receive()> Error: stream is not open\n");
        }

        return count;
    }

    int32_t SerialNerve::openStream(char* fileName) {
        // Open stream in non blocking read/write mode.
        // this->stream = open(fileName, O_RDWR | O_NOCTTY | O_NDELAY);
        this->stream = open(fileName, O_RDWR | O_NOCTTY);

        if (this->stream == -1) {
            printf("\n<SerialNerve::openStream()> Error: couldn't open serial communication to device %s\n", fileName);
        }

        return this->stream;
    }

    int32_t SerialNerve::closeStream() {
        int32_t result = close(this->stream);

        this->stream = -1;

        return result;
    }

    int32_t SerialNerve::getStream() {
        return this->stream;
    }
}
