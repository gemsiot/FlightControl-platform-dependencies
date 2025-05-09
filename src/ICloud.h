/**
 * @file ICloud.h
 * @brief Interface for abstracting cloud connection.
 *
 * Defines a contract for connecting, disconnecting, and syncing to the cloud
 * independent of the underlying platform (e.g., Particle, Arduino).
 *
 * © 2025 Regents of the University of Minnesota. All rights reserved.
 * Adapted from refactoring discussion.
 */

 #ifndef I_CLOUD_H
 #define I_CLOUD_H
 
 #include <stdint.h> // For uint32_t standard type
 #include <stddef.h>
 // Need chrono for std::chrono::milliseconds
 #include <chrono>
 
 struct ICloudDisconnectOptions
 {
    bool graceful = false;
    std::chrono::milliseconds timeout {0};
 };


 /**
  * @brief Abstract interface for Cellular/Cloud related funcitonality.
  *
  * Provides methods to interact with Cloud servcices in a
  * platform-agnostic way, enabling dependency injection and testing.
  */
 class ICloud {
 public:
    virtual ~ICloud() = default;
    virtual void connect() = 0;
    virtual void disconnect(const ICloudDisconnectOptions& options) = 0;
    virtual bool connected() = 0;
    virtual bool syncTime() = 0;
    virtual bool syncTimePending() = 0;
    virtual bool syncTimeDone() = 0;
    virtual bool process() = 0;
}; 
 
 #endif // I_CLOUD_H