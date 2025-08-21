/**
 * @file test_integration.cpp
 * @brief Integration tests for the complete vehicle system
 */

#include "VehicleMonitor.h"
#include "GPSNavigator.h"
#include "MediaPlayer.h"
#include "SystemSettings.h"
#include "NotificationManager.h"
#include <iostream>
#include <memory>
#include <cassert>

class IntegrationTest {
private:
    std::shared_ptr<NotificationManager> notificationManager;
    std::shared_ptr<VehicleMonitor> vehicleMonitor;
    std::shared_ptr<GPSNavigator> gpsNavigator;
    std::shared_ptr<MediaPlayer> mediaPlayer;
    std::shared_ptr<SystemSettings> systemSettings;
    
    void assertTrue(bool condition, const std::string& message) {
        if (!condition) {
            std::cout << "❌ FAIL: " << message << std::endl;
            throw std::runtime_error("Test assertion failed: " + message);
        }
    }
    
public:
    IntegrationTest() {
        notificationManager = std::make_shared<NotificationManager>();
        vehicleMonitor = std::make_shared<VehicleMonitor>(notificationManager);
        gpsNavigator = std::make_shared<GPSNavigator>(notificationManager);
        mediaPlayer = std::make_shared<MediaPlayer>(notificationManager);
        systemSettings = std::make_shared<SystemSettings>(notificationManager);
    }
    
    void testSystemInitialization() {
        std::cout << "🧪 Testing system initialization..." << std::endl;
        
        // All components should be properly initialized
        assertTrue(vehicleMonitor != nullptr, "Vehicle monitor should be initialized");
        assertTrue(gpsNavigator != nullptr, "GPS navigator should be initialized");
        assertTrue(mediaPlayer != nullptr, "Media player should be initialized");
        assertTrue(systemSettings != nullptr, "System settings should be initialized");
        assertTrue(notificationManager != nullptr, "Notification manager should be initialized");
        
        std::cout << "✅ System initialization tests passed" << std::endl;
    }
    
    void testNotificationIntegration() {
        std::cout << "🧪 Testing notification system integration..." << std::endl;
        
        // Clear existing notifications
        notificationManager->clearNotifications();
        int initialCount = notificationManager->getNotificationCount();
        
        // Trigger various alerts from different components
        vehicleMonitor->setEngineTemperature(110.0); // Should trigger critical alert
        vehicleMonitor->setFuelLevel(3.0); // Should trigger critical alert
        
        gpsNavigator->updateGPSSignal(2, 15.0); // Should trigger GPS signal warning
        
        // Check that notifications were generated
        int finalCount = notificationManager->getNotificationCount();
        assertTrue(finalCount > initialCount, "Components should generate notifications");
        
        std::cout << "✅ Notification integration tests passed" << std::endl;
    }
    
    void testVehicleGPSIntegration() {
        std::cout << "🧪 Testing vehicle and GPS integration..." << std::endl;
        
        // Set vehicle speed
        vehicleMonitor->setCurrentSpeed(75.0);
        
        // Update GPS with same speed and ensure good signal
        gpsNavigator->updateGPSSignal(8, 3.0);
        gpsNavigator->updateSpeed(75.0);
        
        // Both should report the same speed
        assertTrue(vehicleMonitor->getCurrentSpeed() == gpsNavigator->getCurrentSpeed(),
                  "Vehicle and GPS speed should be synchronized");
        
        // Test navigation scenario
        GPSCoordinate destination(34.0522, -118.2437);
        gpsNavigator->setDestination(destination, "Los Angeles");
        gpsNavigator->startNavigation();
        
        assertTrue(gpsNavigator->getNavigationStatus() == NavigationStatus::NAVIGATING,
                  "Navigation should start successfully");
        
        std::cout << "✅ Vehicle-GPS integration tests passed" << std::endl;
    }
    
    void testCompleteSystemScenario() {
        std::cout << "🧪 Testing complete system scenario..." << std::endl;
        
        // Simulate a complete driving scenario
        
        // 1. Start the vehicle system
        systemSettings->setSystemVolume(75);
        systemSettings->setDisplayBrightness(80);
        
        // 2. Load media
        mediaPlayer->loadDemoPlaylist();
        mediaPlayer->play();
        
        // 3. Set initial vehicle parameters
        vehicleMonitor->setEngineTemperature(85.0);
        vehicleMonitor->setFuelLevel(80.0);
        vehicleMonitor->setCurrentSpeed(0.0);
        vehicleMonitor->setBrakeWearLevel(90.0);
        
        // 4. Set GPS location and start navigation
        GPSCoordinate startLocation(37.7749, -122.4194); // San Francisco
        gpsNavigator->updateLocation(startLocation);
        gpsNavigator->updateSpeed(0.0);
        
        GPSCoordinate destination(34.0522, -118.2437); // Los Angeles
        gpsNavigator->setDestination(destination, "Los Angeles");
        gpsNavigator->startNavigation();
        
        // 5. Simulate driving
        vehicleMonitor->setCurrentSpeed(65.0);
        gpsNavigator->updateSpeed(65.0);
        gpsNavigator->updateHeading(180.0); // Heading south
        
        // 6. Perform system check
        vehicleMonitor->performSystemCheck();
        
        // Verify system state
        assertTrue(mediaPlayer->getState() == PlayerState::PLAYING, "Media should be playing");
        assertTrue(gpsNavigator->getNavigationStatus() == NavigationStatus::NAVIGATING, "Should be navigating");
        assertTrue(vehicleMonitor->getCurrentSpeed() == 65.0, "Vehicle speed should be 65 km/h");
        assertTrue(gpsNavigator->getCurrentSpeed() == 65.0, "GPS speed should be 65 km/h");
        
        std::cout << "✅ Complete system scenario tests passed" << std::endl;
    }
    
    void testErrorHandling() {
        std::cout << "🧪 Testing error handling..." << std::endl;
        
        // Test invalid GPS coordinates
        GPSCoordinate invalidCoord(91.0, 181.0); // Invalid lat/lon
        gpsNavigator->updateLocation(invalidCoord);
        
        // Test boundary conditions
        vehicleMonitor->setFuelLevel(-10.0); // Should clamp to 0
        assertTrue(vehicleMonitor->getFuelLevel() == 0.0, "Fuel level should be clamped to 0");
        
        vehicleMonitor->setFuelLevel(110.0); // Should clamp to 100
        assertTrue(vehicleMonitor->getFuelLevel() == 100.0, "Fuel level should be clamped to 100");
        
        // Test GPS signal loss
        gpsNavigator->updateGPSSignal(1, 50.0); // Poor signal
        assertTrue(!gpsNavigator->isGPSSignalAvailable(), "GPS signal should be unavailable");
        
        std::cout << "✅ Error handling tests passed" << std::endl;
    }
    
    void runAllTests() {
        std::cout << "\n🧪 === RUNNING INTEGRATION TESTS ===" << std::endl;
        std::cout << std::string(45, '=') << std::endl;
        
        testSystemInitialization();
        testNotificationIntegration();
        testVehicleGPSIntegration();
        testCompleteSystemScenario();
        testErrorHandling();
        
        std::cout << std::string(45, '=') << std::endl;
        std::cout << "🎉 All integration tests passed!" << std::endl;
    }
};

int main() {
    try {
        IntegrationTest test;
        test.runAllTests();
        return 0;
    } catch (const std::runtime_error& e) {
        std::cout << "❌ Integration test failed: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "❌ Integration test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
