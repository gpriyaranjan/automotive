#******************************************************************************
# AUTOSAR EPS System Makefile
# Version: 4.4.0
# Date: 2025-07-29
# 
# This Makefile builds the AUTOSAR Electronic Power Steering (EPS) system
# according to AUTOSAR R4.4 specification.
#
# Target Platform: ARM Cortex-M4
# Compiler: GCC ARM
#******************************************************************************

#******************************************************************************
# Project Configuration
#******************************************************************************
PROJECT_NAME = EPS_AUTOSAR_System
VERSION = 1.0.0
TARGET = eps_autosar_system

# Build Configuration
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
DEP_DIR = $(BUILD_DIR)/dep

# Project Root Directory
PROJECT_ROOT = ..

#******************************************************************************
# Toolchain Configuration
#******************************************************************************
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE = $(CROSS_COMPILE)size
GDB = $(CROSS_COMPILE)gdb

#******************************************************************************
# Compiler and Linker Flags
#******************************************************************************
# CPU Configuration
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard

# Architecture Flags
ARCH_FLAGS = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# C Compiler Flags
CFLAGS = $(ARCH_FLAGS)
CFLAGS += -std=c99
CFLAGS += -Wall -Wextra -Werror
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -fno-strict-aliasing
CFLAGS += -fno-builtin
CFLAGS += -fshort-enums
CFLAGS += -O2
CFLAGS += -g3
CFLAGS += -DUSE_FULL_ASSERT
CFLAGS += -DARM_MATH_CM4
CFLAGS += -D__FPU_PRESENT=1
CFLAGS += -DAUTOSAR_R44

# Assembler Flags
ASFLAGS = $(ARCH_FLAGS)
ASFLAGS += -g3

# Linker Flags
LDFLAGS = $(ARCH_FLAGS)
LDFLAGS += -specs=nano.specs
LDFLAGS += -T$(PROJECT_ROOT)/Build/linker_script.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage
LDFLAGS += -Wl,-Map=$(BIN_DIR)/$(TARGET).map

# Libraries
LIBS = -lc -lm -lnosys

#******************************************************************************
# Include Directories
#******************************************************************************
INCLUDES = -I$(PROJECT_ROOT)/Application/EPS_SWC
INCLUDES += -I$(PROJECT_ROOT)/Application/EPS_Safety_SWC
INCLUDES += -I$(PROJECT_ROOT)/Application/EPS_Diagnostics_SWC
INCLUDES += -I$(PROJECT_ROOT)/RTE
INCLUDES += -I$(PROJECT_ROOT)/BSW/OS
INCLUDES += -I$(PROJECT_ROOT)/BSW/COM
INCLUDES += -I$(PROJECT_ROOT)/BSW/DEM
INCLUDES += -I$(PROJECT_ROOT)/BSW/DCM
INCLUDES += -I$(PROJECT_ROOT)/BSW/IoHwAb
INCLUDES += -I$(PROJECT_ROOT)/BSW/Mcal
INCLUDES += -I$(PROJECT_ROOT)/Config

#******************************************************************************
# Source Files
#******************************************************************************

# Application Layer Sources
APP_SOURCES = $(PROJECT_ROOT)/Application/EPS_SWC/EPS_SWC.c

# RTE Sources
RTE_SOURCES = $(PROJECT_ROOT)/RTE/Rte_EPS_SWC.c

# BSW Sources
BSW_SOURCES = $(PROJECT_ROOT)/BSW/OS/Os.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/DEM/Dem.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/COM/Com.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/DCM/Dcm.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/IoHwAb/IoHwAb.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/Mcal/Adc.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/Mcal/Pwm.c
BSW_SOURCES += $(PROJECT_ROOT)/BSW/Mcal/Can.c

# Startup and System Sources
STARTUP_SOURCES = $(PROJECT_ROOT)/BSW/OS/startup_stm32f4xx.s
SYSTEM_SOURCES = $(PROJECT_ROOT)/BSW/OS/system_stm32f4xx.c

# All Sources
C_SOURCES = $(APP_SOURCES) $(RTE_SOURCES) $(BSW_SOURCES) $(SYSTEM_SOURCES)
ASM_SOURCES = $(STARTUP_SOURCES)

#******************************************************************************
# Object Files
#******************************************************************************
C_OBJECTS = $(C_SOURCES:$(PROJECT_ROOT)/%.c=$(OBJ_DIR)/%.o)
ASM_OBJECTS = $(ASM_SOURCES:$(PROJECT_ROOT)/%.s=$(OBJ_DIR)/%.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Dependency Files
DEPS = $(C_OBJECTS:.o=.d)

#******************************************************************************
# Build Rules
#******************************************************************************

.PHONY: all clean flash debug size info help

# Default target
all: $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex $(BIN_DIR)/$(TARGET).bin
	@echo "Build completed successfully!"
	@$(SIZE) $(BIN_DIR)/$(TARGET).elf

# Create directories
$(BUILD_DIR) $(OBJ_DIR) $(BIN_DIR) $(DEP_DIR):
	@mkdir -p $@

# Compile C source files
$(OBJ_DIR)/%.o: $(PROJECT_ROOT)/%.c | $(OBJ_DIR)
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF $(DEP_DIR)/$(notdir $(@:.o=.d)) -c $< -o $@

# Compile Assembly source files
$(OBJ_DIR)/%.o: $(PROJECT_ROOT)/%.s | $(OBJ_DIR)
	@echo "Assembling: $<"
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -c $< -o $@

# Link ELF file
$(BIN_DIR)/$(TARGET).elf: $(OBJECTS) | $(BIN_DIR)
	@echo "Linking: $@"
	@$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@

# Generate HEX file
$(BIN_DIR)/$(TARGET).hex: $(BIN_DIR)/$(TARGET).elf
	@echo "Generating HEX: $@"
	@$(OBJCOPY) -O ihex $< $@

# Generate BIN file
$(BIN_DIR)/$(TARGET).bin: $(BIN_DIR)/$(TARGET).elf
	@echo "Generating BIN: $@"
	@$(OBJCOPY) -O binary -S $< $@

# Include dependency files
-include $(DEPS)

#******************************************************************************
# Utility Targets
#******************************************************************************

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)

# Flash firmware to target
flash: $(BIN_DIR)/$(TARGET).hex
	@echo "Flashing firmware..."
	@openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg \
		-c "program $(BIN_DIR)/$(TARGET).hex verify reset exit"

# Start debug session
debug: $(BIN_DIR)/$(TARGET).elf
	@echo "Starting debug session..."
	@$(GDB) -ex "target remote localhost:3333" \
		-ex "monitor reset halt" \
		-ex "load" \
		-ex "monitor reset halt" \
		$(BIN_DIR)/$(TARGET).elf

# Show memory usage
size: $(BIN_DIR)/$(TARGET).elf
	@echo "Memory usage:"
	@$(SIZE) -A -t $<

# Show build information
info:
	@echo "Project: $(PROJECT_NAME) v$(VERSION)"
	@echo "Target: $(TARGET)"
	@echo "Compiler: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "Sources: $(words $(C_SOURCES)) C files, $(words $(ASM_SOURCES)) ASM files"

# Generate disassembly
disasm: $(BIN_DIR)/$(TARGET).elf
	@echo "Generating disassembly..."
	@$(OBJDUMP) -d $< > $(BIN_DIR)/$(TARGET).dis

# Static analysis with PC-lint
lint:
	@echo "Running static analysis..."
	@pc-lint -i$(PROJECT_ROOT)/Build/lint std.lnt $(C_SOURCES)

# Generate documentation
docs:
	@echo "Generating documentation..."
	@doxygen $(PROJECT_ROOT)/Documentation/Doxyfile

# Run unit tests
test:
	@echo "Running unit tests..."
	@cd $(PROJECT_ROOT)/Test && make run

# AUTOSAR compliance check
autosar-check:
	@echo "Checking AUTOSAR compliance..."
	@polyspace-bug-finder -sources-list-file $(PROJECT_ROOT)/Build/sources.txt \
		-checkers autosar-c-2012 \
		-results-dir $(BUILD_DIR)/polyspace

# MISRA-C compliance check
misra-check:
	@echo "Checking MISRA-C compliance..."
	@pc-lint -i$(PROJECT_ROOT)/Build/lint misra-c.lnt $(C_SOURCES)

# Code coverage analysis
coverage:
	@echo "Running code coverage analysis..."
	@gcov $(C_SOURCES)
	@lcov --capture --directory $(OBJ_DIR) --output-file $(BUILD_DIR)/coverage.info
	@genhtml $(BUILD_DIR)/coverage.info --output-directory $(BUILD_DIR)/coverage

# Performance profiling
profile: $(BIN_DIR)/$(TARGET).elf
	@echo "Running performance profiling..."
	@gprof $(BIN_DIR)/$(TARGET).elf gmon.out > $(BUILD_DIR)/profile.txt

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build the complete project (default)"
	@echo "  clean        - Remove all build artifacts"
	@echo "  flash        - Flash firmware to target device"
	@echo "  debug        - Start GDB debug session"
	@echo "  size         - Show memory usage"
	@echo "  info         - Show build information"
	@echo "  disasm       - Generate disassembly listing"
	@echo "  lint         - Run static analysis with PC-lint"
	@echo "  docs         - Generate documentation with Doxygen"
	@echo "  test         - Run unit tests"
	@echo "  autosar-check - Check AUTOSAR compliance"
	@echo "  misra-check  - Check MISRA-C compliance"
	@echo "  coverage     - Generate code coverage report"
	@echo "  profile      - Run performance profiling"
	@echo "  help         - Show this help message"

#******************************************************************************
# Build Configuration Variants
#******************************************************************************

# Debug build
debug-build: CFLAGS += -DDEBUG -O0 -g3
debug-build: all

# Release build
release-build: CFLAGS += -DNDEBUG -O2 -g0
release-build: all

# Safety build (ASIL D compliant)
safety-build: CFLAGS += -DSAFETY_BUILD -O2 -g3 -fstack-protector-strong
safety-build: CFLAGS += -Wformat=2 -Wformat-security -Wstack-protector
safety-build: all

# Test build
test-build: CFLAGS += -DTEST_BUILD -O0 -g3 --coverage
test-build: LDFLAGS += --coverage
test-build: all

#******************************************************************************
# Platform-Specific Configurations
#******************************************************************************

# STM32F407 Configuration
stm32f407: CFLAGS += -DSTM32F407xx -DHSE_VALUE=8000000
stm32f407: LDFLAGS += -T$(PROJECT_ROOT)/Build/STM32F407VGTx_FLASH.ld
stm32f407: all

# STM32F429 Configuration
stm32f429: CFLAGS += -DSTM32F429xx -DHSE_VALUE=8000000
stm32f429: LDFLAGS += -T$(PROJECT_ROOT)/Build/STM32F429ZITx_FLASH.ld
stm32f429: all

#******************************************************************************
# End of Makefile
#******************************************************************************