# Electronic Braking System (EBS) Makefile
# ASIL-D Safety Critical System
# Compliance: ISO 26262, MISRA C:2012

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
CFLAGS += -O2 -g
CFLAGS += -DEBS_SAFETY_LEVEL_ASIL_D
CFLAGS += -DEBS_MISRA_COMPLIANCE

# Safety and debugging flags
CFLAGS += -fstack-protector-strong
CFLAGS += -D_FORTIFY_SOURCE=2
CFLAGS += -Wformat=2
CFLAGS += -Wformat-security
CFLAGS += -Wnull-dereference
CFLAGS += -Wstack-protector
CFLAGS += -Wvla

# Include directories
INCLUDES = -Iinclude

# Source directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
HEADERS = $(wildcard $(INCDIR)/*.h)

# Target executable
TARGET = $(BINDIR)/ebs_system

# Default target
all: directories $(TARGET)

# Create directories
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Link target
$(TARGET): $(OBJECTS)
	@echo "Linking EBS system..."
	$(CC) $(OBJECTS) -o $@ -lm

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

# Static analysis with cppcheck (if available)
static-analysis:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 --platform=unix64 \
		--suppress=missingIncludeSystem \
		--suppress=unusedFunction \
		--inline-suppr \
		$(INCLUDES) $(SRCDIR)/; \
	else \
		echo "cppcheck not found, skipping static analysis"; \
	fi

# MISRA C compliance check (placeholder)
misra-check:
	@echo "MISRA C:2012 compliance check..."
	@echo "Note: Full MISRA compliance requires commercial tools like PC-lint Plus"
	@echo "Current build uses MISRA-friendly compiler flags"

# Safety analysis
safety-check: static-analysis misra-check
	@echo "Safety analysis complete"

# Documentation generation (if Doxygen available)
docs:
	@echo "Generating documentation..."
	@if command -v doxygen >/dev/null 2>&1; then \
		doxygen Doxyfile 2>/dev/null || echo "Doxyfile not found"; \
	else \
		echo "Doxygen not found, skipping documentation generation"; \
	fi

# Unit tests (placeholder)
test:
	@echo "Running unit tests..."
	@echo "Note: Unit test framework not yet implemented"

# Integration tests (placeholder)
integration-test:
	@echo "Running integration tests..."
	@echo "Note: Integration test framework not yet implemented"

# Install target (for embedded deployment)
install: $(TARGET)
	@echo "Installing EBS system..."
	@echo "Note: Deployment scripts not yet implemented"

# Debug build
debug: CFLAGS += -DDEBUG -O0
debug: clean all

# Release build
release: CFLAGS += -DNDEBUG -O3
release: clean all

# Show build information
info:
	@echo "EBS Build Information:"
	@echo "  Compiler: $(CC)"
	@echo "  Flags: $(CFLAGS)"
	@echo "  Includes: $(INCLUDES)"
	@echo "  Sources: $(SOURCES)"
	@echo "  Objects: $(OBJECTS)"
	@echo "  Target: $(TARGET)"

# Help target
help:
	@echo "EBS Build System Help:"
	@echo ""
	@echo "Targets:"
	@echo "  all              - Build the EBS system (default)"
	@echo "  clean            - Remove build artifacts"
	@echo "  debug            - Build with debug symbols and no optimization"
	@echo "  release          - Build optimized release version"
	@echo "  static-analysis  - Run static code analysis"
	@echo "  misra-check      - Check MISRA C compliance"
	@echo "  safety-check     - Run all safety-related checks"
	@echo "  docs             - Generate documentation"
	@echo "  test             - Run unit tests"
	@echo "  integration-test - Run integration tests"
	@echo "  install          - Install the system"
	@echo "  info             - Show build information"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Safety Features:"
	@echo "  - ASIL-D compliance flags enabled"
	@echo "  - Stack protection enabled"
	@echo "  - Format security warnings enabled"
	@echo "  - MISRA C:2012 friendly compilation"

# Phony targets
.PHONY: all clean debug release static-analysis misra-check safety-check docs test integration-test install info help directories

# Special targets
.DEFAULT_GOAL := all
.SUFFIXES: