#ifndef I_SYSTEM_H
#define I_SYSTEM_H

#include <stdint.h>
#include <string>
#include <functional>
// Need chrono for std::chrono::milliseconds
#include <chrono>

// --- Interface-specific Enums ---
enum class IEventType {
    TIME_CHANGED,
    OUT_OF_MEMORY
};

enum class IInterruptMode {
    CHANGE,
    RISING,
    FALLING
};

enum class ISleepMode {
    STOP,
    ULTRA_LOW_POWER,
    HIBERNATE
};

enum class INetworkInterfaceIndex {
    ALL = 0,
    LOOPBACK = 1,
    //MESH = 2, // Deprecated
    ETHERNET = 3,
    CELLULAR = 4,
    WIFI = 5,
    NONE = 6
};

// Using Particle's standard naming convention RESET_REASON_* is fine
// But ensure the values map correctly if needed elsewhere.
// For abstraction, just the enum names matter most.
enum class IResetReason {
    UNKNOWN = 0,
    PIN_RESET = 20,
    POWER_MANAGEMENT = 30,
    POWER_DOWN = 40,
    POWER_BROWNOUT = 50,
    WATCHDOG = 60,
    UPDATE = 70,
    UPDATE_ERROR = 80,
    UPDATE_TIMEOUT = 90,
    FACTORY_RESET = 100,
    SAFE_MODE = 110,
    DFU_MODE = 120,
    PANIC = 130,
    USER = 140,
    CONFIG_UPDATE = 150
};

enum class IWakeupReason: uint16_t{
    UNKNOWN = 0,
    BY_GPIO = 1,
    BY_ADC = 2,
    BY_DAC = 3,
    BY_RTC = 4,
    BY_LPCOMP = 5,
    BY_USART = 6,
    BY_I2C = 7,
    BY_SPI = 8,
    BY_TIMER = 9,
    BY_CAN = 10,
    BY_USB = 11,
    BY_BLE = 12,
    BY_NFC = 13,
    BY_NETWORK = 14
};


// --- Callback Type Alias ---
using SystemEventHandler = std::function<void(IEventType event, int data)>;


// --- Use a STRUCT for configuration data ---
// This struct can be created and populated by Kestrel.cpp without Particle.h
struct ISleepConfig {
    ISleepMode mode = ISleepMode::ULTRA_LOW_POWER; // Sensible default?
    std::chrono::milliseconds duration {0}; // Default to no duration (pin/event wake only)
    // Use standard uint16_t for pin number. Define Pins::Clock_INT elsewhere using standard types.
    uint16_t wakePin = 0xFFFF; // Use an invalid value like max uint16_t or a specific constant
    IInterruptMode wakePinMode = IInterruptMode::FALLING; // Default to falling
    INetworkInterfaceIndex network = INetworkInterfaceIndex::NONE; // Default network off
    // Add other flags if needed, e.g., bool waitForCloud = false;
};


// --- Interface Definition ---
class ISystem {
    public:
    virtual ~ISystem() = default;

    virtual void on(IEventType event, SystemEventHandler handler) = 0;
    virtual IResetReason resetReason() = 0;
    virtual uint32_t freeMemory() = 0;
    virtual bool waitForCondition(std::function<bool()> condition, std::chrono::milliseconds timeout) = 0;

    /**
     * @brief Puts the system to sleep using configuration and returns the wake reason.
     * @param config A const reference to the INTERFACE sleep configuration struct.
     * @return IWakeupReason An enum value indicating how the system woke up.
     */
    // Use the interface struct ISleepConfig here
    virtual IWakeupReason sleep(const ISleepConfig& config) = 0;
};

#endif // I_SYSTEM_H