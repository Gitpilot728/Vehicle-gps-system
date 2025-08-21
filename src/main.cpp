#include "VehicleMonitor.h"
#include "MediaPlayer.h"
#include "SystemSettings.h"
#include "GPSNavigator.h"
#include "NotificationManager.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <limits>

void displayMenu() {
    std::cout << "\n            VEHICLE SYSTEM MENU     \n" << std::endl;
    std::cout << "........................................................................................................" << std::endl;
    std::cout << "1. Vehicle Monitor Status" << std::endl;
    std::cout << "2. GPS Navigator Status" << std::endl;
    std::cout << "3. Media Player Controls" << std::endl;
    std::cout << "4. System Settings" << std::endl;
    std::cout << "5. View All Notifications" << std::endl;
    std::cout << "6. Simulate Real-time Updates" << std::endl;
    std::cout << "7. GPS Navigation Demo" << std::endl;
    std::cout << "8. Run System Check" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

void gpsNavigationDemo(std::shared_ptr<GPSNavigator> gps) {
    std::cout << "\n                   GPS NAVIGATION DEMO                " << std::endl;    
    // Set current location (example: San Francisco)
    GPSCoordinate currentLoc(37.7749, -122.4194, 50.0);
    gps->updateLocation(currentLoc);
    gps->updateSpeed(45.0);
    gps->updateHeading(90.0);    
    // Add some waypoints
    Waypoint waypoint1(GPSCoordinate(37.7849, -122.4094, 60.0), "Golden Gate Park", "Golden Gate Park, San Francisco, CA");
    Waypoint waypoint2(GPSCoordinate(37.8049, -122.4194, 70.0), "Fisherman's Wharf", "Pier 39, San Francisco, CA");
    gps->addWaypoint(waypoint1);
    gps->addWaypoint(waypoint2);    
    // Set destination (example: Alcatraz Island)
    GPSCoordinate destination(37.8267, -122.4233, 40.0);
    gps->setDestination(destination, "Alcatraz Island");    
    // Start navigation
    gps->startNavigation();
    gps->stopNavigation();

    // Display status
    gps->displayGPSStatus();
    gps->displayRoute();
}
int main() {
    std::cout << "          Vehicle Monitoring System with GPS Navigation" << std::endl;
    std::cout << "..........................................................................................................................................." << std::endl;    
    // Create shared notification manager
    auto notificationManager = std::make_shared<NotificationManager>();    
    // Create system components
    auto vehicleMonitor = std::make_shared<VehicleMonitor>(notificationManager);
    auto gpsNavigator = std::make_shared<GPSNavigator>(notificationManager);
    auto mediaPlayer = std::make_shared<MediaPlayer>(notificationManager);
    auto systemSettings = std::make_shared<SystemSettings>(notificationManager);    
    // Initialize with some demo data
    mediaPlayer->loadDemoPlaylist();    
    // Set initial GPS location (example: Los Angeles)
    GPSCoordinate initialLocation(34.0522, -118.2437, 100.0);
    gpsNavigator->updateLocation(initialLocation);
    gpsNavigator->updateSpeed(60.0);
    gpsNavigator->updateHeading(45.0);
    gpsNavigator->updateGPSSignal(8, 3.5);    
    int choice;
    do {
        displayMenu();        
        // Input validation
        if (!(std::cin >> choice)) {
            std::cout << "   Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }        
        switch (choice) {
            case 1:
                vehicleMonitor->displayStatus();
                break;                
            case 2:
                gpsNavigator->displayGPSStatus();
                break;                
            case 3:
                std::cout << "\n\tMedia Player Status:" << std::endl;
                mediaPlayer->displayCurrentTrack();
                mediaPlayer->displayPlaylist();
                break;                
            case 4:
                systemSettings->displaySettings();
                break;                
            case 5:
                notificationManager->displayNotifications();
                break;                
            case 6:
                std::cout << "\n     Simulating real-time updates..." << std::endl;
                vehicleMonitor->simulateRealTimeUpdate();
                gpsNavigator->simulateGPSUpdate();
                std::cout << "Updates completed!" << std::endl;
                break;                
            case 7:
                gpsNavigationDemo(gpsNavigator);
                break;                
            case 8:
                vehicleMonitor->performSystemCheck();
                break;                
            case 0:
                std::cout << "\n Shutting down vehicle system..." << std::endl;
                break;                
            default:
                std::cout << " Invalid option. Please try again." << std::endl;
                break;
        }        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }        
    } while (choice != 0);    
    std::cout << "  Vehicle system shutdown complete." << std::endl;
    return 0;
}
