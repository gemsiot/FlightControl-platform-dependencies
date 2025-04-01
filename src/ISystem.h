#ifndef I_SYSTEM_H
#define I_SYSTEM_H

#include <stdint.h>
#include <string>
#include <functional>

// --- Forward Declarations ---
namespace particle {
    class SystemSleepConfiguration;
}

// --- Interface-specific Enums ---
enum class IEventType {
    TIME_CHANGED,
    OUT_OF_MEMORY
};

enum class IInterruptMode {
    RISING,
    FALLING,
    CHANGE
};

enum class IResetReason {
    RESET_REASON_NONE = 0, ///< Invalid reason code.
    RESET_REASON_UNKNOWN = 10, ///< Unspecified reason.
    // Hardware
    RESET_REASON_PIN_RESET = 20, ///< Reset from the reset pin.
    RESET_REASON_POWER_MANAGEMENT = 30, ///< Low-power management reset.
    RESET_REASON_POWER_DOWN = 40, ///< Power-down reset.
    RESET_REASON_POWER_BROWNOUT = 50, ///< Brownout reset.
    RESET_REASON_WATCHDOG = 60, ///< Watchdog reset.
    // Software
    RESET_REASON_UPDATE = 70, ///< Reset to apply firmware update.
    RESET_REASON_UPDATE_ERROR = 80, ///< Generic firmware update error (deprecated).
    RESET_REASON_UPDATE_TIMEOUT = 90, ///< Firmware update timeout.
    RESET_REASON_FACTORY_RESET = 100, ///< Factory reset requested.
    RESET_REASON_SAFE_MODE = 110, ///< Safe mode requested.
    RESET_REASON_DFU_MODE = 120, ///< DFU mode requested.
    RESET_REASON_PANIC = 130, ///< System panic.
    RESET_REASON_USER = 140, ///< User-requested reset.
    RESET_REASON_CONFIG_UPDATE = 150 ///< Reset to apply configuration changes.
};

/**
 * @brief Defines the reason the system woke from sleep (Interface Definition).
 * Mirrors common reasons found in platforms like Particle.
 */
enum class IWakeupReason: uint16_t{
    UNKNOWN,        ///< Wakeup reason is unknown or not applicable.
    BY_GPIO,        ///< Woken up by a GPIO pin interrupt.
    BY_ADC,
    BY_DAC,
    BY_RTC,         ///< Woken up by the Real-Time Clock alarm.
    BY_LPCOMP,
    BY_USART,
    BY_I2C,
    BY_SPI,
    BY_TIMER,
    BY_CAN,
    BY_USB,
    BY_BLE,
    BY_NFC,
    BY_NETWORK      ///< Woken up by a network event (e.g., cellular, Wi-Fi). Often relevant for ULP modes.
};


// --- Callback Type Alias ---
using SystemEventHandler = std::function<void(IEventType event, int data)>;

// --- Interface Definition ---
class ISystem {
public:
    virtual ~ISystem() = default;

    virtual void on(IEventType event, SystemEventHandler handler) = 0;
    virtual IResetReason resetReason() = 0;
    virtual uint32_t freeMemory() = 0;

    /**
     * @brief Puts the system to sleep using configuration and returns the wake reason.
     * @param config A const reference to the Particle sleep configuration object.
     * @return IWakeupReason An enum value indicating how the system woke up.
     */
    virtual IWakeupReason sleep(const particle::SystemSleepConfiguration& config) = 0; // Changed return type

};

#endif // I_SYSTEM_H