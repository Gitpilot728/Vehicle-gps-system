/**
 * @file test_vehicle_monitor.cpp
 * @brief Unit tests for VehicleMonitor class
 */

#include "VehicleMonitor.h"
#include "NotificationManager.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>

class VehicleMonitorTest {
private:
    std::shared_ptr<NotificationManager> notificationManager;
    std::shared_ptr<VehicleMonitor> monitor;
    
    void assertEqual(double expected, double actual, double tolerance = 0.001) {
        if (std::fabs(expected - actual) > tolerance) {
            std::cout << "❌ FAIL: Expected " << expected << ", got " << actual << std::endl;
            throw std::runtime_error("Assertion failed: Expected " + std::to_string(expected) + ", got " + std::to_string(actual));
        }
    }
    
    void assertTrue(bool condition, const std::string& message) {
        if (!condition) {
            std::cout << "❌ FAIL: " << message << std::endl;
            throw std::runtime_error("Test assertion failed: " + message);
        }
    }
    
public:
    VehicleMonitorTest() {
        notificationManager = std::make_shared<NotificationManager>();
        monitor = std::make_shared<VehicleMonitor>(notificationManager);
    }
    
    void testEngineTemperatureMonitoring() {
        std::cout << "🧪 Testing engine temperature monitoring..." << std::endl;
        
        // Test normal temperature
        monitor->setEngineTemperature(85.0);
        assertEqual(85.0, monitor->getEngineTemperature());
        
        // Test high temperature (should trigger warning)
        monitor->setEngineTemperature(100.0);
        assertEqual(100.0, monitor->getEngineTemperature());
        
        // Test overheating (should trigger critical alert)
        monitor->setEngineTemperature(110.0);
        assertEqual(110.0, monitor->getEngineTemperature());
        
        std::cout << "✅ Engine temperature monitoring tests passed" << std::endl;
    }
    
    void testFuelLevelMonitoring() {
        std::cout << "🧪 Testing fuel level monitoring..." << std::endl;
        
        // Test normal fuel level
        monitor->setFuelLevel(75.0);
        assertEqual(75.0, monitor->getFuelLevel());
        
        // Test low fuel (should trigger warning)
        monitor->setFuelLevel(10.0);
        assertEqual(10.0, monitor->getFuelLevel());
        
        // Test critical fuel (should trigger critical alert)
        monitor->setFuelLevel(3.0);
        assertEqual(3.0, monitor->getFuelLevel());
        
        // Test boundary validation
        monitor->setFuelLevel(-5.0); // Should clamp to 0
        assertEqual(0.0, monitor->getFuelLevel());
        
        monitor->setFuelLevel(105.0); // Should clamp to 100
        assertEqual(100.0, monitor->getFuelLevel());
        
        std::cout << "✅ Fuel level monitoring tests passed" << std::endl;
    }
    
    void testSpeedMonitoring() {
        std::cout << "🧪 Testing speed monitoring..." << std::endl;
        
        // Test normal speed
        monitor->setCurrentSpeed(80.0);
        assertEqual(80.0, monitor->getCurrentSpeed());
        
        // Test speed limit exceeded (should trigger warning)
        monitor->setCurrentSpeed(130.0);
        assertEqual(130.0, monitor->getCurrentSpeed());
        
        // Test negative speed (should clamp to 0)
        monitor->setCurrentSpeed(-10.0);
        assertEqual(0.0, monitor->getCurrentSpeed());
        
        std::cout << "✅ Speed monitoring tests passed" << std::endl;
    }
    
    void testBrakeWearMonitoring() {
        std::cout << "🧪 Testing brake wear monitoring..." << std::endl;
        
        // Test normal brake wear
        monitor->setBrakeWearLevel(85.0);
        assertEqual(85.0, monitor->getBrakeWearLevel());
        
        // Test low brake wear (should trigger warning)
        monitor->setBrakeWearLevel(15.0);
        assertEqual(15.0, monitor->getBrakeWearLevel());
        
        // Test critical brake wear (should trigger critical alert)
        monitor->setBrakeWearLevel(5.0);
        assertEqual(5.0, monitor->getBrakeWearLevel());
        
        // Test boundary validation
        monitor->setBrakeWearLevel(-5.0); // Should clamp to 0
        assertEqual(0.0, monitor->getBrakeWearLevel());
        
        monitor->setBrakeWearLevel(105.0); // Should clamp to 100
        assertEqual(100.0, monitor->getBrakeWearLevel());
        
        std::cout << "✅ Brake wear monitoring tests passed" << std::endl;
    }
    
    void testFuelConsumptionAndRange() {
        std::cout << "🧪 Testing fuel consumption and range calculation..." << std::endl;
        
        // Set fuel consumption rate
        monitor->setFuelConsumptionRate(8.5);
        assertEqual(8.5, monitor->getFuelConsumptionRate());
        
        // Test negative consumption rate (should clamp to 0)
        monitor->setFuelConsumptionRate(-2.0);
        assertEqual(0.0, monitor->getFuelConsumptionRate());
        
        // Reset to valid value and test range calculation
        monitor->setFuelConsumptionRate(8.0);
        monitor->setFuelLevel(50.0); // 50% of 50L tank = 25L
        
        double expectedRange = (25.0 / 8.0) * 100.0; // 312.5 km
        double actualRange = monitor->calculateEstimatedRange();
        assertEqual(expectedRange, actualRange, 0.1);
        
        std::cout << "✅ Fuel consumption and range tests passed" << std::endl;
    }
    
    void testSystemCheck() {
        std::cout << "🧪 Testing system check functionality..." << std::endl;
        
        // Set all parameters to normal values
        monitor->setEngineTemperature(85.0);
        monitor->setFuelLevel(75.0);
        monitor->setCurrentSpeed(60.0);
        monitor->setBrakeWearLevel(80.0);
        
        // Clear any existing notifications
        notificationManager->clearNotifications();
        
        // Perform system check
        monitor->performSystemCheck();
        
        // Should have at least one notification (system check completed)
        assertTrue(notificationManager->getNotificationCount() > 0, "System check should generate notifications");
        
        std::cout << "✅ System check tests passed" << std::endl;
    }
    
    void runAllTests() {
        std::cout << "\n🧪 === RUNNING VEHICLE MONITOR TESTS ===" << std::endl;
        std::cout << std::string(45, '=') << std::endl;
        
        testEngineTemperatureMonitoring();
        testFuelLevelMonitoring();
        testSpeedMonitoring();
        testBrakeWearMonitoring();
        testFuelConsumptionAndRange();
        testSystemCheck();
        
        std::cout << std::string(45, '=') << std::endl;
        std::cout << "🎉 All Vehicle Monitor tests passed!" << std::endl;
    }
};

int main() {
    try {
        VehicleMonitorTest test;
        test.runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
