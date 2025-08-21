/**
 * @file GPSNavigator.h
 * @brief GPS navigation and location tracking system
 * @author AI-Enhanced Development System
 */

#ifndef GPS_NAVIGATOR_H
#define GPS_NAVIGATOR_H

#include "NotificationManager.h"
#include <memory>
#include <string>
#include <vector>
#include <cmath>

/**
 * @brief Structure representing GPS coordinates
 */
struct GPSCoordinate {
    double latitude;    ///< Latitude in decimal degrees
    double longitude;   ///< Longitude in decimal degrees
    double altitude;    ///< Altitude in meters
    
    /**
     * @brief Constructor for GPS coordinate
     * @param lat Latitude
     * @param lon Longitude
     * @param alt Altitude (default 0.0)
     */
    GPSCoordinate(double lat = 0.0, double lon = 0.0, double alt = 0.0);
    
    /**
     * @brief Check if coordinates are valid
     * @return True if coordinates are within valid ranges
     */
    bool isValid() const;
};

/**
 * @brief Structure representing a waypoint
 */
struct Waypoint {
    GPSCoordinate coordinate;   ///< GPS coordinate of waypoint
    std::string name;          ///< Name/description of waypoint
    std::string address;       ///< Address of waypoint
    
    /**
     * @brief Constructor for waypoint
     * @param coord GPS coordinate
     * @param n Name
     * @param addr Address
     */
    Waypoint(const GPSCoordinate& coord, const std::string& n, const std::string& addr);
};

/**
 * @brief Enumeration for navigation status
 */
enum class NavigationStatus {
    IDLE,           ///< No active navigation
    NAVIGATING,     ///< Currently navigating
    ARRIVED,        ///< Arrived at destination
    OFF_ROUTE,      ///< Vehicle is off the planned route
    GPS_LOST        ///< GPS signal lost
};

/**
 * @brief GPS navigation and location tracking system
 * 
 * Provides GPS functionality including location tracking, route planning,
 * distance calculations, and turn-by-turn navigation guidance.
 */
class GPSNavigator {
private:
    GPSCoordinate currentLocation;                          ///< Current GPS position
    GPSCoordinate destination;                              ///< Current destination
    std::vector<Waypoint> route;                           ///< Current route waypoints
    NavigationStatus status;                                ///< Current navigation status
    double currentSpeed;                                    ///< Current speed in km/h
    double currentHeading;                                  ///< Current heading in degrees (0-360)
    bool gpsSignalAvailable;                               ///< GPS signal status
    int satelliteCount;                                    ///< Number of visible satellites
    double accuracy;                                       ///< GPS accuracy in meters
    std::shared_ptr<NotificationManager> notificationManager;   ///< Notification system
    
    // Constants
    static constexpr double EARTH_RADIUS_KM = 6371.0;     ///< Earth radius in kilometers
    static constexpr double MIN_GPS_ACCURACY = 10.0;      ///< Minimum acceptable GPS accuracy
    static constexpr int MIN_SATELLITES = 4;              ///< Minimum satellites for good fix
    
    /**
     * @brief Check GPS signal quality and update status
     */
    void checkGPSSignal();
    
    /**
     * @brief Calculate bearing between two coordinates
     * @param from Starting coordinate
     * @param to Ending coordinate
     * @return Bearing in degrees (0-360)
     */
    double calculateBearing(const GPSCoordinate& from, const GPSCoordinate& to) const;
    
public:
    /**
     * @brief Constructor with notification manager
     * @param notifManager Shared pointer to notification manager
     */
    explicit GPSNavigator(std::shared_ptr<NotificationManager> notifManager);
    
    /**
     * @brief Update current GPS location
     * @param location New GPS coordinate
     */
    void updateLocation(const GPSCoordinate& location);
    
    /**
     * @brief Set destination for navigation
     * @param dest Destination coordinate
     * @param name Optional destination name
     */
    void setDestination(const GPSCoordinate& dest, const std::string& name = "Destination");
    
    /**
     * @brief Start navigation to current destination
     */
    void startNavigation();
    
    /**
     * @brief Stop current navigation
     */
    void stopNavigation();
    
    /**
     * @brief Add waypoint to current route
     * @param waypoint Waypoint to add
     */
    void addWaypoint(const Waypoint& waypoint);
    
    /**
     * @brief Clear all waypoints from route
     */
    void clearRoute();
    
    /**
     * @brief Calculate distance between two coordinates using Haversine formula
     * @param coord1 First coordinate
     * @param coord2 Second coordinate
     * @return Distance in kilometers
     */
    double calculateDistance(const GPSCoordinate& coord1, const GPSCoordinate& coord2) const;
    
    /**
     * @brief Get distance to destination
     * @return Distance in kilometers, -1 if no destination set
     */
    double getDistanceToDestination() const;
    
    /**
     * @brief Get estimated time to arrival
     * @return ETA in minutes, -1 if cannot calculate
     */
    double getEstimatedTimeToArrival() const;
    
    /**
     * @brief Update current speed
     * @param speed Speed in km/h
     */
    void updateSpeed(double speed);
    
    /**
     * @brief Update current heading
     * @param heading Heading in degrees (0-360)
     */
    void updateHeading(double heading);
    
    /**
     * @brief Update GPS signal information
     * @param satellites Number of visible satellites
     * @param acc GPS accuracy in meters
     */
    void updateGPSSignal(int satellites, double acc);
    
    /**
     * @brief Get current location
     * @return Current GPS coordinate
     */
    GPSCoordinate getCurrentLocation() const;
    
    /**
     * @brief Get current destination
     * @return Destination coordinate
     */
    GPSCoordinate getDestination() const;
    
    /**
     * @brief Get current navigation status
     * @return Navigation status
     */
    NavigationStatus getNavigationStatus() const;
    
    /**
     * @brief Get current speed
     * @return Speed in km/h
     */
    double getCurrentSpeed() const;
    
    /**
     * @brief Get current heading
     * @return Heading in degrees
     */
    double getCurrentHeading() const;
    
    /**
     * @brief Check if GPS signal is available
     * @return True if GPS signal is good
     */
    bool isGPSSignalAvailable() const;
    
    /**
     * @brief Get number of visible satellites
     * @return Satellite count
     */
    int getSatelliteCount() const;
    
    /**
     * @brief Get GPS accuracy
     * @return Accuracy in meters
     */
    double getGPSAccuracy() const;
    
    /**
     * @brief Display current GPS status
     */
    void displayGPSStatus() const;
    
    /**
     * @brief Display current route information
     */
    void displayRoute() const;
    
    /**
     * @brief Simulate GPS data update (for demonstration)
     */
    void simulateGPSUpdate();
    
    /**
     * @brief Convert navigation status to string
     * @param status Status to convert
     * @return String representation
     */
    static std::string statusToString(NavigationStatus status);
    
    /**
     * @brief Format coordinate as string
     * @param coord Coordinate to format
     * @return Formatted string
     */
    static std::string formatCoordinate(const GPSCoordinate& coord);
};

#endif // GPS_NAVIGATOR_H
