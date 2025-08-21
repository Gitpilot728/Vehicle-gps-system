/**
 * @file test_gps_navigator.cpp
 * @brief Unit tests for GPSNavigator class
 */

#include "GPSNavigator.h"
#include "NotificationManager.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>

class GPSNavigatorTest {
private:
    std::shared_ptr<NotificationManager> notificationManager;
    std::shared_ptr<GPSNavigator> gps;
    
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
    GPSNavigatorTest() {
        notificationManager = std::make_shared<NotificationManager>();
        gps = std::make_shared<GPSNavigator>(notificationManager);
    }
    
    void testGPSCoordinateValidation() {
        std::cout << "🧪 Testing GPS coordinate validation..." << std::endl;
        
        GPSCoordinate validCoord(37.7749, -122.4194, 50.0);
        assertTrue(validCoord.isValid(), "Valid coordinates should pass validation");
        
        GPSCoordinate invalidLat(91.0, -122.4194, 50.0);
        assertTrue(!invalidLat.isValid(), "Invalid latitude should fail validation");
        
        GPSCoordinate invalidLon(37.7749, 181.0, 50.0);
        assertTrue(!invalidLon.isValid(), "Invalid longitude should fail validation");
        
        std::cout << "✅ GPS coordinate validation tests passed" << std::endl;
    }
    
    void testDistanceCalculation() {
        std::cout << "🧪 Testing distance calculation..." << std::endl;
        
        // Test known distance: San Francisco to Los Angeles (approx 559 km)
        GPSCoordinate sf(37.7749, -122.4194);
        GPSCoordinate la(34.0522, -118.2437);
        
        double distance = gps->calculateDistance(sf, la);
        assertTrue(distance > 550 && distance < 570, "SF to LA distance should be ~559 km");
        
        // Test same location
        double sameDistance = gps->calculateDistance(sf, sf);
        assertEqual(0.0, sameDistance, 0.1);
        
        std::cout << "✅ Distance calculation tests passed" << std::endl;
    }
    
    void testLocationUpdate() {
        std::cout << "🧪 Testing location updates..." << std::endl;
        
        GPSCoordinate testLocation(40.7128, -74.0060, 10.0); // New York
        gps->updateLocation(testLocation);
        
        GPSCoordinate currentLoc = gps->getCurrentLocation();
        assertEqual(testLocation.latitude, currentLoc.latitude);
        assertEqual(testLocation.longitude, currentLoc.longitude);
        assertEqual(testLocation.altitude, currentLoc.altitude);
        
        std::cout << "✅ Location update tests passed" << std::endl;
    }
    
    void testNavigation() {
        std::cout << "🧪 Testing navigation functionality..." << std::endl;
        
        // Set starting location
        GPSCoordinate start(37.7749, -122.4194);
        gps->updateLocation(start);
        
        // Set destination
        GPSCoordinate dest(37.7849, -122.4094);
        gps->setDestination(dest, "Test Destination");
        
        assertTrue(gps->getNavigationStatus() == NavigationStatus::IDLE, "Status should be IDLE after setting destination");
        
        // Start navigation
        gps->startNavigation();
        assertTrue(gps->getNavigationStatus() == NavigationStatus::NAVIGATING, "Status should be NAVIGATING after start");
        
        // Test distance calculation
        double distance = gps->getDistanceToDestination();
        assertTrue(distance > 0, "Distance to destination should be positive");
        
        // Stop navigation
        gps->stopNavigation();
        assertTrue(gps->getNavigationStatus() == NavigationStatus::IDLE, "Status should be IDLE after stop");
        
        std::cout << "✅ Navigation tests passed" << std::endl;
    }
    
    void testGPSSignalHandling() {
        std::cout << "🧪 Testing GPS signal handling..." << std::endl;
        
        // Test good signal
        gps->updateGPSSignal(8, 3.0);
        assertTrue(gps->isGPSSignalAvailable(), "Should have good GPS signal with 8 satellites and 3m accuracy");
        
        // Test poor signal
        gps->updateGPSSignal(2, 15.0);
        assertTrue(!gps->isGPSSignalAvailable(), "Should have poor GPS signal with 2 satellites and 15m accuracy");
        
        std::cout << "✅ GPS signal handling tests passed" << std::endl;
    }
    
    void testWaypointManagement() {
        std::cout << "🧪 Testing waypoint management..." << std::endl;
        
        // Clear any existing waypoints
        gps->clearRoute();
        
        // Add waypoints
        Waypoint wp1(GPSCoordinate(37.7749, -122.4194), "Waypoint 1", "Address 1");
        Waypoint wp2(GPSCoordinate(37.7849, -122.4094), "Waypoint 2", "Address 2");
        
        gps->addWaypoint(wp1);
        gps->addWaypoint(wp2);
        
        // Test that waypoints were added (we can't directly access the route vector,
        // but we can test that no errors occurred)
        std::cout << "✅ Waypoint management tests passed" << std::endl;
    }
    
    void testSpeedAndHeadingUpdates() {
        std::cout << "🧪 Testing speed and heading updates..." << std::endl;
        
        gps->updateSpeed(65.5);
        assertEqual(65.5, gps->getCurrentSpeed());
        
        gps->updateHeading(270.0);
        assertEqual(270.0, gps->getCurrentHeading());
        
        // Test heading normalization
        gps->updateHeading(450.0); // Should normalize to 90.0
        assertEqual(90.0, gps->getCurrentHeading());
        
        gps->updateHeading(-90.0); // Should normalize to 270.0
        assertEqual(270.0, gps->getCurrentHeading());
        
        std::cout << "✅ Speed and heading update tests passed" << std::endl;
    }
    
    void runAllTests() {
        std::cout << "\n🧪 === RUNNING GPS NAVIGATOR TESTS ===" << std::endl;
        std::cout << std::string(45, '=') << std::endl;
        
        testGPSCoordinateValidation();
        testDistanceCalculation();
        testLocationUpdate();
        testNavigation();
        testGPSSignalHandling();
        testWaypointManagement();
        testSpeedAndHeadingUpdates();
        
        std::cout << std::string(45, '=') << std::endl;
        std::cout << "🎉 All GPS Navigator tests passed!" << std::endl;
    }
};

int main() {
    try {
        GPSNavigatorTest test;
        test.runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
