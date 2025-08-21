/**
 * @file SystemSettings.cpp
 * @brief Implementation of the SystemSettings class
 */

#include "SystemSettings.h"
#include <iostream>
#include <iomanip>

SystemSettings::SystemSettings(std::shared_ptr<NotificationManager> notifManager)
    : systemVolume(50), displayBrightness(75), theme(DisplayTheme::AUTO),
      language(Language::ENGLISH), nightModeEnabled(false), voiceGuidanceEnabled(true),
      notificationSoundsEnabled(true), timeFormat("12h"), temperatureUnit("C"),
      notificationManager(notifManager) {}

void SystemSettings::setSystemVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    
    systemVolume = volume;
    std::cout << "🔊 System volume set to " << volume << "%" << std::endl;
    
    if (volume == 0) {
        notificationManager->addNotification("System muted", AlertLevel::INFO);
    }
}

int SystemSettings::getSystemVolume() const {
    return systemVolume;
}

void SystemSettings::setDisplayBrightness(int brightness) {
    if (brightness < 0) brightness = 0;
    if (brightness > 100) brightness = 100;
    
    displayBrightness = brightness;
    std::cout << "💡 Display brightness set to " << brightness << "%" << std::endl;
    
    if (brightness < 20) {
        notificationManager->addNotification("Low brightness - may affect visibility", AlertLevel::WARNING);
    }
}

int SystemSettings::getDisplayBrightness() const {
    return displayBrightness;
}

void SystemSettings::setDisplayTheme(DisplayTheme newTheme) {
    theme = newTheme;
    std::cout << " Display theme changed to: " << themeToString(newTheme) << std::endl;
    notificationManager->addNotification("Theme changed to " + themeToString(newTheme), AlertLevel::INFO);
}

DisplayTheme SystemSettings::getDisplayTheme() const {
    return theme;
}

void SystemSettings::setLanguage(Language lang) {
    language = lang;
    std::cout << " Language changed to: " << languageToString(lang) << std::endl;
    notificationManager->addNotification("Language changed to " + languageToString(lang), AlertLevel::INFO);
}

Language SystemSettings::getLanguage() const {
    return language;
}

void SystemSettings::setNightMode(bool enabled) {
    nightModeEnabled = enabled;
    std::cout << "🌙 Night mode " << (enabled ? "enabled" : "disabled") << std::endl;
    
    if (enabled) {
        // Automatically adjust brightness for night mode
        if (displayBrightness > 30) {
            setDisplayBrightness(30);
            notificationManager->addNotification("Brightness auto-adjusted for night mode", AlertLevel::INFO);
        }
    }
}

bool SystemSettings::isNightModeEnabled() const {
    return nightModeEnabled;
}

void SystemSettings::setVoiceGuidance(bool enabled) {
    voiceGuidanceEnabled = enabled;
    std::cout << "  Voice guidance " << (enabled ? "enabled" : "disabled") << std::endl;
}

bool SystemSettings::isVoiceGuidanceEnabled() const {
    return voiceGuidanceEnabled;
}

void SystemSettings::setNotificationSounds(bool enabled) {
    notificationSoundsEnabled = enabled;
    notificationManager->setSoundEnabled(enabled);
    std::cout << "🔔 Notification sounds " << (enabled ? "enabled" : "disabled") << std::endl;
}

bool SystemSettings::areNotificationSoundsEnabled() const {
    return notificationSoundsEnabled;
}

void SystemSettings::setTimeFormat(const std::string& format) {
    if (format == "12h" || format == "24h") {
        timeFormat = format;
        std::cout << "🕐 Time format set to: " << format << std::endl;
    } else {
        notificationManager->addNotification("Invalid time format. Use '12h' or '24h'", AlertLevel::WARNING);
    }
}

std::string SystemSettings::getTimeFormat() const {
    return timeFormat;
}

void SystemSettings::setTemperatureUnit(const std::string& unit) {
    if (unit == "C" || unit == "F") {
        temperatureUnit = unit;
        std::cout << "🌡️  Temperature unit set to: °" << unit << std::endl;
    } else {
        notificationManager->addNotification("Invalid temperature unit. Use 'C' or 'F'", AlertLevel::WARNING);
    }
}

std::string SystemSettings::getTemperatureUnit() const {
    return temperatureUnit;
}

void SystemSettings::displaySettings() const {
    std::cout << "\n⚙️  === SYSTEM SETTINGS ===" << std::endl;
    std::cout << std::string(35, '=') << std::endl;
    
    // Audio Settings
    std::cout << "🔊 Audio Settings:" << std::endl;
    std::cout << "   System Volume: " << systemVolume << "%" << std::endl;
    std::cout << "   Notification Sounds: " << (notificationSoundsEnabled ? "ON" : "OFF") << std::endl;
    std::cout << "   Voice Guidance: " << (voiceGuidanceEnabled ? "ON" : "OFF") << std::endl;
    
    // Display Settings
    std::cout << "\n💡 Display Settings:" << std::endl;
    std::cout << "   Brightness: " << displayBrightness << "%" << std::endl;
    std::cout << "   Theme: " << themeToString(theme) << std::endl;
    std::cout << "   Night Mode: " << (nightModeEnabled ? "ON" : "OFF") << std::endl;
    
    // System Settings
    std::cout << "\n🌐 System Settings:" << std::endl;
    std::cout << "   Language: " << languageToString(language) << std::endl;
    std::cout << "   Time Format: " << timeFormat << std::endl;
    std::cout << "   Temperature Unit: °" << temperatureUnit << std::endl;
    
    std::cout << std::string(35, '=') << std::endl;
}

void SystemSettings::resetToDefaults() {
    systemVolume = 50;
    displayBrightness = 75;
    theme = DisplayTheme::AUTO;
    language = Language::ENGLISH;
    nightModeEnabled = false;
    voiceGuidanceEnabled = true;
    notificationSoundsEnabled = true;
    timeFormat = "12h";
    temperatureUnit = "C";
    
    std::cout << "🔄 Settings reset to defaults" << std::endl;
    notificationManager->addNotification("All settings reset to defaults", AlertLevel::INFO);
}

void SystemSettings::saveSettings() {
    // Simulate saving to file
    std::cout << "💾 Settings saved successfully" << std::endl;
    notificationManager->addNotification("Settings saved", AlertLevel::INFO);
}

void SystemSettings::loadSettings() {
    // Simulate loading from file
    std::cout << "📂 Settings loaded successfully" << std::endl;
    notificationManager->addNotification("Settings loaded", AlertLevel::INFO);
}

std::string SystemSettings::themeToString(DisplayTheme theme) {
    switch (theme) {
        case DisplayTheme::LIGHT: return "Light";
        case DisplayTheme::DARK: return "Dark";
        case DisplayTheme::AUTO: return "Auto";
        default: return "Unknown";
    }
}

std::string SystemSettings::languageToString(Language lang) {
    switch (lang) {
        case Language::ENGLISH: return "English";
        case Language::SPANISH: return "Español";
        case Language::FRENCH: return "Français";
        case Language::GERMAN: return "Deutsch";
        case Language::JAPANESE: return "日本語";
        default: return "Unknown";
    }
}
