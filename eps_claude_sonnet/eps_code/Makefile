# Electronic Power Steering (EPS) System Makefile
# Version: 1.0
# Date: 2025-07-29

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
INCLUDES = -I.
LIBS = -lm

# Source files
SOURCES = eps_main.c eps_safety.c eps_test_main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = eps_test

# Header files
HEADERS = eps_main.h eps_safety.h eps_motor_control.h eps_sensors.h \
          eps_communication.h eps_diagnostics.h eps_power_management.h

# Default target
all: $(TARGET)

# Build the test executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "EPS System test program built successfully"

# Compile source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Build artifacts cleaned"

# Install (placeholder for production deployment)
install: $(TARGET)
	@echo "Installing EPS System..."
	@echo "Note: This is a demonstration - actual installation requires embedded target"

# Run tests
test: $(TARGET)
	@echo "Running EPS System Tests..."
	./$(TARGET)

# Static analysis (requires cppcheck)
analyze:
	@echo "Running static analysis..."
	cppcheck --enable=all --std=c99 $(SOURCES) $(HEADERS)

# Generate documentation (requires doxygen)
docs:
	@echo "Generating documentation..."
	doxygen Doxyfile

# Help target
help:
	@echo "EPS System Build Targets:"
	@echo "  all      - Build the EPS test program"
	@echo "  clean    - Remove build artifacts"
	@echo "  test     - Run the EPS system tests"
	@echo "  analyze  - Run static code analysis"
	@echo "  docs     - Generate documentation"
	@echo "  install  - Install the system (demo only)"
	@echo "  help     - Show this help message"

.PHONY: all clean install test analyze docs help