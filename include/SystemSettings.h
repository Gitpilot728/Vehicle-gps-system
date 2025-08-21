/**
 * @file SystemSettings.h
 * @brief System configuration and settings management
 * @author AI-Enhanced Development System
 */

#ifndef SYSTEM_SETTINGS_H
#define SYSTEM_SETTINGS_H

#include <string>
#include <memory>
#include "NotificationManager.h"

/**
 * @brief Enumeration for display themes
 */
enum class DisplayTheme {
    LIGHT,      ///< Light theme
    DARK,       ///< Dark theme
    AUTO        ///< Automatic theme based on time
};

/**
 * @brief Enumeration for language options
 */
enum class Language {
    ENGLISH,    ///< English
    SPANISH,    ///< Spanish
    FRENCH,     ///< French
    GERMAN,     ///< German
    JAPANESE    ///< Japanese
};

/**
 * @brief System settings and configuration management
 * 
 * Manages user-configurable settings including display preferences, audio settings,
 * and system behavior options.
 */
class SystemSettings {
private:
    int systemVolume;                                       ///< Master system volume (0-100)
    int displayBrightness;                                  ///< Display brightness (0-100)
    DisplayTheme theme;                                     ///< Current display theme
    Language language;                                      ///< System language
    bool nightModeEnabled;                                  ///< Night mode status
    bool voiceGuidanceEnabled;                              ///< Voice guidance for navigation
    bool notificationSoundsEnabled;                         ///< Notification sound status
    std::string timeFormat;                                 ///< Time format (12h/24h)
    std::string temperatureUnit;                            ///< Temperature unit (C/F)
    std::shared_ptr<NotificationManager> notificationManager;   ///< Notification system
    
public:
    /**
     * @brief Constructor with notification manager
     * @param notifManager Shared pointer to notification manager
     */
    explicit SystemSettings(std::shared_ptr<NotificationManager> notifManager);
    
    /**
     * @brief Set system volume
     * @param volume Volume level (0-100)
     */
    void setSystemVolume(int volume);
    
    /**
     * @brief Get system volume
     * @return Current volume level
     */
    int getSystemVolume() const;
    
    /**
     * @brief Set display brightness
     * @param brightness Brightness level (0-100)
     */
    void setDisplayBrightness(int brightness);
    
    /**
     * @brief Get display brightness
     * @return Current brightness level
     */
    int getDisplayBrightness() const;
    
    /**
     * @brief Set display theme
     * @param newTheme Theme to apply
     */
    void setDisplayTheme(DisplayTheme newTheme);
    
    /**
     * @brief Get current display theme
     * @return Current theme
     */
    DisplayTheme getDisplayTheme() const;
    
    /**
     * @brief Set system language
     * @param lang Language to set
     */
    void setLanguage(Language lang);
    
    /**
     * @brief Get current system language
     * @return Current language
     */
    Language getLanguage() const;
    
    /**
     * @brief Enable or disable night mode
     * @param enabled True to enable night mode
     */
    void setNightMode(bool enabled);
    
    /**
     * @brief Check if night mode is enabled
     * @return True if night mode is active
     */
    bool isNightModeEnabled() const;
    
    /**
     * @brief Enable or disable voice guidance
     * @param enabled True to enable voice guidance
     */
    void setVoiceGuidance(bool enabled);
    
    /**
     * @brief Check if voice guidance is enabled
     * @return True if voice guidance is active
     */
    bool isVoiceGuidanceEnabled() const;
    
    /**
     * @brief Enable or disable notification sounds
     * @param enabled True to enable notification sounds
     */
    void setNotificationSounds(bool enabled);
    
    /**
     * @brief Check if notification sounds are enabled
     * @return True if notification sounds are active
     */
    bool areNotificationSoundsEnabled() const;
    
    /**
     * @brief Set time format
     * @param format Time format ("12h" or "24h")
     */
    void setTimeFormat(const std::string& format);
    
    /**
     * @brief Get current time format
     * @return Current time format
     */
    std::string getTimeFormat() const;
    
    /**
     * @brief Set temperature unit
     * @param unit Temperature unit ("C" or "F")
     */
    void setTemperatureUnit(const std::string& unit);
    
    /**
     * @brief Get current temperature unit
     * @return Current temperature unit
     */
    std::string getTemperatureUnit() const;
    
    /**
     * @brief Display all current settings
     */
    void displaySettings() const;
    
    /**
     * @brief Reset all settings to defaults
     */
    void resetToDefaults();
    
    /**
     * @brief Save settings to file (simulated)
     */
    void saveSettings();
    
    /**
     * @brief Load settings from file (simulated)
     */
    void loadSettings();
    
    /**
     * @brief Convert theme enum to string
     * @param theme Theme to convert
     * @return String representation
     */
    static std::string themeToString(DisplayTheme theme);
    
    /**
     * @brief Convert language enum to string
     * @param lang Language to convert
     * @return String representation
     */
    static std::string languageToString(Language lang);
};

#endif // SYSTEM_SETTINGS_H
