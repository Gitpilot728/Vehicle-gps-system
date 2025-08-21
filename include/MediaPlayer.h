/**
 * @file MediaPlayer.h
 * @brief Media playback system for infotainment
 * @author AI-Enhanced Development System
 */

#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "NotificationManager.h"

/**
 * @brief Enumeration for media player states
 */
enum class PlayerState {
    STOPPED,    ///< Player is stopped
    PLAYING,    ///< Currently playing media
    PAUSED      ///< Player is paused
};

/**
 * @brief Structure representing a media track
 */
struct Track {
    std::string title;      ///< Track title
    std::string artist;     ///< Artist name
    std::string album;      ///< Album name
    int duration;           ///< Duration in seconds
    
    /**
     * @brief Constructor for Track
     * @param t Title
     * @param ar Artist
     * @param al Album
     * @param dur Duration in seconds
     */
    Track(const std::string& t, const std::string& ar, const std::string& al, int dur);
};

/**
 * @brief Media player for infotainment system
 * 
 * Provides music playback functionality including play, pause, skip, and playlist management.
 */
class MediaPlayer {
private:
    std::vector<Track> playlist;                            ///< Current playlist
    int currentTrackIndex;                                  ///< Index of current track
    PlayerState state;                                      ///< Current player state
    int volume;                                             ///< Volume level (0-100)
    int currentPosition;                                    ///< Current position in track (seconds)
    std::shared_ptr<NotificationManager> notificationManager;   ///< Notification system
    
public:
    /**
     * @brief Constructor with notification manager
     * @param notifManager Shared pointer to notification manager
     */
    explicit MediaPlayer(std::shared_ptr<NotificationManager> notifManager);
    
    /**
     * @brief Add a track to the playlist
     * @param track Track to add
     */
    void addTrack(const Track& track);
    
    /**
     * @brief Start playing current track
     */
    void play();
    
    /**
     * @brief Pause playback
     */
    void pause();
    
    /**
     * @brief Stop playback
     */
    void stop();
    
    /**
     * @brief Skip to next track
     */
    void nextTrack();
    
    /**
     * @brief Go to previous track
     */
    void previousTrack();
    
    /**
     * @brief Set volume level
     * @param vol Volume level (0-100)
     */
    void setVolume(int vol);
    
    /**
     * @brief Get current volume level
     * @return Volume level (0-100)
     */
    int getVolume() const;
    
    /**
     * @brief Get current player state
     * @return Current state
     */
    PlayerState getState() const;
    
    /**
     * @brief Display current track information
     */
    void displayCurrentTrack() const;
    
    /**
     * @brief Display entire playlist
     */
    void displayPlaylist() const;
    
    /**
     * @brief Get current track if available
     * @return Pointer to current track, nullptr if no track
     */
    const Track* getCurrentTrack() const;
    
    /**
     * @brief Load default demo playlist
     */
    void loadDemoPlaylist();
};

#endif // MEDIA_PLAYER_H
