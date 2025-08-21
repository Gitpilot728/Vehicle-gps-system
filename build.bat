@echo off
REM Build script for Vehicle GPS Monitoring System
REM Windows batch file for easy compilation and testing

echo Building Vehicle GPS Monitoring System...
echo ==========================================

REM Create directories
if not exist "bin" mkdir bin
if not exist "obj" mkdir obj

REM Compile source files
echo Compiling NotificationManager...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude -c src/NotificationManager.cpp -o obj/NotificationManager.o
if errorlevel 1 goto error

echo Compiling VehicleMonitor...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude -c src/VehicleMonitor.cpp -o obj/VehicleMonitor.o
if errorlevel 1 goto error

echo Compiling GPSNavigator...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude -c src/GPSNavigator.cpp -o obj/GPSNavigator.o
if errorlevel 1 goto error

echo Compiling MediaPlayer...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude -c src/MediaPlayer.cpp -o obj/MediaPlayer.o
if errorlevel 1 goto error

echo Compiling SystemSettings...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude -c src/SystemSettings.cpp -o obj/SystemSettings.o
if errorlevel 1 goto error

echo Compiling main application...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude -c src/main.cpp -o obj/main.o
if errorlevel 1 goto error

REM Link main application
echo Linking main application...
g++ -std=c++17 -Wall -Wextra -O2 -g obj/main.o obj/NotificationManager.o obj/VehicleMonitor.o obj/GPSNavigator.o obj/MediaPlayer.o obj/SystemSettings.o -o bin/vehicle_system.exe
if errorlevel 1 goto error

REM Compile tests
echo Compiling tests...
g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude tests/test_integration.cpp obj/NotificationManager.o obj/VehicleMonitor.o obj/GPSNavigator.o obj/MediaPlayer.o obj/SystemSettings.o -o bin/test_integration.exe
if errorlevel 1 goto error

g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude tests/test_vehicle_monitor.cpp obj/NotificationManager.o obj/VehicleMonitor.o obj/GPSNavigator.o obj/MediaPlayer.o obj/SystemSettings.o -o bin/test_vehicle_monitor.exe
if errorlevel 1 goto error

g++ -std=c++17 -Wall -Wextra -O2 -g -Iinclude tests/test_gps_navigator.cpp obj/NotificationManager.o obj/VehicleMonitor.o obj/GPSNavigator.o obj/MediaPlayer.o obj/SystemSettings.o -o bin/test_gps_navigator.exe
if errorlevel 1 goto error

echo.
echo ==========================================
echo Build completed successfully!
echo ==========================================
echo.
echo Available executables:
echo   bin\vehicle_system.exe     - Main application
echo   bin\test_integration.exe   - Integration tests
echo   bin\test_vehicle_monitor.exe - Vehicle monitor tests
echo   bin\test_gps_navigator.exe - GPS navigator tests
echo.
echo To run the main application:
echo   bin\vehicle_system.exe
echo.
echo To run all tests:
echo   run_tests.bat
echo.
goto end

:error
echo.
echo ==========================================
echo Build failed! Check the error messages above.
echo ==========================================
pause
exit /b 1

:end
pause