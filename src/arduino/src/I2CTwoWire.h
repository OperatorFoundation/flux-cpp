//
// Arduino TwoWire adapter for I2C interface
//

#ifndef I2CTWOWIRE_H
#define I2CTWOWIRE_H

#include <flux-cpp.h>
#include <Wire.h>

class I2CTwoWire : public I2C {
  public:
    explicit I2CTwoWire(TwoWire& wire);
    ~I2CTwoWire() override = default;

    void setLogger(Logger* logger);

    // Communication
    void beginTransmission(uint8_t address) override;
    uint8_t endTransmission() override;
    uint8_t endTransmission(bool sendStop) override;

    // Write operations
    size_t write(uint8_t data) override;
    size_t write(const uint8_t* data, size_t length) override;

    // Read operations
    uint8_t requestFrom(uint8_t address, uint8_t quantity) override;
    uint8_t requestFrom(uint8_t address, uint8_t quantity, bool sendStop) override;
    int available() override;
    int read() override;
    int peek() override;

  private:
    TwoWire& wire;
    Logger* logger = nullptr;
    const char* wireName;  // "0", "1", "2", or nullptr

    const char* getWireId() const;  // Helper to get wire identifier
};

#endif // I2CTWOWIRE_H