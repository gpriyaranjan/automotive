# AUTOSAR Electric Power Steering (EPS) System Makefile
# Based on eps_design.md requirements

# Compiler and Tools
CC = gcc
AR = ar
LD = ld
OBJCOPY = objcopy
SIZE = size

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
CFLAGS += -DDEBUG -DTRACE_LEVEL=3
CFLAGS += -I./bsw/services -I./bsw/os -I./bsw/mcal -I./bsw/ecual
CFLAGS += -I./swc/eps_control -I./swc/sensor_interface -I./swc/motor_control -I./swc/fault_management

# Linker Flags
LDFLAGS = -Wl,--gc-sections -Wl,--strip-all

# Directories
SRC_DIR = .
SWC_DIR = swc
BSW_DIR = bsw
CONFIG_DIR = config
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib
BIN_DIR = $(BUILD_DIR)/bin

# Source Files
SWC_SOURCES = \
	$(SWC_DIR)/eps_control/EpsControl.c \
	$(SWC_DIR)/sensor_interface/SensorInterface.c \
	$(SWC_DIR)/motor_control/MotorControl.c \
	$(SWC_DIR)/fault_management/FaultManagement.c

BSW_SOURCES = \
	$(BSW_DIR)/os/Os.c \
	$(BSW_DIR)/services/Rte.c \
	$(BSW_DIR)/mcal/Adc.c \
	$(BSW_DIR)/mcal/Can.c \
	$(BSW_DIR)/mcal/Gpt.c \
	$(BSW_DIR)/mcal/Mcu.c \
	$(BSW_DIR)/mcal/Pwm.c \
	$(BSW_DIR)/ecual/CanIf.c \
	$(BSW_DIR)/ecual/Det.c \
	$(BSW_DIR)/ecual/Dem.c

# Header Files
SWC_HEADERS = \
	$(SWC_DIR)/eps_control/EpsControl.h \
	$(SWC_DIR)/sensor_interface/SensorInterface.h \
	$(SWC_DIR)/motor_control/MotorControl.h \
	$(SWC_DIR)/fault_management/FaultManagement.h

BSW_HEADERS = \
	$(BSW_DIR)/os/Os.h \
	$(BSW_DIR)/services/Rte_EpsControl.h \
	$(BSW_DIR)/mcal/Adc.h \
	$(BSW_DIR)/mcal/Can.h \
	$(BSW_DIR)/mcal/Gpt.h \
	$(BSW_DIR)/mcal/Mcu.h \
	$(BSW_DIR)/mcal/Pwm.h \
	$(BSW_DIR)/ecual/CanIf.h \
	$(BSW_DIR)/ecual/Det.h \
	$(BSW_DIR)/ecual/Dem.h

# Object Files
SWC_OBJECTS = $(SWC_SOURCES:%.c=$(OBJ_DIR)/%.o)
BSW_OBJECTS = $(BSW_SOURCES:%.c=$(OBJ_DIR)/%.o)
ALL_OBJECTS = $(SWC_OBJECTS) $(BSW_OBJECTS)

# Libraries
LIBS = -lm -lpthread

# Target
TARGET = $(BIN_DIR)/eps_system

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)/$(SWC_DIR)/eps_control
	@mkdir -p $(OBJ_DIR)/$(SWC_DIR)/sensor_interface
	@mkdir -p $(OBJ_DIR)/$(SWC_DIR)/motor_control
	@mkdir -p $(OBJ_DIR)/$(SWC_DIR)/fault_management
	@mkdir -p $(OBJ_DIR)/$(BSW_DIR)/os
	@mkdir -p $(OBJ_DIR)/$(BSW_DIR)/services
	@mkdir -p $(OBJ_DIR)/$(BSW_DIR)/mcal
	@mkdir -p $(OBJ_DIR)/$(BSW_DIR)/ecual
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(BIN_DIR)

# Build target executable
$(TARGET): $(ALL_OBJECTS)
	@echo "Linking $@..."
	$(CC) $(ALL_OBJECTS) $(LDFLAGS) $(LIBS) -o $@
	@echo "Build complete: $@"
	@$(SIZE) $@

# Compile Software Components
$(OBJ_DIR)/$(SWC_DIR)/eps_control/%.o: $(SWC_DIR)/eps_control/%.c $(SWC_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(SWC_DIR)/sensor_interface/%.o: $(SWC_DIR)/sensor_interface/%.c $(SWC_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(SWC_DIR)/motor_control/%.o: $(SWC_DIR)/motor_control/%.c $(SWC_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(SWC_DIR)/fault_management/%.o: $(SWC_DIR)/fault_management/%.c $(SWC_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Basic Software
$(OBJ_DIR)/$(BSW_DIR)/os/%.o: $(BSW_DIR)/os/%.c $(BSW_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(BSW_DIR)/services/%.o: $(BSW_DIR)/services/%.c $(BSW_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(BSW_DIR)/mcal/%.o: $(BSW_DIR)/mcal/%.c $(BSW_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(BSW_DIR)/ecual/%.o: $(BSW_DIR)/ecual/%.c $(BSW_HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Build libraries
lib: directories $(SWC_OBJECTS) $(BSW_OBJECTS)
	@echo "Creating libraries..."
	$(AR) rcs $(LIB_DIR)/libeps_swc.a $(SWC_OBJECTS)
	$(AR) rcs $(LIB_DIR)/libeps_bsw.a $(BSW_OBJECTS)
	@echo "Libraries created in $(LIB_DIR)"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR)
	@echo "Clean complete"

# Install target
install: $(TARGET)
	@echo "Installing EPS system..."
	cp $(TARGET) /usr/local/bin/
	@echo "Installation complete"

# Uninstall target
uninstall:
	@echo "Uninstalling EPS system..."
	rm -f /usr/local/bin/eps_system
	@echo "Uninstallation complete"

# Run target
run: $(TARGET)
	@echo "Running EPS system..."
	./$(TARGET)

# Debug target
debug: CFLAGS += -DDEBUG -g -O0
debug: $(TARGET)
	@echo "Debug build complete: $(TARGET)"

# Release target
release: CFLAGS += -DNDEBUG -O3
release: $(TARGET)
	@echo "Release build complete: $(TARGET)"

# Test target
test: $(TARGET)
	@echo "Running tests..."
	# Add test execution here
	@echo "Tests complete"

# Documentation target
doc:
	@echo "Generating documentation..."
	doxygen Doxyfile
	@echo "Documentation generated in doc/html/"

# Static analysis
analyze:
	@echo "Running static analysis..."
	cppcheck --enable=all --std=c99 $(SWC_DIR) $(BSW_DIR)
	@echo "Static analysis complete"

# Code formatting
format:
	@echo "Formatting code..."
	clang-format -i $(SWC_SOURCES) $(BSW_SOURCES) $(SWC_HEADERS) $(BSW_HEADERS)
	@echo "Code formatting complete"

# Dependencies
deps:
	@echo "Checking dependencies..."
	@which $(CC) > /dev/null || (echo "Error: $(CC) not found" && exit 1)
	@which $(AR) > /dev/null || (echo "Error: $(AR) not found" && exit 1)
	@which $(LD) > /dev/null || (echo "Error: $(LD) not found" && exit 1)
	@echo "All dependencies satisfied"

# Help target
help:
	@echo "AUTOSAR EPS System Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all       - Build the complete EPS system (default)"
	@echo "  lib       - Build libraries only"
	@echo "  clean     - Remove all build artifacts"
	@echo "  install   - Install the EPS system"
	@echo "  uninstall - Uninstall the EPS system"
	@echo "  run       - Build and run the EPS system"
	@echo "  debug     - Build with debug information"
	@echo "  release   - Build optimized release version"
	@echo "  test      - Run tests"
	@echo "  doc       - Generate documentation"
	@echo "  analyze   - Run static analysis"
	@echo "  format    - Format source code"
	@echo "  deps      - Check build dependencies"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Build directories:"
	@echo "  Source: $(SRC_DIR)"
	@echo "  Build:  $(BUILD_DIR)"
	@echo "  Output: $(TARGET)"

# Phony targets
.PHONY: all directories lib clean install uninstall run debug release test doc analyze format deps help

# Include dependency files if they exist
-include $(ALL_OBJECTS:.o=.d)

# Generate dependency files
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$ 