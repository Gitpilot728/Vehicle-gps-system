/**
 * @file VehicleMonitor.cpp
 * @brief Implementation of the VehicleMonitor class
 */

#include "VehicleMonitor.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>

VehicleMonitor::VehicleMonitor(std::shared_ptr<NotificationManager> notifManager)
    : engineTemperature(85.0), fuelLevel(75.0), fuelConsumptionRate(8.5),
      currentSpeed(0.0), brakeWearLevel(85.0), notificationManager(notifManager) {}
void VehicleMonitor::setEngineTemperature(double temperature) {
    // Validate temperature range (-50°C to 200°C)
    if (temperature < -50.0) temperature = -50.0;
    if (temperature > 200.0) temperature = 200.0;
    engineTemperature = temperature;
    checkEngineTemperature();
}

void VehicleMonitor::setFuelLevel(double level) {

    if (level < 0.0) level = 0.0;
    if (level > 100.0) level = 100.0;
    fuelLevel = level;
    checkFuelLevel();
}

void VehicleMonitor::setFuelConsumptionRate(double rate) {
    if (rate < 0.0) rate = 0.0;
    fuelConsumptionRate = rate;
}

void VehicleMonitor::setCurrentSpeed(double speed) {
    if (speed < 0.0) speed = 0.0;
    currentSpeed = speed;
    checkSpeed();
}

void VehicleMonitor::setBrakeWearLevel(double wearLevel) {
    if (wearLevel < 0.0) wearLevel = 0.0;
    if (wearLevel > 100.0) wearLevel = 100.0;
    brakeWearLevel = wearLevel;
    checkBrakeSystem();
}

double VehicleMonitor::getEngineTemperature() const { return engineTemperature; }
double VehicleMonitor::getFuelLevel() const { return fuelLevel; }
double VehicleMonitor::getFuelConsumptionRate() const { return fuelConsumptionRate; }
double VehicleMonitor::getCurrentSpeed() const { return currentSpeed; }
double VehicleMonitor::getBrakeWearLevel() const { return brakeWearLevel; }
void VehicleMonitor::checkEngineTemperature() {
    if (engineTemperature > MAX_ENGINE_TEMP) {
        std::stringstream ss;
        ss << "Engine overheating! Temperature: " << std::fixed << std::setprecision(1) 
           << engineTemperature << "°C (Max: " << MAX_ENGINE_TEMP << "°C)";
        notificationManager->addNotification(ss.str(), AlertLevel::CRITICAL);
    } else if (engineTemperature > MAX_ENGINE_TEMP - 10.0) {
        std::stringstream ss;
        ss << "Engine temperature elevated: " << std::fixed << std::setprecision(1) 
           << engineTemperature << "°C";
        notificationManager->addNotification(ss.str(), AlertLevel::WARNING);
    }
}

void VehicleMonitor::checkFuelLevel() {
    if (fuelLevel <= CRITICAL_FUEL_THRESHOLD) {
        std::stringstream ss;
        ss << "CRITICAL: Fuel level extremely low! " << std::fixed << std::setprecision(1) 
           << fuelLevel << "% remaining";
        notificationManager->addNotification(ss.str(), AlertLevel::CRITICAL);
    } else if (fuelLevel <= LOW_FUEL_THRESHOLD) {
        std::stringstream ss;
        ss << "Low fuel warning: " << std::fixed << std::setprecision(1) 
           << fuelLevel << "% remaining";
        notificationManager->addNotification(ss.str(), AlertLevel::WARNING);
    }
}

void VehicleMonitor::checkSpeed() {
    if (currentSpeed > MAX_SPEED_LIMIT) {
        std::stringstream ss;
        ss << "Speed limit exceeded! Current: " << std::fixed << std::setprecision(1) 
           << currentSpeed << " km/h (Limit: " << MAX_SPEED_LIMIT << " km/h)";
        notificationManager->addNotification(ss.str(), AlertLevel::WARNING);
    }
}

void VehicleMonitor::checkBrakeSystem() {
    if (brakeWearLevel <= MIN_BRAKE_THRESHOLD) {
        std::stringstream ss;
        ss << "Brake system requires attention! Wear level: " << std::fixed << std::setprecision(1) 
           << brakeWearLevel << "%";
        if (brakeWearLevel <= 10.0) {
            notificationManager->addNotification(ss.str(), AlertLevel::CRITICAL);
        } else {
            notificationManager->addNotification(ss.str(), AlertLevel::WARNING);
        }
    }
}
void VehicleMonitor::performSystemCheck() {
    std::cout << "\n\tPerforming comprehensive system check..." << std::endl;    
    checkEngineTemperature();
    checkFuelLevel();
    checkSpeed();
    checkBrakeSystem();    
    if (!notificationManager->hasCriticalAlerts()) {
        notificationManager->addNotification("System check completed - All systems normal", AlertLevel::INFO);
    }
}

void VehicleMonitor::displayStatus() const {
    std::cout << "\n\t=== VEHICLE STATUS DASHBOARD ===" << std::endl;
    std::cout << std::string(45, '=') << std::endl;    
    // Engine status
    std::cout << "\tEngine Temperature: " << std::fixed << std::setprecision(1) 
              << engineTemperature << "°C";
    if (engineTemperature > MAX_ENGINE_TEMP) {
        std::cout << "\tOVERHEATING!";
    } else if (engineTemperature > MAX_ENGINE_TEMP - 10.0) {
        std::cout << "\tHIGH";
    } else {
        std::cout << "\tNORMAL";
    }
    std::cout << std::endl;    
    // Fuel status
    std::cout << "\tFuel Level: " << std::fixed << std::setprecision(1) << fuelLevel << "%";
    if (fuelLevel <= CRITICAL_FUEL_THRESHOLD) {
        std::cout << "\tCRITICAL!";
    } else if (fuelLevel <= LOW_FUEL_THRESHOLD) {
        std::cout << "\tLOW";
    } else {
        std::cout << "\tOK";
    }
    std::cout << " (Range: ~" << std::fixed << std::setprecision(0) 
              << calculateEstimatedRange() << " km)" << std::endl;
    
    // Speed status
    std::cout << "\tCurrent Speed: " << std::fixed << std::setprecision(1) << currentSpeed << " km/h";
    if (currentSpeed > MAX_SPEED_LIMIT) {
        std::cout << "\tOVER LIMIT!";
    } else {
        std::cout << "\tOK";
    }
    std::cout << std::endl;
    
    // Brake status
    std::cout << "\tBrake Wear: " << std::fixed << std::setprecision(1) << brakeWearLevel << "%";
    if (brakeWearLevel <= 10.0) {
        std::cout << "\tCRITICAL!";
    } else if (brakeWearLevel <= MIN_BRAKE_THRESHOLD) {
        std::cout << "\tNEEDS SERVICE";
    } else {
        std::cout << "\tGOOD";
    }
    std::cout << std::endl;
    
    // Fuel consumption
    std::cout << "\tFuel Consumption: " << std::fixed << std::setprecision(1) 
              << fuelConsumptionRate << " L/100km" << std::endl;
    
    std::cout << std::string(45, '=') << std::endl;
}
void VehicleMonitor::simulateRealTimeUpdate() {
    std::random_device rd;
    std::mt19937 gen(rd());    
    std::uniform_real_distribution<> tempVar(-2.0, 3.0);
    std::uniform_real_distribution<> fuelVar(-0.5, 0.0);  // Fuel only decreases
    std::uniform_real_distribution<> speedVar(-5.0, 10.0);
    std::uniform_real_distribution<> brakeVar(-0.1, 0.0); 
    setEngineTemperature(engineTemperature + tempVar(gen));
    setFuelLevel(fuelLevel + fuelVar(gen));
    setCurrentSpeed(std::max(0.0, currentSpeed + speedVar(gen)));
    setBrakeWearLevel(brakeWearLevel + brakeVar(gen));
    std::cout << " Real-time data updated..." << std::endl;
}
double VehicleMonitor::calculateEstimatedRange() const {
    if (fuelConsumptionRate <= 0.0) return 0.0;
    if (fuelLevel <= 0.0) return 0.0;    
    const double tankCapacity = 50.0;
    double currentFuelAmount = (fuelLevel / 100.0) * tankCapacity;    
    return (currentFuelAmount / fuelConsumptionRate) * 100.0;
}
