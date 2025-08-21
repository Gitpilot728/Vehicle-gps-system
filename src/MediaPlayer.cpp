/**
 * @file MediaPlayer.cpp
 * @brief Implementation of the MediaPlayer class
 */

#include "MediaPlayer.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

Track::Track(const std::string& t, const std::string& ar, const std::string& al, int dur)
    : title(t), artist(ar), album(al), duration(dur) {}
MediaPlayer::MediaPlayer(std::shared_ptr<NotificationManager> notifManager)
    : currentTrackIndex(0), state(PlayerState::STOPPED), volume(50), 
      currentPosition(0), notificationManager(notifManager) {}
void MediaPlayer::addTrack(const Track& track) {
    playlist.push_back(track);
    notificationManager->addNotification("Track added: " + track.title, AlertLevel::INFO);
}
void MediaPlayer::play() {
    if (playlist.empty()) {
        notificationManager->addNotification("No tracks in playlist", AlertLevel::WARNING);
        return;
    }
    if (currentTrackIndex >= playlist.size()) {
        currentTrackIndex = 0;
    }
    state = PlayerState::PLAYING;
    notificationManager->addNotification("Now playing: " + playlist[currentTrackIndex].title, AlertLevel::INFO);
    std::cout << "▶️  Playing..." << std::endl;
}

void MediaPlayer::pause() {
    if (state == PlayerState::PLAYING) {
        state = PlayerState::PAUSED;
        std::cout << "⏸️  Paused" << std::endl;
    } else if (state == PlayerState::PAUSED) {
        state = PlayerState::PLAYING;
        std::cout << "▶️  Resumed" << std::endl;
    }
}

void MediaPlayer::stop() {
    state = PlayerState::STOPPED;
    currentPosition = 0;
    std::cout << "⏹️  Stopped" << std::endl;
}

void MediaPlayer::nextTrack() {
    if (playlist.empty()) return;
    
    currentTrackIndex = (currentTrackIndex + 1) % playlist.size();
    currentPosition = 0;
    
    if (state == PlayerState::PLAYING && notificationManager) {
        notificationManager->addNotification("Skipped to: " + playlist[currentTrackIndex].title, AlertLevel::INFO);
    }
    std::cout << "⏭️  Next track" << std::endl;
}

void MediaPlayer::previousTrack() {
    if (playlist.empty()) return;    
    currentTrackIndex = (currentTrackIndex - 1 + playlist.size()) % playlist.size();
    currentPosition = 0;    
    if (state == PlayerState::PLAYING && notificationManager) {
        notificationManager->addNotification("Previous track: " + playlist[currentTrackIndex].title, AlertLevel::INFO);
    }
    std::cout << "⏮️  Previous track" << std::endl;
}

void MediaPlayer::setVolume(int vol) {
    if (vol < 0) vol = 0;
    if (vol > 100) vol = 100;
    volume = vol;
    std::cout << "🔊 Volume set to " << volume << "%" << std::endl;
    if (state == PlayerState::PLAYING) {
        std::cout << "🔊 Adjusting volume while playing..." << std::endl;
    }
    notificationManager->addNotification("Volume set to " + std::to_string(volume) + "%", AlertLevel::INFO);
}
int MediaPlayer::getVolume() const {
    return volume;
}
PlayerState MediaPlayer::getState() const {
    return state;
}
void MediaPlayer::displayCurrentTrack() const {
    if (playlist.empty()) {
        std::cout << "🎵 No tracks available" << std::endl;
        return;
    }
    if (currentTrackIndex >= playlist.size()) {
        std::cout << "🎵 Invalid track index" << std::endl;
        return;
    }
    const Track& track = playlist[currentTrackIndex];
    std::cout << "\n         NOW PLAYING        " << std::endl;
    std::cout << "Title: " << track.title << std::endl;
    std::cout << "Artist: " << track.artist << std::endl;
    std::cout << "Album: " << track.album << std::endl;
    std::cout << "Duration: " << track.duration / 60 << ":" 
              << std::setfill('0') << std::setw(2) << track.duration % 60 << std::endl;
    
    std::string stateStr;
    switch (state) {
        case PlayerState::PLAYING: stateStr = "▶️  PLAYING"; break;
        case PlayerState::PAUSED: stateStr = "⏸️  PAUSED"; break;
        case PlayerState::STOPPED: stateStr = "⏹️  STOPPED"; break;
        default: stateStr = "❓ UNKNOWN"; break;
    }
    std::cout << "Status: " << stateStr << std::endl;
    std::cout << "Volume: " << volume << "%" << std::endl;
    std::cout << "Track: " << (currentTrackIndex + 1) << "/" << playlist.size() << std::endl;
}

void MediaPlayer::displayPlaylist() const {
    if (playlist.empty()) {
        std::cout << "📝 Playlist is empty" << std::endl;
        return;
    }
    
    std::cout << "\n📝 === PLAYLIST ===" << std::endl;
    for (size_t i = 0; i < playlist.size(); ++i) {
        std::string indicator = (i == currentTrackIndex) ? "► " : "  ";
        std::cout << indicator << (i + 1) << ". " << playlist[i].title 
                  << " - " << playlist[i].artist << std::endl;
    }
}

const Track* MediaPlayer::getCurrentTrack() const {
    if (playlist.empty() || currentTrackIndex >= playlist.size()) return nullptr;
    return &playlist[currentTrackIndex];
}

void MediaPlayer::loadDemoPlaylist() {
    playlist.clear();
    
    addTrack(Track("Bohemian Rhapsody", "Queen", "A Night at the Opera", 355));
    addTrack(Track("Hotel California", "Eagles", "Hotel California", 391));
    addTrack(Track("Stairway to Heaven", "Led Zeppelin", "Led Zeppelin IV", 482));
    addTrack(Track("Sweet Child O' Mine", "Guns N' Roses", "Appetite for Destruction", 356));
    addTrack(Track("Imagine", "John Lennon", "Imagine", 183));
    addTrack(Track("Billie Jean", "Michael Jackson", "Thriller", 294));
    addTrack(Track("Smells Like Teen Spirit", "Nirvana", "Nevermind", 301));
    addTrack(Track("Shape of You", "Ed Sheeran", "÷ (Divide)", 263));
    addTrack(Track("Rolling in the Deep", "Adele", "21", 228));
    addTrack(Track("Uptown Funk", "Mark Ronson ft. Bruno Mars", "Uptown Special", 269));
    addTrack(Track("Despacito", "Luis Fonsi ft. Daddy Yankee", "Vida", 229));
    addTrack(Track("Thinking Out Loud", "Ed Sheeran", "x (Multiply)", 281));
    addTrack(Track("Shake It Off", "Taylor Swift", "1989", 219));
    addTrack(Track("Lose Yourself", "Eminem", "8 Mile", 326));
    
    currentTrackIndex = 0;
    std::cout << "🎵 Demo playlist loaded with " << playlist.size() << " tracks" << std::endl;
}
