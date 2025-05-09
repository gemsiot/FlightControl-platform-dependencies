# FlightControl-platform-dependencies

Platform Dependenies aims to remove Particle dependencies from the project and instead rely on interfaces developed as a middle ground between Particle.h and Particle's platform library.

## Included Abstractions
- Cloud - functions for connecting to Particle cloud
- Gpio - functions for reading and writing GPIO pins
- Hal - placeholder for any direct hardware functions
- Serial - functions for SDI12 and USB serial
- TimeProvider - time related functions, delay, millis etc
- Wire - I2C related functions

## Interfaces
Each of these headers are interfaces to Particle firmware. This allows for unit testing and debugging independent of Particle hardware.