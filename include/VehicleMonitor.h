/**
 * @file VehicleMonitor.h
 * @brief Vehicle health monitoring and diagnostic system
 * @author AI-Enhanced Development System
 */

#ifndef VEHICLE_MONITOR_H
#define VEHICLE_MONITOR_H

#include "NotificationManager.h"
#include <memory>

/**
 * @brief Comprehensive vehicle monitoring and diagnostic system
 * 
 * Monitors critical vehicle parameters including engine temperature, fuel levels,
 * speed, and brake system health. Automatically triggers alerts when parameters
 * exceed safe operating ranges.
 */
class VehicleMonitor {
private:
    // Vehicle parameters
    double engineTemperature;           ///< Engine temperature in Celsius
    double fuelLevel;                   ///< Fuel level as percentage (0-100)
    double fuelConsumptionRate;         ///< Fuel consumption in L/100km
    double currentSpeed;                ///< Current speed in km/h
    double brakeWearLevel;              ///< Brake wear as percentage (100 = new, 0 = worn out)
    
    // Threshold values
    static constexpr double MAX_ENGINE_TEMP = 105.0;        ///< Maximum safe engine temperature
    static constexpr double LOW_FUEL_THRESHOLD = 15.0;      ///< Low fuel warning threshold
    static constexpr double CRITICAL_FUEL_THRESHOLD = 5.0;  ///< Critical fuel alert threshold
    static constexpr double MAX_SPEED_LIMIT = 120.0;        ///< Speed limit for alerts
    static constexpr double MIN_BRAKE_THRESHOLD = 20.0;     ///< Minimum brake wear threshold
    
    std::shared_ptr<NotificationManager> notificationManager;   ///< Notification system reference
    
    /**
     * @brief Check engine temperature and trigger alerts if necessary
     */
    void checkEngineTemperature();
    
    /**
     * @brief Check fuel levels and trigger alerts if necessary
     */
    void checkFuelLevel();
    
    /**
     * @brief Check current speed and trigger alerts if necessary
     */
    void checkSpeed();
    
    /**
     * @brief Check brake system health and trigger alerts if necessary
     */
    void checkBrakeSystem();
    
public:
    /**
     * @brief Constructor with notification manager
     * @param notifManager Shared pointer to notification manager
     */
    explicit VehicleMonitor(std::shared_ptr<NotificationManager> notifManager);
    
    /**
     * @brief Set engine temperature
     * @param temperature Temperature in Celsius
     */
    void setEngineTemperature(double temperature);
    
    /**
     * @brief Set fuel level
     * @param level Fuel level as percentage (0-100)
     */
    void setFuelLevel(double level);
    
    /**
     * @brief Set fuel consumption rate
     * @param rate Consumption rate in L/100km
     */
    void setFuelConsumptionRate(double rate);
    
    /**
     * @brief Set current vehicle speed
     * @param speed Speed in km/h
     */
    void setCurrentSpeed(double speed);
    
    /**
     * @brief Set brake wear level
     * @param wearLevel Wear level as percentage (100 = new, 0 = completely worn)
     */
    void setBrakeWearLevel(double wearLevel);
    
    /**
     * @brief Get current engine temperature
     * @return Engine temperature in Celsius
     */
    double getEngineTemperature() const;
    
    /**
     * @brief Get current fuel level
     * @return Fuel level as percentage
     */
    double getFuelLevel() const;
    
    /**
     * @brief Get fuel consumption rate
     * @return Consumption rate in L/100km
     */
    double getFuelConsumptionRate() const;
    
    /**
     * @brief Get current speed
     * @return Speed in km/h
     */
    double getCurrentSpeed() const;
    
    /**
     * @brief Get brake wear level
     * @return Brake wear as percentage
     */
    double getBrakeWearLevel() const;
    
    /**
     * @brief Perform comprehensive system check
     * 
     * Checks all monitored parameters and triggers appropriate alerts
     */
    void performSystemCheck();
    
    /**
     * @brief Display current vehicle status
     */
    void displayStatus() const;
    
    /**
     * @brief Simulate real-time data updates (for demonstration)
     */
    void simulateRealTimeUpdate();
    
    /**
     * @brief Calculate estimated range based on current fuel and consumption
     * @return Estimated range in kilometers
     */
    double calculateEstimatedRange() const;
};

#endif // VEHICLE_MONITOR_H
