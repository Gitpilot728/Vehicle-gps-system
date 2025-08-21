@echo off
REM Test runner script for Vehicle GPS Monitoring System
REM Runs all test suites and reports results

echo Running Vehicle GPS Monitoring System Tests...
echo =============================================
echo.

set TESTS_PASSED=0
set TESTS_FAILED=0

REM Run Integration Tests
echo [1/3] Running Integration Tests...
echo ---------------------------------------------
bin\test_integration.exe
if errorlevel 1 (
    echo ❌ Integration tests FAILED
    set /a TESTS_FAILED+=1
) else (
    echo ✅ Integration tests PASSED
    set /a TESTS_PASSED+=1
)
echo.

REM Run Vehicle Monitor Tests
echo [2/3] Running Vehicle Monitor Tests...
echo ---------------------------------------------
bin\test_vehicle_monitor.exe
if errorlevel 1 (
    echo ❌ Vehicle Monitor tests FAILED
    set /a TESTS_FAILED+=1
) else (
    echo ✅ Vehicle Monitor tests PASSED
    set /a TESTS_PASSED+=1
)
echo.

REM Run GPS Navigator Tests
echo [3/3] Running GPS Navigator Tests...
echo ---------------------------------------------
bin\test_gps_navigator.exe
if errorlevel 1 (
    echo ❌ GPS Navigator tests FAILED
    set /a TESTS_FAILED+=1
) else (
    echo ✅ GPS Navigator tests PASSED
    set /a TESTS_PASSED+=1
)
echo.

REM Summary
echo =============================================
echo TEST SUMMARY
echo =============================================
echo Tests Passed: %TESTS_PASSED%
echo Tests Failed: %TESTS_FAILED%
echo.

if %TESTS_FAILED% equ 0 (
    echo 🎉 All tests passed successfully!
    echo The Vehicle GPS Monitoring System is ready for use.
) else (
    echo ⚠️  Some tests failed. Please check the output above.
    echo Review the failed tests and fix any issues before deployment.
)

echo.
echo Press any key to exit...
pause >nul