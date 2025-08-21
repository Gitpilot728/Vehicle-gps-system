/**
 * @file NotificationManager.h
 * @brief Notification management system for vehicle alerts and infotainment messages
 * @author AI-Enhanced Development System
 */

#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>

/**
 * @brief Enumeration for different alert severity levels
 */
enum class AlertLevel {
    INFO,       ///< Informational messages
    WARNING,    ///< Warning messages requiring attention
    CRITICAL    ///< Critical alerts requiring immediate action
};

/**
 * @brief Structure representing a notification/alert
 */
struct Notification {
    std::string message;                                    ///< Alert message content
    AlertLevel level;                                       ///< Severity level
    std::chrono::system_clock::time_point timestamp;       ///< When alert was created
    
    /**
     * @brief Constructor for Notification
     * @param msg Message content
     * @param lvl Alert severity level
     */
    Notification(const std::string& msg, AlertLevel lvl);
};

/**
 * @brief Central notification management system
 * 
 * Handles all alerts, warnings, and informational messages throughout the system.
 * Provides logging capabilities and different display methods based on severity.
 */
class NotificationManager {
private:
    std::vector<Notification> notifications;    ///< Storage for all notifications
    bool soundEnabled;                          ///< Whether alert sounds are enabled
    
public:
    /**
     * @brief Default constructor
     */
    NotificationManager();
    
    /**
     * @brief Add a new notification to the system
     * @param message The notification message
     * @param level The severity level of the notification
     */
    void addNotification(const std::string& message, AlertLevel level);
    
    /**
     * @brief Display all pending notifications
     */
    void displayNotifications() const;
    
    /**
     * @brief Clear all notifications from the system
     */
    void clearNotifications();
    
    /**
     * @brief Get count of notifications by severity level
     * @param level The severity level to count
     * @return Number of notifications at specified level
     */
    int getNotificationCount(AlertLevel level) const;
    
    /**
     * @brief Get total count of all notifications
     * @return Total number of notifications
     */
    int getNotificationCount() const;
    
    /**
     * @brief Enable or disable notification sounds
     * @param enabled True to enable sounds, false to disable
     */
    void setSoundEnabled(bool enabled);
    
    /**
     * @brief Check if there are any critical alerts
     * @return True if critical alerts exist, false otherwise
     */
    bool hasCriticalAlerts() const;
    
    /**
     * @brief Get string representation of alert level
     * @param level The alert level to convert
     * @return String representation of the level
     */
    static std::string alertLevelToString(AlertLevel level);
};

#endif // NOTIFICATION_MANAGER_H
