# Makefile for Vehicle GPS Monitoring System
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
INCLUDES = -Iinclude
SRCDIR = src
TESTDIR = tests
BINDIR = bin
OBJDIR = obj

# Create directories if they don't exist
$(shell mkdir -p $(BINDIR) $(OBJDIR))

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
MAIN_SRC = $(SRCDIR)/main.cpp
LIB_SOURCES = $(filter-out $(MAIN_SRC), $(SOURCES))
LIB_OBJECTS = $(LIB_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Test files
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_TARGETS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(BINDIR)/%)

# Main target
MAIN_TARGET = $(BINDIR)/vehicle_system

# Default target
all: $(MAIN_TARGET)

# Build main application
$(MAIN_TARGET): $(OBJDIR)/main.o $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build tests
tests: $(TEST_TARGETS)

$(BINDIR)/test_%: $(TESTDIR)/test_%.cpp $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Run main application
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run all tests
test: tests
	@echo "Running all tests..."
	@for test in $(TEST_TARGETS); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo "All tests passed!"

# Clean build files
clean:
	rm -rf $(BINDIR) $(OBJDIR)

# Install (copy to system directory - optional)
install: $(MAIN_TARGET)
	@echo "Installation not implemented. Run 'make run' to execute."

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the main application (default)"
	@echo "  tests    - Build all test executables"
	@echo "  test     - Build and run all tests"
	@echo "  run      - Build and run the main application"
	@echo "  clean    - Remove all build files"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all tests test run clean install help

# Dependencies (simplified - in a real project, use automatic dependency generation)
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp include/VehicleMonitor.h include/GPSNavigator.h include/MediaPlayer.h include/SystemSettings.h include/NotificationManager.h
$(OBJDIR)/VehicleMonitor.o: $(SRCDIR)/VehicleMonitor.cpp include/VehicleMonitor.h include/NotificationManager.h
$(OBJDIR)/GPSNavigator.o: $(SRCDIR)/GPSNavigator.cpp include/GPSNavigator.h include/NotificationManager.h
$(OBJDIR)/MediaPlayer.o: $(SRCDIR)/MediaPlayer.cpp include/MediaPlayer.h include/NotificationManager.h
$(OBJDIR)/SystemSettings.o: $(SRCDIR)/SystemSettings.cpp include/SystemSettings.h include/NotificationManager.h
$(OBJDIR)/NotificationManager.o: $(SRCDIR)/NotificationManager.cpp include/NotificationManager.h