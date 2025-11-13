//
// Created by Dr. Brandon Wiley on 11/12/25.
//
//
// Cross-platform I2C interface
//

#ifndef ONDA_CPP_I2C_H
#define ONDA_CPP_I2C_H

#include <cstdint>
#include <cstddef>

class I2C {
  public:
    virtual ~I2C() = default;

    // Communication
    virtual void beginTransmission(uint8_t address) = 0;
    virtual uint8_t endTransmission() = 0;
    virtual uint8_t endTransmission(bool sendStop) = 0;

    // Write operations
    virtual size_t write(uint8_t data) = 0;
    virtual size_t write(const uint8_t* data, size_t length) = 0;

    // Read operations
    virtual uint8_t requestFrom(uint8_t address, uint8_t quantity) = 0;
    virtual uint8_t requestFrom(uint8_t address, uint8_t quantity, bool sendStop) = 0;
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
};

#endif //ONDA_CPP_I2C_H