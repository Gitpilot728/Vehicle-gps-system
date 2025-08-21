# Vehicle GPS Monitoring System

A comprehensive C++ vehicle monitoring system with GPS navigation capabilities, featuring real-time vehicle diagnostics, GPS tracking, media playback, and system settings management.

## Features

### Vehicle Monitoring
- **Engine Temperature Monitoring**: Real-time temperature tracking with overheating alerts
- **Fuel Level Management**: Fuel level monitoring with low fuel warnings and range estimation
- **Speed Monitoring**: Current speed tracking with speed limit alerts
- **Brake System Health**: Brake wear monitoring with maintenance alerts
- **Real-time Updates**: Simulated sensor data updates for demonstration

### GPS Navigation
- **Location Tracking**: Precise GPS coordinate tracking with validation
- **Route Planning**: Waypoint management and route calculation
- **Distance Calculations**: Haversine formula for accurate distance measurements
- **Navigation Status**: Real-time navigation status with arrival detection
- **Signal Quality**: GPS signal strength and satellite count monitoring
- **Turn-by-turn Guidance**: Bearing calculations and navigation assistance

### Media Player
- **Playlist Management**: Add and manage music tracks
- **Playback Controls**: Play, pause, stop, next, and previous track functionality
- **Volume Control**: Adjustable volume levels
- **Track Information**: Display current track and playlist details

### System Settings
- **Display Settings**: Theme selection (Light/Dark/Auto) and brightness control
- **Audio Settings**: System volume and notification sound management
- **Localization**: Multi-language support and regional settings
- **User Preferences**: Customizable time format and temperature units

### Notification System
- **Alert Levels**: Info, Warning, and Critical alert classifications
- **Real-time Notifications**: Instant alerts for system events
- **Notification History**: View and manage notification history
- **Integration**: Unified notification system across all components

## Project Structure

\`\`\`
vehicle-gps-system/
├── include/                 # Header files
│   ├── VehicleMonitor.h    # Vehicle diagnostics
│   ├── GPSNavigator.h      # GPS navigation system
│   ├── MediaPlayer.h       # Media playback
│   ├── SystemSettings.h    # System configuration
│   └── NotificationManager.h # Alert system
├── src/                    # Source files
│   ├── VehicleMonitor.cpp
│   ├── GPSNavigator.cpp
│   ├── MediaPlayer.cpp
│   ├── SystemSettings.cpp
│   ├── NotificationManager.cpp
│   └── main.cpp           # Main application
├── tests/                 # Test files
│   ├── test_gps_navigator.cpp
│   ├── test_vehicle_monitor.cpp
│   └── test_integration.cpp
├── Makefile              # Build configuration
└── README.md            # This file
\`\`\`

## Building the Project

### Prerequisites
- C++17 compatible compiler (GCC 7+ or Clang 5+)
- Make build system

### Build Commands

\`\`\`bash
# Build the main application
make all

# Build test executables
make tests

# Build and run all tests
make test

# Run the main application
make run

# Clean build files
make clean

# Show help
make help
\`\`\`

## Usage

### Running the Main Application

\`\`\`bash
make run
\`\`\`

The application provides an interactive menu with the following options:

1. **Vehicle Monitor Status** - View current vehicle diagnostics
2. **GPS Navigator Status** - Check GPS location and navigation status
3. **Media Player Controls** - Control music playback
4. **System Settings** - View and modify system configuration
5. **View All Notifications** - Display notification history
6. **Simulate Real-time Updates** - Generate simulated sensor data
7. **GPS Navigation Demo** - Run a complete navigation demonstration
8. **Run System Check** - Perform comprehensive system diagnostics

### Running Tests

\`\`\`bash
# Run all tests
make test

# Run individual test suites
./bin/test_gps_navigator
./bin/test_vehicle_monitor
./bin/test_integration
\`\`\`

## GPS Navigation Features

### Coordinate System
- Uses decimal degrees for latitude and longitude
- Supports altitude measurements in meters
- Validates coordinate ranges (lat: -90 to 90, lon: -180 to 180)

### Distance Calculations
- Implements Haversine formula for accurate Earth surface distances
- Accounts for Earth's curvature in distance measurements
- Provides distance calculations in kilometers

### Navigation Capabilities
- **Route Planning**: Add multiple waypoints to create complex routes
- **Real-time Tracking**: Continuous location updates with arrival detection
- **Signal Monitoring**: GPS signal quality assessment with satellite count
- **Status Management**: Comprehensive navigation status tracking

### Example GPS Usage

\`\`\`cpp
// Create GPS navigator
auto gps = std::make_shared<GPSNavigator>(notificationManager);

// Set current location (San Francisco)
GPSCoordinate currentLoc(37.7749, -122.4194, 50.0);
gps->updateLocation(currentLoc);

// Set destination (Los Angeles)
GPSCoordinate destination(34.0522, -118.2437, 100.0);
gps->setDestination(destination, "Los Angeles");

// Start navigation
gps->startNavigation();

// Get distance and ETA
double distance = gps->getDistanceToDestination(); // ~559 km
double eta = gps->getEstimatedTimeToArrival();     // Based on current speed
\`\`\`

## Vehicle Monitoring Features

### Engine Management
- Temperature monitoring with configurable thresholds
- Overheating detection and alerts
- Real-time temperature updates

### Fuel System
- Fuel level percentage tracking
- Low fuel warnings at configurable thresholds
- Critical fuel alerts for emergency situations
- Estimated range calculations based on consumption rate

### Safety Systems
- Speed monitoring with limit enforcement
- Brake wear level tracking
- Maintenance alerts for brake system

### Example Vehicle Monitoring

\`\`\`cpp
// Create vehicle monitor
auto monitor = std::make_shared<VehicleMonitor>(notificationManager);

// Set vehicle parameters
monitor->setEngineTemperature(95.0);  // Normal operating temperature
monitor->setFuelLevel(25.0);          // 25% fuel remaining
monitor->setCurrentSpeed(75.0);       // 75 km/h
monitor->setBrakeWearLevel(30.0);     // 30% brake wear remaining

// Perform system check
monitor->performSystemCheck();        // Checks all parameters

// Calculate estimated range
double range = monitor->calculateEstimatedRange(); // Based on fuel and consumption
\`\`\`

## Testing

The project includes comprehensive test suites:

### GPS Navigator Tests
- Coordinate validation
- Distance calculation accuracy
- Navigation state management
- Signal quality handling
- Waypoint management

### Vehicle Monitor Tests
- Parameter boundary validation
- Alert threshold testing
- System check functionality
- Range calculation accuracy

### Integration Tests
- Component interaction testing
- Notification system integration
- Complete system scenarios
- Error handling validation

## Contributing

1. Follow C++17 standards
2. Maintain comprehensive documentation
3. Add unit tests for new features
4. Use consistent coding style
5. Update README for new functionality

## License

This project is developed for educational and demonstration purposes.

## Future Enhancements

- **Real Hardware Integration**: Connect to actual vehicle sensors and GPS modules
- **Database Storage**: Persistent storage for routes, settings, and history
- **Web Interface**: Remote monitoring and control capabilities
- **Advanced Navigation**: Traffic-aware routing and real-time updates
- **Machine Learning**: Predictive maintenance based on usage patterns
- **Mobile App**: Companion mobile application for remote access
