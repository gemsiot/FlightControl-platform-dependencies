/**
 * @file    ISerial.h
 * @brief   Interface for serial communication abstraction
 */

#ifndef __I_SERIAL_H
#define __I_SERIAL_H

#include <stddef.h>
#include <stdint.h>
#include <time.h>

/**
 * @brief Interface for serial communication
 * 
 * This interface defines only the functions used in Kestrel.cpp
 * to abstract serial communication functionality.
 */
class ISerial {
public:
    virtual ~ISerial() = default;

    virtual void begin(long speed) = 0;
    virtual void begin(unsigned long speed, uint32_t config) = 0;
    // Make this optional in case the implementation only supports one begin method
    virtual void begin(unsigned long speed) { begin(speed, 0); }
    virtual size_t print(const char* str) = 0;
    virtual size_t print(int value) = 0;
    virtual size_t print(uint32_t value) = 0;
    virtual size_t print(time_t value) = 0;
    virtual size_t print(unsigned int value, int base = 10) = 0;
    virtual size_t print(float value) = 0;
    virtual size_t print(double value) = 0;
    virtual size_t println() = 0;
    virtual size_t println(const char* str) = 0;
    virtual size_t println(int value) = 0;
    virtual size_t println(uint32_t value) = 0;
    virtual size_t println(time_t value) = 0;
    virtual size_t println(unsigned int value, int base = 10) = 0;
    virtual void flush() = 0;
};

#endif // __I_SERIAL_H