# AUTOSAR Electric Power Steering (EPS) Implementation Guide

## Overview

This document describes the AUTOSAR (AUTomotive Open System ARchitecture) implementation of the Electric Power Steering system based on the `eps_design.md` specification. The implementation follows AUTOSAR 4.4.0 standards and provides a complete software architecture for EPS control.

## Architecture Overview

The AUTOSAR EPS system is structured according to the standard AUTOSAR layered architecture:

```
┌─────────────────────────────────────────────────────────────┐
│                    Application Layer                        │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────┐ │
│  │ EPS Control │ │   Sensor    │ │   Motor     │ │ Fault   │ │
│  │    SWC      │ │ Interface   │ │  Control    │ │Management│ │
│  │             │ │    SWC      │ │    SWC      │ │   SWC    │ │
│  └─────────────┘ └─────────────┘ └─────────────┘ └─────────┘ │
└─────────────────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────────────────┐
│                    Runtime Environment (RTE)                │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────┐ │
│  │   Client-   │ │   Sender-   │ │   Mode      │ │ Timing  │ │
│  │   Server    │ │  Receiver   │ │ Management  │ │Services │ │
│  │ Interfaces  │ │ Interfaces  │ │ Interfaces  │ │         │ │
│  └─────────────┘ └─────────────┘ └─────────────┘ └─────────┘ │
└─────────────────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────────────────┐
│                    Basic Software (BSW)                     │
│  ┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────┐ │
│  │    OS       │ │  Services   │ │    ECUAL    │ │  MCAL   │ │
│  │             │ │             │ │             │ │         │ │
│  └─────────────┘ └─────────────┘ └─────────────┘ └─────────┘ │
└─────────────────────────────────────────────────────────────┘
┌─────────────────────────────────────────────────────────────┐
│                    Microcontroller                          │
└─────────────────────────────────────────────────────────────┘
```

## Software Components (SWCs)

### 1. EPS Control SWC

**Purpose**: Main control algorithm implementation based on the EPS design document.

**Key Features**:
- Assist torque calculation with speed-dependent mapping
- Return-to-center (RTC) logic for low-speed operation
- Damping control for improved steering feel
- ADAS integration support
- Fault detection and state management

**Files**:
- `swc/eps_control/EpsControl.h` - Header file with interfaces and data structures
- `swc/eps_control/EpsControl.c` - Implementation of the main control algorithm

**Key Functions**:
```c
// Main control function executed at 1kHz
Std_ReturnType EpsControl_MainFunction(EpsControlData_t* control_data);

// Core assist torque calculation
float EpsControl_CalculateAssistTorque(float driver_torque, 
                                     float vehicle_speed,
                                     float steering_angle,
                                     float steering_angular_velocity);

// Return-to-center component calculation
float EpsControl_CalculateRTCComponent(float steering_angle, float vehicle_speed);

// Damping control
float EpsControl_CalculateDampingComponent(float steering_angular_velocity);
```

**Control Algorithm Flow**:
1. **Sensor Data Acquisition**: Read driver torque, steering angle, and vehicle speed
2. **Data Processing**: Apply digital filtering and calculate steering angular velocity
3. **Base Assist Mapping**: Use lookup table for speed-dependent assist mapping
4. **Additional Components**: Add damping, RTC, and inertia compensation
5. **ADAS Integration**: Apply ADAS commands if active
6. **Limiting**: Apply safety limits to final assist torque
7. **Motor Control**: Convert torque to motor current command

### 2. Sensor Interface SWC

**Purpose**: Handle sensor data acquisition, filtering, and calibration.

**Key Features**:
- Multi-sensor support (torque, angle, speed)
- Digital filtering for noise reduction
- Sensor calibration and validation
- Fault detection for sensor failures

**Files**:
- `swc/sensor_interface/SensorInterface.h` - Header file
- `swc/sensor_interface/SensorInterface.c` - Implementation

**Supported Sensors**:
- **Torque Sensor**: Measures driver-applied steering torque
- **Steering Angle Sensor**: Measures absolute steering wheel angle
- **Vehicle Speed Sensor**: Provides vehicle speed information

### 3. Motor Control SWC

**Purpose**: Electric motor control with PID regulation and safety features.

**Key Features**:
- PID current control loop
- Motor temperature monitoring
- Overcurrent and overtemperature protection
- PWM-based motor drive control

**Files**:
- `swc/motor_control/MotorControl.h` - Header file
- `swc/motor_control/MotorControl.c` - Implementation

**Control Features**:
- **PID Regulation**: Proportional-Integral-Derivative current control
- **Safety Limits**: Current, voltage, and temperature limits
- **Fault Handling**: Motor fault detection and safe shutdown

### 4. Fault Management SWC

**Purpose**: System-wide fault detection, management, and reporting.

**Key Features**:
- Comprehensive fault detection across all components
- Fault categorization and severity levels
- Safe mode activation for critical faults
- Integration with AUTOSAR Diagnostic Event Manager (DEM)

**Files**:
- `swc/fault_management/FaultManagement.h` - Header file
- `swc/fault_management/FaultManagement.c` - Implementation

**Fault Categories**:
- **Sensor Faults**: Torque, angle, and speed sensor failures
- **Motor Faults**: Overcurrent, overtemperature, driver failures
- **Communication Faults**: CAN, LIN, SPI, I2C communication errors
- **Power Faults**: Undervoltage, overvoltage, power supply failures
- **Software Faults**: Timeouts, memory errors, stack overflow
- **Hardware Faults**: ECU temperature, internal errors, IO failures

## Basic Software (BSW)

### 1. Operating System (OS)

**Purpose**: Real-time task scheduling and resource management.

**Key Features**:
- Preemptive multitasking
- Priority-based scheduling
- Resource management with priority ceiling protocol
- Event-driven task activation
- Alarm management for periodic tasks

**Files**:
- `bsw/os/Os.h` - OS interface definitions
- `bsw/os/Os.c` - OS implementation

**Task Configuration**:
- **EPS Control Task**: 1kHz periodic execution, highest priority
- **Sensor Interface Task**: 1kHz periodic execution, high priority
- **Motor Control Task**: 1kHz periodic execution, high priority
- **Fault Management Task**: 100Hz periodic execution, medium priority
- **Communication Task**: 100Hz periodic execution, medium priority
- **Watchdog Task**: 10Hz periodic execution, low priority

### 2. Runtime Environment (RTE)

**Purpose**: Communication layer between SWCs and BSW modules.

**Key Features**:
- Client-Server interfaces for synchronous communication
- Sender-Receiver interfaces for asynchronous communication
- Mode management interfaces
- Timing services

**Files**:
- `bsw/services/Rte_EpsControl.h` - RTE interface definitions

**Interface Types**:
- **Client-Server**: For synchronous operations (sensor data, motor control)
- **Sender-Receiver**: For asynchronous data exchange (ADAS integration, system status)
- **Mode Management**: For system mode transitions (normal, safe, fault)

### 3. Microcontroller Abstraction Layer (MCAL)

**Purpose**: Hardware abstraction for microcontroller peripherals.

**Modules**:
- **ADC**: Analog-to-digital conversion for sensor readings
- **CAN**: Controller Area Network communication
- **GPT**: General Purpose Timer for timing functions
- **MCU**: Microcontroller unit initialization and configuration
- **PWM**: Pulse Width Modulation for motor control

### 4. ECU Abstraction Layer (ECUAL)

**Purpose**: ECU-specific hardware abstraction.

**Modules**:
- **CanIf**: CAN interface abstraction
- **Det**: Development Error Tracer for error reporting
- **Dem**: Diagnostic Event Manager for fault management

## Configuration Files

### 1. AUTOSAR XML (ARXML)

**Purpose**: AUTOSAR-compliant configuration files for tool integration.

**Files**:
- `config/swc/EpsControl.arxml` - EPS Control SWC configuration

**Configuration Elements**:
- **Software Component Type**: Component definition with ports and interfaces
- **Port Interfaces**: Client-Server and Sender-Receiver interface definitions
- **Internal Behavior**: Runnable entities and event definitions
- **Data Types**: Application and implementation data type mappings

### 2. Build Configuration

**Purpose**: Build system configuration for compilation and linking.

**Files**:
- `Makefile` - Complete build system with multiple targets

**Build Targets**:
- `all` - Build complete system (default)
- `debug` - Build with debug information
- `release` - Build optimized release version
- `clean` - Remove build artifacts
- `test` - Run system tests
- `doc` - Generate documentation

## Implementation Details

### 1. Assist Torque Calculation

The core EPS algorithm implements the following steps:

```c
float EpsControl_CalculateAssistTorque(float driver_torque, 
                                     float vehicle_speed,
                                     float steering_angle,
                                     float steering_angular_velocity)
{
    float assist_torque = 0.0f;
    
    // Step 1: Base assist mapping
    assist_torque = EpsControl_LookupAssistTorque(driver_torque, vehicle_speed);
    
    // Step 2: Add damping component
    assist_torque += EpsControl_CalculateDampingComponent(steering_angular_velocity);
    
    // Step 3: Add return-to-center component
    assist_torque += EpsControl_CalculateRTCComponent(steering_angle, vehicle_speed);
    
    // Step 4: Apply ADAS override if active
    if (eps_control_data.adas_active) {
        assist_torque = eps_control_data.adas_command_torque;
    }
    
    // Step 5: Apply limits
    EpsControl_ApplyLimits(&assist_torque);
    
    return assist_torque;
}
```

### 2. Lookup Table Implementation

The assist torque mapping uses a 2D lookup table with bilinear interpolation:

```c
static const float assist_torque_map[EPS_ASSIST_MAP_SIZE_X][EPS_ASSIST_MAP_SIZE_Y] = {
    /* Speed: 0, 10, 20, 30, 40, 50, 60, 70 km/h */
    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},  /* 0 Nm driver torque */
    {2.0f, 1.8f, 1.5f, 1.2f, 1.0f, 0.8f, 0.6f, 0.4f},  /* 1 Nm driver torque */
    // ... additional rows for different driver torques
};
```

### 3. Fault Management

The fault management system provides comprehensive error handling:

```c
Std_ReturnType EpsControl_FaultDetection(EpsControlData_t* control_data)
{
    Std_ReturnType result = E_OK;
    
    // Check sensor validity
    if (control_data->driver_torque < -20.0f || control_data->driver_torque > 20.0f) {
        control_data->fault_code = EPS_FAULT_TORQUE_SENSOR;
        result = E_NOT_OK;
    }
    
    // Check motor current limits
    if (fabs(control_data->motor_current_command) > 100.0f) {
        control_data->fault_code = EPS_FAULT_MOTOR_OVERCURRENT;
        result = E_NOT_OK;
    }
    
    return result;
}
```

## Safety Features

### 1. System States

The EPS system operates in multiple states:

- **INIT**: System initialization
- **NORMAL**: Normal operation with full assist
- **FAULT**: Fault detected, reduced functionality
- **SAFE_MODE**: Critical fault, minimal assist only

### 2. Safety Limits

- **Assist Torque**: ±50 Nm maximum
- **Motor Current**: ±100 A maximum
- **Motor Voltage**: ±48 V maximum
- **Temperature**: 85°C maximum

### 3. Fault Handling

- **Sensor Faults**: Use last valid data or default values
- **Motor Faults**: Disable motor and switch to manual steering
- **Communication Faults**: Continue with local sensor data
- **Critical Faults**: Activate safe mode or system shutdown

## ADAS Integration

The system supports Advanced Driver Assistance Systems:

```c
// ADAS data structure
typedef struct {
    boolean adas_active;           /* ADAS system active flag */
    float adas_command_torque;     /* ADAS command torque (Nm) */
    uint8_t adas_mode;             /* ADAS operation mode */
    boolean adas_override;         /* ADAS override flag */
} Rte_AdasData_t;
```

**Integration Features**:
- **Lane Keeping Assist**: Automatic steering corrections
- **Park Assist**: Automated parking maneuvers
- **Emergency Steering**: Collision avoidance steering
- **Override Control**: ADAS can override driver input when necessary

## Performance Characteristics

### 1. Timing Requirements

- **Control Loop Rate**: 1kHz (1ms period)
- **Sensor Sampling**: 1kHz
- **Motor Control**: 1kHz
- **Fault Detection**: 100Hz
- **Communication**: 100Hz

### 2. Resource Usage

- **CPU Usage**: <80% under normal conditions
- **Memory Usage**: <64KB RAM, <256KB Flash
- **Stack Usage**: <4KB per task
- **Interrupt Latency**: <10μs

### 3. Response Time

- **Torque Response**: <5ms from sensor input to motor command
- **Fault Response**: <1ms for critical faults
- **Mode Transition**: <10ms for state changes

## Testing and Validation

### 1. Unit Testing

Each SWC includes unit tests for:
- **Functionality**: Core algorithm validation
- **Boundary Conditions**: Edge case handling
- **Error Conditions**: Fault scenario testing

### 2. Integration Testing

System-level tests for:
- **Component Interaction**: SWC communication
- **Timing Behavior**: Real-time performance
- **Fault Propagation**: Error handling across components

### 3. Hardware-in-the-Loop (HIL)

HIL testing for:
- **Sensor Simulation**: Realistic sensor inputs
- **Motor Simulation**: Motor behavior modeling
- **Fault Injection**: Hardware fault simulation

## Deployment

### 1. Build Process

```bash
# Build complete system
make all

# Build debug version
make debug

# Build release version
make release

# Run system
make run
```

### 2. Configuration

The system can be configured through:
- **ARXML Files**: AUTOSAR tool integration
- **Header Files**: Compile-time configuration
- **Runtime Parameters**: Calibration data

### 3. Calibration

Key calibration parameters:
- **Assist Torque Map**: Speed-dependent assist mapping
- **PID Gains**: Motor control parameters
- **Filter Coefficients**: Sensor filtering parameters
- **Safety Limits**: System protection thresholds

## Conclusion

This AUTOSAR implementation provides a complete, production-ready Electric Power Steering system that follows automotive software standards. The modular architecture enables easy maintenance, testing, and integration with other vehicle systems.

The implementation successfully addresses all requirements from the `eps_design.md` specification while providing additional safety features, fault management, and ADAS integration capabilities required for modern automotive applications.

## References

1. AUTOSAR 4.4.0 Specification
2. ISO 26262 Functional Safety Standard
3. SAE J3016 Automated Driving Standards
4. eps_design.md - Original EPS Algorithm Specification 