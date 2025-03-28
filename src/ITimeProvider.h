/**
 * @file ITimeProvider.h
 * @brief Interface for abstracting time-related functions.
 *
 * Defines a contract for getting the current time, system uptime (millis),
 * pausing execution (delay), setting the system time, and checking time validity,
 * independent of the underlying platform (e.g., Particle, Arduino).
 *
 * © 2023 Regents of the University of Minnesota. All rights reserved.
 * Adapted from refactoring discussion.
 */

 #ifndef I_TIME_PROVIDER_H
 #define I_TIME_PROVIDER_H
 
 #include <stdint.h> // For uint32_t standard type
 #include <time.h>   // For time_t standard type
 
 /**
  * @brief Abstract interface for time-related functionalities.
  *
  * Provides methods to interact with system time and delays in a
  * platform-agnostic way, enabling dependency injection and testing.
  */
 class ITimeProvider {
 public:
    virtual ~ITimeProvider() = default;
    
    //TimeClass from spark_wiring_time.h
    virtual int year() = 0;
    virtual int year(time_t t) = 0;
    virtual int month() = 0;
    virtual int month(time_t t) = 0;
    virtual int day() = 0;
    virtual int day(time_t t) = 0;
    virtual int hour() = 0;
    virtual int hour(time_t t) = 0;
    virtual int minute() = 0;
    virtual int minute(time_t t) = 0;
    virtual int second() = 0;
    virtual int second(time_t t) = 0;
    virtual time_t now() = 0;
    virtual void setTime(time_t t) = 0;
    virtual bool isValid() = 0;
    virtual void zone(float GMT_Offset) = 0;

    // System uptime and delay functions, related to timing
    virtual uint32_t millis() = 0;
    virtual void delay(uint32_t ms) = 0;
 };
 
 #endif // I_TIME_PROVIDER_H