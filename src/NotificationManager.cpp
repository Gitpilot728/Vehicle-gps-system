/**
 * @file NotificationManager.cpp
 * @brief Implementation of the NotificationManager class
 */

#include "NotificationManager.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

Notification::Notification(const std::string& msg, AlertLevel lvl)
    : message(msg), level(lvl), timestamp(std::chrono::system_clock::now()) {}

NotificationManager::NotificationManager() : soundEnabled(true) {}

void NotificationManager::addNotification(const std::string& message, AlertLevel level) {
    // Basic input sanitization - remove control characters
    std::string sanitizedMessage = message;
    sanitizedMessage.erase(std::remove_if(sanitizedMessage.begin(), sanitizedMessage.end(),
                          [](char c) { return c < 32 && c != '\t' && c != '\n'; }), sanitizedMessage.end());
    
    notifications.emplace_back(sanitizedMessage, level);    
    // Immediate display for critical alerts
    if (level == AlertLevel::CRITICAL) {
        std::cout << "\n\t\tCRITICAL ALERT: " << sanitizedMessage << std::endl;
        if (soundEnabled) {
            std::cout << "\t*BEEP BEEP BEEP*" << std::endl;
        }
    } else if (level == AlertLevel::WARNING) {
        std::cout << "\n\tWARNING: " << sanitizedMessage << std::endl;
    }
}

void NotificationManager::displayNotifications() const {
    if (notifications.empty()) {
        std::cout << "\tNo notifications." << std::endl;
        return;
    }
    
    std::cout << "\n\t=== NOTIFICATION CENTER ===" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    std::stringstream ss;
    for (const auto& notification : notifications) {
        auto time_t = std::chrono::system_clock::to_time_t(notification.timestamp);
        ss.str("");
        ss.clear();
        ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        
        std::string icon;
        switch (notification.level) {
            case AlertLevel::INFO: icon = "INFO"; break;
            case AlertLevel::WARNING: icon = "WARN"; break;
            case AlertLevel::CRITICAL: icon = "CRIT"; break;
            default: icon = "NOTE"; break;
        }
        
        std::cout << "[" << ss.str() << "] " << icon << ": "
                  << notification.message << std::endl;
    }
    std::cout << std::string(40, '-') << std::endl;
}

void NotificationManager::clearNotifications() {
    notifications.clear();
    std::cout << "\tAll notifications cleared." << std::endl;
}

int NotificationManager::getNotificationCount(AlertLevel level) const {
    return std::count_if(notifications.begin(), notifications.end(),
                        [level](const auto& n) { return n.level == level; });
}

int NotificationManager::getNotificationCount() const {
    return static_cast<int>(notifications.size());
}

void NotificationManager::setSoundEnabled(bool enabled) {
    soundEnabled = enabled;
    std::cout << "\tNotification sounds " << (enabled ? "enabled" : "disabled") << std::endl;
}

bool NotificationManager::hasCriticalAlerts() const {
    return std::any_of(notifications.begin(), notifications.end(),
                      [](const auto& n) { return n.level == AlertLevel::CRITICAL; });
}

std::string NotificationManager::alertLevelToString(AlertLevel level) {
    switch (level) {
        case AlertLevel::INFO: return "INFO";
        case AlertLevel::WARNING: return "WARNING";
        case AlertLevel::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}