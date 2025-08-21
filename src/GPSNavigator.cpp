/**
 * @file GPSNavigator.cpp
 * @brief Implementation of the GPSNavigator class
 */

#include "GPSNavigator.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Earth radius in kilometers
static const double EARTH_RADIUS_KM = 6371.0;

// GPSCoordinate implementation
GPSCoordinate::GPSCoordinate(double lat, double lon, double alt)
    : latitude(lat), longitude(lon), altitude(alt) {}

bool GPSCoordinate::isValid() const {
    return (latitude >= -90.0 && latitude <= 90.0) &&
           (longitude >= -180.0 && longitude <= 180.0);
}

// Waypoint implementation
Waypoint::Waypoint(const GPSCoordinate& coord, const std::string& n, const std::string& addr)
    : coordinate(coord), name(n), address(addr) {}

// GPSNavigator implementation
GPSNavigator::GPSNavigator(std::shared_ptr<NotificationManager> notifManager)
    : currentLocation(0.0, 0.0, 0.0), destination(0.0, 0.0, 0.0),
      status(NavigationStatus::IDLE), currentSpeed(0.0), currentHeading(0.0),
      gpsSignalAvailable(true), satelliteCount(8), accuracy(3.0),
      notificationManager(notifManager) {}

void GPSNavigator::updateLocation(const GPSCoordinate& location) {
    if (!location.isValid()) {
        notificationManager->addNotification("Invalid GPS coordinates received", AlertLevel::WARNING);
        return;
    }
    
    currentLocation = location;
    checkGPSSignal();
    
    // Check if we're navigating and update status
    if (status == NavigationStatus::NAVIGATING) {
        double distanceToDestination = getDistanceToDestination();
        if (distanceToDestination < 0.1) { // Within 100 meters
            status = NavigationStatus::ARRIVED;
            notificationManager->addNotification("Destination reached!", AlertLevel::INFO);
        }
    }
}

void GPSNavigator::setDestination(const GPSCoordinate& dest, const std::string& name) {
    if (!dest.isValid()) {
        notificationManager->addNotification("Invalid destination coordinates", AlertLevel::WARNING);
        return;
    }
    
    destination = dest;
    status = NavigationStatus::IDLE;
    
    std::stringstream ss;
    ss << "Destination set: " << name << " (" << formatCoordinate(dest) << ")";
    notificationManager->addNotification(ss.str(), AlertLevel::INFO);
}

void GPSNavigator::startNavigation() {
    if (!destination.isValid()) {
        notificationManager->addNotification("No destination set for navigation", AlertLevel::WARNING);
        return;
    }
    
    if (!gpsSignalAvailable) {
        notificationManager->addNotification("GPS signal unavailable - cannot start navigation", AlertLevel::CRITICAL);
        return;
    }
    
    status = NavigationStatus::NAVIGATING;
    double distance = getDistanceToDestination();
    double eta = getEstimatedTimeToArrival();
    
    std::stringstream ss;
    ss << "Navigation started - Distance: " << std::fixed << std::setprecision(1) 
       << distance << " km, ETA: " << std::fixed << std::setprecision(0) << eta << " min";
    notificationManager->addNotification(ss.str(), AlertLevel::INFO);
}

void GPSNavigator::stopNavigation() {
    status = NavigationStatus::IDLE;
    clearRoute();
    notificationManager->addNotification("Navigation stopped", AlertLevel::INFO);
}

void GPSNavigator::addWaypoint(const Waypoint& waypoint) {
    if (!waypoint.coordinate.isValid()) {
        notificationManager->addNotification("Invalid waypoint coordinates", AlertLevel::WARNING);
        return;
    }
    
    route.push_back(waypoint);
    
    std::stringstream ss;
    ss << "Waypoint added: " << waypoint.name;
    notificationManager->addNotification(ss.str(), AlertLevel::INFO);
}

void GPSNavigator::clearRoute() {
    route.clear();
}

double GPSNavigator::calculateDistance(const GPSCoordinate& coord1, const GPSCoordinate& coord2) const {
    if (!coord1.isValid() || !coord2.isValid()) {
        return -1.0;
    }
    
    // Haversine formula
    double lat1Rad = coord1.latitude * M_PI / 180.0;
    double lat2Rad = coord2.latitude * M_PI / 180.0;
    double deltaLatRad = (coord2.latitude - coord1.latitude) * M_PI / 180.0;
    double deltaLonRad = (coord2.longitude - coord1.longitude) * M_PI / 180.0;
    
    double a = sin(deltaLatRad / 2.0) * sin(deltaLatRad / 2.0) +
               cos(lat1Rad) * cos(lat2Rad) *
               sin(deltaLonRad / 2.0) * sin(deltaLonRad / 2.0);
    
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    return EARTH_RADIUS_KM * c;
}

double GPSNavigator::getDistanceToDestination() const {
    if (!destination.isValid() || !currentLocation.isValid()) {
        return -1.0;
    }
    
    return calculateDistance(currentLocation, destination);
}

double GPSNavigator::getEstimatedTimeToArrival() const {
    double distance = getDistanceToDestination();
    if (distance < 0 || currentSpeed <= 0) {
        return -1.0;
    }
    
    return (distance / currentSpeed) * 60.0; // Convert hours to minutes
}

void GPSNavigator::updateSpeed(double speed) {
    currentSpeed = std::max(0.0, speed);
}

void GPSNavigator::updateHeading(double heading) {
    // Normalize heading to 0-360 degrees
    while (heading < 0) heading += 360.0;
    while (heading >= 360.0) heading -= 360.0;
    currentHeading = heading;
}

void GPSNavigator::updateGPSSignal(int satellites, double acc) {
    satelliteCount = std::max(0, satellites);
    accuracy = std::max(0.0, acc);
    checkGPSSignal();
}

void GPSNavigator::checkGPSSignal() {
    bool previousSignalStatus = gpsSignalAvailable;
    
    gpsSignalAvailable = (satelliteCount >= MIN_SATELLITES && accuracy <= MIN_GPS_ACCURACY);
    
    if (!gpsSignalAvailable && previousSignalStatus) {
        if (status == NavigationStatus::NAVIGATING) {
            status = NavigationStatus::GPS_LOST;
        }
        notificationManager->addNotification("GPS signal lost!", AlertLevel::CRITICAL);
    } else if (gpsSignalAvailable && !previousSignalStatus) {
        if (status == NavigationStatus::GPS_LOST) {
            status = NavigationStatus::NAVIGATING;
        }
        notificationManager->addNotification("GPS signal restored", AlertLevel::INFO);
    }
}

double GPSNavigator::calculateBearing(const GPSCoordinate& from, const GPSCoordinate& to) const {
    if (!from.isValid() || !to.isValid()) {
        return 0.0;
    }
    
    double lat1Rad = from.latitude * M_PI / 180.0;
    double lat2Rad = to.latitude * M_PI / 180.0;
    double deltaLonRad = (to.longitude - from.longitude) * M_PI / 180.0;
    
    double y = sin(deltaLonRad) * cos(lat2Rad);
    double x = cos(lat1Rad) * sin(lat2Rad) - sin(lat1Rad) * cos(lat2Rad) * cos(deltaLonRad);
    
    double bearing = atan2(y, x) * 180.0 / M_PI;
    
    // Normalize to 0-360 degrees
    while (bearing < 0) bearing += 360.0;
    while (bearing >= 360.0) bearing -= 360.0;
    
    return bearing;
}

GPSCoordinate GPSNavigator::getCurrentLocation() const { return currentLocation; }
GPSCoordinate GPSNavigator::getDestination() const { return destination; }
NavigationStatus GPSNavigator::getNavigationStatus() const { return status; }
double GPSNavigator::getCurrentSpeed() const { return currentSpeed; }
double GPSNavigator::getCurrentHeading() const { return currentHeading; }
bool GPSNavigator::isGPSSignalAvailable() const { return gpsSignalAvailable; }
int GPSNavigator::getSatelliteCount() const { return satelliteCount; }
double GPSNavigator::getGPSAccuracy() const { return accuracy; }

void GPSNavigator::displayGPSStatus() const {
    std::cout << "\n🛰️  === GPS STATUS ===" << std::endl;
    std::cout << std::string(35, '=') << std::endl;
    
    // Current location
    std::cout << "📍 Current Location: " << formatCoordinate(currentLocation) << std::endl;
    
    // GPS signal status
    std::cout << "📡 GPS Signal: ";
    if (gpsSignalAvailable) {
        std::cout << "✅ GOOD";
    } else {
        std::cout << "❌ POOR/LOST";
    }
    std::cout << " (" << satelliteCount << " satellites, " 
              << std::fixed << std::setprecision(1) << accuracy << "m accuracy)" << std::endl;
    
    // Speed and heading
    std::cout << "🏎️  Speed: " << std::fixed << std::setprecision(1) << currentSpeed << " km/h" << std::endl;
    std::cout << "🧭 Heading: " << std::fixed << std::setprecision(0) << currentHeading << "°" << std::endl;
    
    // Navigation status
    std::cout << "🗺️  Navigation: " << statusToString(status) << std::endl;
    
    if (destination.isValid()) {
        std::cout << "🎯 Destination: " << formatCoordinate(destination) << std::endl;
        double distance = getDistanceToDestination();
        double eta = getEstimatedTimeToArrival();
        
        if (distance >= 0) {
            std::cout << "📏 Distance: " << std::fixed << std::setprecision(1) << distance << " km" << std::endl;
        }
        if (eta >= 0) {
            std::cout << "⏱️  ETA: " << std::fixed << std::setprecision(0) << eta << " minutes" << std::endl;
        }
    }
    
    std::cout << std::string(35, '=') << std::endl;
}

void GPSNavigator::displayRoute() const {
    if (route.empty()) {
        std::cout << "\n🗺️  No route waypoints set" << std::endl;
        return;
    }
    
    std::cout << "\n🗺️  === ROUTE WAYPOINTS ===" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    
    for (size_t i = 0; i < route.size(); ++i) {
        const auto& waypoint = route[i];
        std::cout << (i + 1) << ". " << waypoint.name << std::endl;
        std::cout << "   📍 " << formatCoordinate(waypoint.coordinate) << std::endl;
        if (!waypoint.address.empty()) {
            std::cout << "   🏠 " << waypoint.address << std::endl;
        }
        
        double distance = calculateDistance(currentLocation, waypoint.coordinate);
        if (distance >= 0) {
            std::cout << "   📏 " << std::fixed << std::setprecision(1) << distance << " km away" << std::endl;
        }
        std::cout << std::endl;
    }
    
    std::cout << std::string(40, '=') << std::endl;
}

void GPSNavigator::simulateGPSUpdate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Simulate small GPS coordinate changes
    std::uniform_real_distribution<> coordVar(-0.001, 0.001);
    std::uniform_real_distribution<> speedVar(-2.0, 5.0);
    std::uniform_real_distribution<> headingVar(-10.0, 10.0);
    std::uniform_int_distribution<> satVar(4, 12);
    std::uniform_real_distribution<> accVar(1.0, 8.0);
    
    GPSCoordinate newLocation(
        currentLocation.latitude + coordVar(gen),
        currentLocation.longitude + coordVar(gen),
        currentLocation.altitude
    );
    
    updateLocation(newLocation);
    updateSpeed(std::max(0.0, currentSpeed + speedVar(gen)));
    updateHeading(currentHeading + headingVar(gen));
    updateGPSSignal(satVar(gen), accVar(gen));
    
    std::cout << "📡 GPS data updated..." << std::endl;
}

std::string GPSNavigator::statusToString(NavigationStatus status) {
    switch (status) {
        case NavigationStatus::IDLE: return "IDLE";
        case NavigationStatus::NAVIGATING: return "NAVIGATING";
        case NavigationStatus::ARRIVED: return "ARRIVED";
        case NavigationStatus::OFF_ROUTE: return "OFF ROUTE";
        case NavigationStatus::GPS_LOST: return "GPS LOST";
        default: return "UNKNOWN";
    }
}

std::string GPSNavigator::formatCoordinate(const GPSCoordinate& coord) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6) << coord.latitude << ", " << coord.longitude;
    if (coord.altitude != 0.0) {
        ss << " (alt: " << std::setprecision(1) << coord.altitude << "m)";
    }
    return ss.str();
}
