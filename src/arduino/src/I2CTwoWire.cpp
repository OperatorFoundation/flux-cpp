//
// Created by Dr. Brandon Wiley on 11/12/25.
//
//
// Arduino TwoWire adapter for I2C interface
//

#include "I2CTwoWire.h"

I2CTwoWire::I2CTwoWire(TwoWire& wire) : wire(wire), wireName(nullptr) {
  // Identify which Wire instance this is
  if(&wire == &Wire) {
    wireName = "0";
  }
#ifdef Wire1
  else if(&wire == &Wire1) {
    wireName = "1";
  }
#endif
#ifdef Wire2
  else if(&wire == &Wire2) {
    wireName = "2";
  }
#endif
  // If no match, wireName stays nullptr and we'll use the address
}

void I2CTwoWire::setLogger(Logger* logger)
{
  this->logger = logger;
}

// Helper function to get wire identifier string
const char* I2CTwoWire::getWireId() const {
  static char addrBuf[20];
  if(wireName) {
    return wireName;
  } else {
    snprintf(addrBuf, sizeof(addrBuf), "%p", static_cast<const void*>(&wire));
    return addrBuf;
  }
}

// Communication
void I2CTwoWire::beginTransmission(uint8_t address) {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.beginTransmission(%d)", getWireId(), address);
  }

  wire.beginTransmission(address);
}

uint8_t I2CTwoWire::endTransmission() {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.endTransmission()", getWireId());
  }

  return wire.endTransmission();
}

uint8_t I2CTwoWire::endTransmission(bool sendStop) {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.endTransmission(%d)", getWireId(), sendStop);
  }

  return wire.endTransmission(sendStop);
}

// Write operations
size_t I2CTwoWire::write(uint8_t data) {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.write(0x%02X)", getWireId(), data);
  }

  return wire.write(data);
}

size_t I2CTwoWire::write(const uint8_t* data, size_t length) {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.write(%p, %zu)", getWireId(), static_cast<const void*>(data), length);
  }

  return wire.write(data, length);
}

// Read operations
uint8_t I2CTwoWire::requestFrom(uint8_t address, uint8_t quantity) {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.requestFrom(%d, %d)", getWireId(), address, quantity);
  }

  return wire.requestFrom(address, quantity);
}

uint8_t I2CTwoWire::requestFrom(uint8_t address, uint8_t quantity, bool sendStop) {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.requestFrom(%d, %d, %d)", getWireId(), address, quantity, sendStop);
  }

  return wire.requestFrom(address, quantity, sendStop);
}

int I2CTwoWire::available() {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.available()", getWireId());
  }

  return wire.available();
}

int I2CTwoWire::read() {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.read()", getWireId());
  }

  return wire.read();
}

int I2CTwoWire::peek() {
  if(logger)
  {
    logger->debugf("I2CTwoWire{%s}.peek()", getWireId());
  }

  return wire.peek();
}