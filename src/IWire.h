/**
 * @file IWire.h
 * @brief Interface for abstracting I2C communication.
 *
 * Defines a contract for starting transmissions, and writing to I2C busses
 * independent of the underlying platform (e.g., Particle, Arduino).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 * Adapted from refactoring discussion.
 */

 #ifndef I_WIRE_H
 #define I_WIRE_H
 
 #include <stdint.h> // For uint32_t standard type
 #include <stddef.h>
 
 /**
  * @brief Abstract interface for I2C relataed funcitonality.
  *
  * Provides methods to interact with I2C communication busses in a
  * platform-agnostic way, enabling dependency injection and testing.
  */
 class IWire {
 public:
    virtual ~IWire() = default;
    
    virtual void begin() = 0;
    virtual void setClock(uint32_t speed) = 0;
    virtual bool isEnabled() = 0;
    virtual void beginTransmission(int) = 0;
    virtual uint8_t endTransmission() = 0;
    virtual size_t write(uint8_t) = 0;
    virtual int reset() = 0;
 };
 
 #endif // I_WIRE_H