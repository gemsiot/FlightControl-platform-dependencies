/**
 * @file IGpio.h
 * @brief Interface for abstracting general purpose i/o pin control
 *
 * Defines a contract for getting setting and reading digital pins
 * on hardware platforms (arduino, particle)
 *
 * © 2023 Regents of the University of Minnesota. All rights reserved.
 * Adapted from refactoring discussion.
 */

 #ifndef I_GPIO_H
 #define I_GPIO_H
 
 #include <stdint.h> // For uint32_t standard type

 enum class IPinMode {
   INPUT = 0,
   OUTPUT = 1
 };

 enum class ILevel: uint8_t {
    LOW = 0,
    HIGH = 1
 };

 /**
  * @brief Abstract interface for GPIO functions
  *
  * Interface for interacting with GPIO in a
  * platform-agnostic way, enabling dependency injection and testing.
  */
 class IGpio {
 public:
    virtual ~IGpio() = default;

    virtual void pinMode(uint16_t pin, IPinMode mode) = 0;
    virtual void digitalWrite(uint16_t pin, uint8_t value) = 0;
    virtual int32_t digitalRead(uint16_t pin) = 0;
 };
 
 #endif // I_GPIO_H