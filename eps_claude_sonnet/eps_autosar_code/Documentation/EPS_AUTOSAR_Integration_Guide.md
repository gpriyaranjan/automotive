# AUTOSAR EPS System Integration Guide

## Table of Contents
1. [Introduction](#introduction)
2. [System Architecture](#system-architecture)
3. [AUTOSAR Components](#autosar-components)
4. [Build Instructions](#build-instructions)
5. [Configuration](#configuration)
6. [Integration Steps](#integration-steps)
7. [Testing and Validation](#testing-and-validation)
8. [Safety Considerations](#safety-considerations)
9. [Troubleshooting](#troubleshooting)
10. [References](#references)

## 1. Introduction

### 1.1 Purpose
This document provides comprehensive guidance for integrating the AUTOSAR-compliant Electronic Power Steering (EPS) system into automotive ECUs. The system is designed according to AUTOSAR R4.4 specification and implements ISO 26262 functional safety requirements up to ASIL D.

### 1.2 Scope
The EPS AUTOSAR system includes:
- Application Software Components (SWCs)
- Runtime Environment (RTE) interfaces
- Basic Software (BSW) modules
- Configuration files (ARXML)
- Build system and toolchain support

### 1.3 Target Platform
- **Primary Target**: ARM Cortex-M4 based ECUs
- **AUTOSAR Version**: R4.4
- **Safety Level**: ASIL D (decomposed)
- **Compiler**: GCC ARM Embedded

## 2. System Architecture

### 2.1 AUTOSAR Layered Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Application Layer                        │
├─────────────────────────────────────────────────────────────┤
│  EPS_SWC  │ EPS_Safety_SWC │ EPS_Diagnostics_SWC           │
├─────────────────────────────────────────────────────────────┤
│                Runtime Environment (RTE)                    │
├─────────────────────────────────────────────────────────────┤
│                   Basic Software (BSW)                      │
├─────────────────────────────────────────────────────────────┤
│    OS    │   COM   │   DEM   │   DCM   │  IoHwAb  │  MCAL  │
├─────────────────────────────────────────────────────────────┤
│                      Hardware                               │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 EPS System Components

#### 2.2.1 Main EPS Software Component (EPS_SWC)
- **Purpose**: Core steering assistance logic
- **ASIL Level**: ASIL D (decomposed to ASIL B(D) + ASIL B(D))
- **Cycle Time**: 1ms main task, 10ms safety monitor
- **Key Functions**:
  - Steering assistance calculation
  - Speed-sensitive control
  - Return-to-center functionality
  - Damping control

#### 2.2.2 Safety Software Component (EPS_Safety_SWC)
- **Purpose**: Safety monitoring and fault management
- **ASIL Level**: ASIL D
- **Key Functions**:
  - Dual-channel monitoring
  - Plausibility checks
  - Fault detection and reaction
  - Safe state management

#### 2.2.3 Diagnostics Software Component (EPS_Diagnostics_SWC)
- **Purpose**: Diagnostic functions and DTC management
- **ASIL Level**: QM
- **Key Functions**:
  - DTC storage and retrieval
  - Diagnostic services
  - Performance monitoring

## 3. AUTOSAR Components

### 3.1 Software Component Types

#### 3.1.1 EPS_SWC_Type
```xml
<APPLICATION-SW-COMPONENT-TYPE>
  <SHORT-NAME>EPS_SWC_Type</SHORT-NAME>
  <CATEGORY>APPLICATION_LEVEL</CATEGORY>
  <PORTS>
    <!-- Sensor Data Input -->
    <R-PORT-PROTOTYPE>
      <SHORT-NAME>SensorData</SHORT-NAME>
      <REQUIRED-INTERFACE-TREF>EPS_SensorData_IF</REQUIRED-INTERFACE-TREF>
    </R-PORT-PROTOTYPE>
    
    <!-- Motor Command Output -->
    <P-PORT-PROTOTYPE>
      <SHORT-NAME>MotorCommand</SHORT-NAME>
      <PROVIDED-INTERFACE-TREF>EPS_MotorCommand_IF</PROVIDED-INTERFACE-TREF>
    </P-PORT-PROTOTYPE>
    
    <!-- Additional ports... -->
  </PORTS>
</APPLICATION-SW-COMPONENT-TYPE>
```

### 3.2 Interface Definitions

#### 3.2.1 Sender-Receiver Interfaces
- **EPS_SensorData_IF**: Sensor data communication
- **EPS_MotorCommand_IF**: Motor control commands
- **EPS_SystemState_IF**: System status information
- **EPS_PerformanceData_IF**: Performance metrics

#### 3.2.2 Client-Server Interfaces
- **PowerManagement_IF**: Power management services
- **SafetyManager_IF**: Safety monitoring services
- **DiagnosticManager_IF**: Diagnostic services

### 3.3 Runnable Entities

#### 3.3.1 EPS_MainTask_Runnable
- **Trigger**: Timing Event (1ms)
- **WCET**: 0.8ms
- **Purpose**: Main control loop execution

#### 3.3.2 EPS_SafetyMonitor_Runnable
- **Trigger**: Timing Event (10ms)
- **WCET**: 2ms
- **Purpose**: Safety mechanism monitoring

#### 3.3.3 EPS_DiagnosticTask_Runnable
- **Trigger**: Timing Event (100ms)
- **WCET**: 5ms
- **Purpose**: Diagnostic data processing

## 4. Build Instructions

### 4.1 Prerequisites
```bash
# Install ARM GCC toolchain
sudo apt-get install gcc-arm-none-eabi

# Install build tools
sudo apt-get install make cmake

# Install debugging tools
sudo apt-get install openocd gdb-multiarch
```

### 4.2 Build Process
```bash
# Navigate to build directory
cd eps_autosar_code/Build

# Clean previous build
make clean

# Build debug version
make debug-build

# Build release version
make release-build

# Build safety-compliant version
make safety-build
```

### 4.3 Build Targets
- `all`: Build complete project
- `clean`: Remove build artifacts
- `flash`: Flash firmware to target
- `debug`: Start debug session
- `test`: Run unit tests
- `autosar-check`: AUTOSAR compliance verification
- `misra-check`: MISRA-C compliance verification

## 5. Configuration

### 5.1 AUTOSAR Configuration (ARXML)

The system configuration is defined in `Config/EPS_System.arxml`:

```xml
<!-- Example configuration snippet -->
<TIMING-EVENT>
  <SHORT-NAME>EPS_MainTask_TimingEvent</SHORT-NAME>
  <START-ON-EVENT-REF>EPS_MainTask_Runnable</START-ON-EVENT-REF>
  <PERIOD>0.001</PERIOD>
</TIMING-EVENT>
```

### 5.2 Calibration Parameters

Key calibration parameters in `EPS_SWC.h`:

```c
#define EPS_MAX_ASSISTANCE_TORQUE_NM    (8.0F)    /* Maximum assistance */
#define EPS_BASE_ASSISTANCE_GAIN        (1.5F)    /* Base gain factor */
#define EPS_LOW_SPEED_THRESHOLD_KMH     (10.0F)   /* Low speed threshold */
#define EPS_HIGH_SPEED_THRESHOLD_KMH    (100.0F)  /* High speed threshold */
```

### 5.3 Safety Configuration

Safety-critical parameters:
```c
#define EPS_WATCHDOG_TIMEOUT_MS         (100U)    /* Watchdog timeout */
#define EPS_MAX_RESPONSE_TIME_MS        (50U)     /* Response time limit */
#define EPS_OSCILLATION_BUFFER_SIZE     (10U)     /* Oscillation detection */
```

## 6. Integration Steps

### 6.1 Step 1: Hardware Setup
1. Connect torque sensor to ADC channels
2. Configure motor control PWM outputs
3. Setup CAN communication interface
4. Connect safety monitoring circuits

### 6.2 Step 2: BSW Configuration
1. Configure OS tasks and priorities
2. Setup CAN communication parameters
3. Configure diagnostic event manager (DEM)
4. Setup I/O hardware abstraction

### 6.3 Step 3: RTE Generation
1. Import ARXML configuration
2. Generate RTE code using AUTOSAR tools
3. Verify interface consistency
4. Compile RTE components

### 6.4 Step 4: Application Integration
1. Integrate EPS software components
2. Configure inter-runnable variables
3. Setup calibration parameters
4. Verify timing constraints

### 6.5 Step 5: Testing and Validation
1. Unit testing of individual components
2. Integration testing of complete system
3. Hardware-in-the-loop (HIL) testing
4. Safety validation testing

## 7. Testing and Validation

### 7.1 Unit Testing
```bash
# Run unit tests
cd eps_autosar_code/Test
make run

# Generate coverage report
make coverage
```

### 7.2 Integration Testing
- **CAN Communication**: Verify message transmission/reception
- **Sensor Interface**: Test ADC readings and validation
- **Motor Control**: Verify PWM output generation
- **Safety Mechanisms**: Test fault detection and reaction

### 7.3 HIL Testing
- **Torque Input Simulation**: Test various torque scenarios
- **Speed Variation**: Verify speed-sensitive assistance
- **Fault Injection**: Test safety mechanism responses
- **Performance Validation**: Measure response times

### 7.4 Safety Validation
- **FMEA Verification**: Confirm fault mode coverage
- **FTA Validation**: Verify fault tree analysis
- **Safety Case**: Document safety argument
- **ASIL Compliance**: Confirm safety integrity level

## 8. Safety Considerations

### 8.1 ASIL D Requirements
- **Dual-channel Architecture**: Redundant processing paths
- **Diverse Monitoring**: Independent safety mechanisms
- **Fault Detection**: <100ms detection time
- **Safe State**: Manual steering always available

### 8.2 Safety Mechanisms
1. **Watchdog Monitoring**: 100ms timeout
2. **Plausibility Checks**: Sensor data validation
3. **Range Monitoring**: Parameter limit checking
4. **Cross-channel Comparison**: Redundant data verification

### 8.3 Fault Handling
```c
// Example fault handling
if (fault_detected) {
    // Transition to safe state
    EPS_SystemState.OperatingMode = EPS_MODE_FAIL_SAFE;
    EPS_SystemState.AssistanceEnabled = FALSE;
    
    // Ensure manual steering
    eps_motor_control_disconnect();
    
    // Set diagnostic trouble code
    Dem_SetEventStatus(DEM_EVENT_EPS_SAFETY_FAULT, DEM_EVENT_STATUS_FAILED);
}
```

## 9. Troubleshooting

### 9.1 Common Issues

#### 9.1.1 Build Errors
**Problem**: Compilation errors due to missing includes
**Solution**: Verify include paths in Makefile

**Problem**: Linker errors for undefined symbols
**Solution**: Check BSW module implementations

#### 9.1.2 Runtime Issues
**Problem**: System not responding to torque input
**Solution**: 
1. Check sensor calibration
2. Verify ADC configuration
3. Validate assistance calculation

**Problem**: Excessive assistance or oscillation
**Solution**:
1. Adjust control gains
2. Check safety limits
3. Verify sensor data quality

#### 9.1.3 Safety Issues
**Problem**: Watchdog timeout
**Solution**:
1. Check task execution times
2. Verify watchdog reset calls
3. Optimize critical code paths

**Problem**: False fault detection
**Solution**:
1. Adjust plausibility thresholds
2. Review sensor noise filtering
3. Validate fault detection logic

### 9.2 Debug Tools
```bash
# Start debug session
make debug

# Memory usage analysis
make size

# Static analysis
make lint

# Performance profiling
make profile
```

### 9.3 Diagnostic Codes

| DTC Code | Description | Action |
|----------|-------------|---------|
| 0x1001 | Torque Sensor Fault | Check sensor wiring |
| 0x1002 | Angle Sensor Fault | Verify sensor calibration |
| 0x2001 | Motor Fault | Check motor connections |
| 0x5001 | Excessive Assistance | Adjust control parameters |
| 0x5003 | Oscillation Detected | Review damping settings |

## 10. References

### 10.1 AUTOSAR Standards
- AUTOSAR R4.4 Specification
- AUTOSAR Methodology
- AUTOSAR Software Component Template

### 10.2 Safety Standards
- ISO 26262: Functional Safety for Road Vehicles
- IEC 61508: Functional Safety of Electrical Systems
- MISRA-C:2012: Guidelines for C Language

### 10.3 EPS Requirements
- EPS Functional Requirements (EPS-FR-001)
- EPS Safety Requirements (EPS-SR-001)
- EPS Performance Requirements (EPS-PR-001)

### 10.4 Tools and Utilities
- **AUTOSAR Builder**: Configuration tool
- **Vector CANoe**: Testing and simulation
- **LDRA Testbed**: Static analysis
- **Polyspace**: Code verification

---

**Document Version**: 1.0  
**Last Updated**: 2025-07-29  
**Author**: AUTOSAR EPS Development Team  
**Classification**: Internal Use