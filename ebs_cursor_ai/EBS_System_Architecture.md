# EBS System Architecture Specification

## Document Information
- **Document Version**: 1.0
- **Date**: 2024
- **Project**: EBS ECU Code Development
- **Author**: System Architecture Team

## Table of Contents
1. [System Overview](#system-overview)
2. [Hardware Architecture](#hardware-architecture)
3. [Software Architecture](#software-architecture)
4. [Communication Architecture](#communication-architecture)
5. [Safety Architecture](#safety-architecture)
6. [Power Architecture](#power-architecture)

## System Overview

### High-Level Architecture
```
┌─────────────────────────────────────────────────────────────┐
│                    EBS System Architecture                   │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐      │
│  │   Sensors   │    │     ECU     │    │  Actuators  │      │
│  │             │    │             │    │             │      │
│  │ • Brake     │◄──►│ • Main      │◄──►│ • Brake     │      │
│  │   Pedal     │    │   Processor │    │   Valves    │      │
│  │ • Wheel     │    │ • Memory    │    │ • Pump      │      │
│  │   Speed     │    │ • I/O       │    │ • Motor     │      │
│  │ • Pressure  │    │ • CAN       │    │ • Solenoids │      │
│  │ • Yaw Rate  │    │   Interface │    │             │      │
│  └─────────────┘    └─────────────┘    └─────────────┘      │
│                                                              │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐      │
│  │   Power     │    │ CAN Bus     │    │ Diagnostic  │      │
│  │ Management  │    │ Network     │    │ Interface   │      │
│  │             │    │             │    │             │      │
│  │ • Main      │    │ • Vehicle   │    │ • OBD-II    │      │
│  │   Supply    │    │   CAN       │    │ • Service   │      │
│  │ • Backup    │    │ • Internal  │    │   Tool      │      │
│  │   Battery   │    │   CAN       │    │ • Remote    │      │
│  └─────────────┘    └─────────────┘    └─────────────┘      │
└─────────────────────────────────────────────────────────────┘
```

## Hardware Architecture

### ECU Hardware Components

#### Main Processor
- **Type**: 32-bit ARM Cortex-R5 dual-core
- **Frequency**: 200 MHz minimum
- **Features**: 
  - Lockstep operation for safety
  - Floating-point unit
  - Memory protection unit
  - Real-time capabilities

#### Memory Architecture
```
┌─────────────────────────────────────────────────────────────┐
│                    Memory Map                               │
├─────────────────────────────────────────────────────────────┤
│ 0x00000000 - 0x000FFFFF │ Flash Memory (1MB)               │
│                         │ • Bootloader                     │
│                         │ • Application Code               │
│                         │ • Calibration Data               │
│                         │ • Fault Codes                    │
├─────────────────────────────────────────────────────────────┤
│ 0x20000000 - 0x2001FFFF │ SRAM (128KB)                     │
│                         │ • Stack                          │
│                         │ • Heap                           │
│                         │ • Variables                      │
│                         │ • Communication Buffers          │
├─────────────────────────────────────────────────────────────┤
│ 0x40000000 - 0x400FFFFF │ Peripheral Registers             │
│                         │ • GPIO                           │
│                         │ • ADC                            │
│                         │ • PWM                            │
│                         │ • CAN                            │
│                         │ • Timer                          │
└─────────────────────────────────────────────────────────────┘
```

#### I/O Interfaces

##### Analog Inputs
- **ADC Resolution**: 12-bit
- **Sampling Rate**: 1kHz minimum
- **Channels**: 16 channels
- **Input Range**: 0-5V, 0-12V, 4-20mA

##### Digital Inputs
- **Type**: 24V tolerant
- **Channels**: 8 channels
- **Debounce**: Configurable 1-100ms

##### PWM Outputs
- **Frequency**: 1kHz - 10kHz
- **Resolution**: 16-bit
- **Channels**: 12 channels
- **Current**: 2A maximum

##### Digital Outputs
- **Type**: High-side drivers
- **Channels**: 8 channels
- **Current**: 5A maximum
- **Protection**: Overcurrent, overtemperature

### Sensor Interfaces

#### Brake Pedal Sensor
- **Type**: Potentiometer or Hall effect
- **Range**: 0-100% pedal travel
- **Accuracy**: ±1% of full scale
- **Interface**: Analog voltage (0-5V)

#### Wheel Speed Sensors
- **Type**: Magnetic reluctance or Hall effect
- **Frequency**: 0-10kHz
- **Interface**: Digital input with frequency measurement
- **Channels**: 6 channels (2-6 axles)

#### Brake Pressure Sensors
- **Type**: Piezoresistive
- **Range**: 0-200 bar
- **Accuracy**: ±2% of full scale
- **Interface**: Analog voltage (0-5V)

#### Yaw Rate Sensor
- **Type**: MEMS gyroscope
- **Range**: ±100°/s
- **Accuracy**: ±2°/s
- **Interface**: SPI or analog

### Actuator Interfaces

#### Brake Valves
- **Type**: Proportional solenoid valves
- **Control**: PWM with current feedback
- **Response Time**: <10ms
- **Channels**: 6 channels (2-6 axles)

#### Pump Motor
- **Type**: Brushless DC motor
- **Power**: 500W maximum
- **Control**: PWM with speed feedback
- **Interface**: 3-phase inverter

## Software Architecture

### Software Layers
```
┌─────────────────────────────────────────────────────────────┐
│                    Software Architecture                    │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────────────────────────────────┐ │
│  │              Application Layer                          │ │
│  │  • Brake Control Algorithms                            │ │
│  │  • ABS/ESC Logic                                       │ │
│  │  • Traction Control                                     │ │
│  │  • Hill Start Assist                                    │ │
│  │  • Emergency Brake Assist                               │ │
│  └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────────────────────────────────┐ │
│  │              Middleware Layer                           │ │
│  │  • Communication Stack (CAN, LIN)                      │ │
│  │  • Diagnostic Services                                  │ │
│  │  • Memory Management                                    │ │
│  │  • Task Scheduler                                       │ │
│  │  • Watchdog Services                                    │ │
│  └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────────────────────────────────┐ │
│  │              Hardware Abstraction Layer                 │ │
│  │  • ADC Driver                                           │ │
│  │  • PWM Driver                                           │ │
│  │  • CAN Driver                                           │ │
│  │  • GPIO Driver                                          │ │
│  │  • Timer Driver                                         │ │
│  └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────────────────────────────────────────────────┐ │
│  │              Hardware Layer                             │ │
│  │  • Microcontroller                                      │ │
│  │  • Peripherals                                          │ │
│  │  • External Components                                  │ │
│  └─────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

### Task Scheduling
```
┌─────────────────────────────────────────────────────────────┐
│                    Task Schedule                            │
├─────────────────────────────────────────────────────────────┤
│ Task Name        │ Priority │ Frequency │ Execution Time   │
├─────────────────────────────────────────────────────────────┤
│ Brake Control    │ High     │ 100Hz     │ 2ms              │
│ ABS/ESC          │ High     │ 100Hz     │ 3ms              │
│ Sensor Reading   │ Medium   │ 1kHz      │ 0.5ms            │
│ Communication    │ Medium   │ 100Hz     │ 1ms              │
│ Diagnostics      │ Low      │ 10Hz      │ 1ms              │
│ Watchdog         │ High     │ 1Hz       │ 0.1ms            │
└─────────────────────────────────────────────────────────────┘
```

### Safety Architecture

#### Dual-Channel Design
```
┌─────────────────────────────────────────────────────────────┐
│                    Safety Architecture                      │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐                    ┌─────────────┐         │
│  │ Channel A   │                    │ Channel B   │         │
│  │             │                    │             │         │
│  │ • Sensor    │◄─── Cross Check ──►│ • Sensor    │         │
│  │   Input     │                    │   Input     │         │
│  │ • Processing│                    │ • Processing│         │
│  │ • Actuator  │                    │ • Actuator  │         │
│  │   Output    │                    │   Output    │         │
│  └─────────────┘                    └─────────────┘         │
│           │                                │                │
│           └─────────── Voter ──────────────┘                │
│                                │                            │
│                         ┌─────────────┐                    │
│                         │ Safe State  │                    │
│                         │ Controller  │                    │
│                         └─────────────┘                    │
└─────────────────────────────────────────────────────────────┘
```

#### Fault Detection Mechanisms
- **Sensor Fault Detection**: Range checking, rate limiting, cross-validation
- **Processing Fault Detection**: Watchdog timer, memory protection, stack overflow
- **Actuator Fault Detection**: Current monitoring, position feedback, response time
- **Communication Fault Detection**: CRC checking, timeout monitoring, sequence numbers

## Communication Architecture

### CAN Bus Configuration
```
┌─────────────────────────────────────────────────────────────┐
│                    CAN Bus Architecture                     │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐      │
│  │    EBS      │    │   Engine    │    │  Steering   │      │
│  │   ECU       │    │    ECU      │    │    ECU      │      │
│  │             │    │             │    │             │      │
│  │ • Brake     │    │ • Engine    │    │ • Steering  │      │
│  │   Status    │    │   Speed     │    │   Angle     │      │
│  │ • Wheel     │    │ • Torque    │    │ • Yaw Rate  │      │
│  │   Speed     │    │ • Gear      │    │             │      │
│  └─────────────┘    └─────────────┘    └─────────────┘      │
│           │                │                │               │
│           └────────────────┼────────────────┘               │
│                            │                                │
│                    ┌─────────────┐                          │
│                    │   Vehicle   │                          │
│                    │    CAN      │                          │
│                    │   (500kbps) │                          │
│                    └─────────────┘                          │
└─────────────────────────────────────────────────────────────┘
```

### CAN Message Definitions

#### EBS Status Messages
```c
// EBS Status (ID: 0x100)
struct EBS_Status {
    uint16_t brake_pressure_front;    // 0.1 bar resolution
    uint16_t brake_pressure_rear;     // 0.1 bar resolution
    uint8_t abs_active;               // Bit field for each wheel
    uint8_t esc_active;               // ESC intervention status
    uint8_t system_status;            // System health status
    uint8_t fault_codes[4];           // Active fault codes
};

// Wheel Speed (ID: 0x101)
struct Wheel_Speed {
    uint16_t wheel_speed_fl;          // 0.1 km/h resolution
    uint16_t wheel_speed_fr;          // 0.1 km/h resolution
    uint16_t wheel_speed_rl;          // 0.1 km/h resolution
    uint16_t wheel_speed_rr;          // 0.1 km/h resolution
    uint16_t wheel_speed_aux1;        // 0.1 km/h resolution
    uint16_t wheel_speed_aux2;        // 0.1 km/h resolution
};
```

## Power Architecture

### Power Supply Design
```
┌─────────────────────────────────────────────────────────────┐
│                    Power Architecture                       │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐      │
│  │   Vehicle   │    │   Main      │    │   Backup    │      │
│  │   Battery   │───►│  Power      │───►│   Battery   │      │
│  │   (24V)     │    │  Supply     │    │   (24V)     │      │
│  └─────────────┘    └─────────────┘    └─────────────┘      │
│                            │                                │
│                    ┌─────────────┐                          │
│                    │   Power     │                          │
│                    │ Management  │                          │
│                    │   Unit      │                          │
│                    └─────────────┘                          │
│                            │                                │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐      │
│  │   5V        │    │   3.3V      │    │   12V       │      │
│  │   Digital   │    │   Analog    │    │   Actuator  │      │
│  │   Logic     │    │   Sensors   │    │   Power     │      │
│  └─────────────┘    └─────────────┘    └─────────────┘      │
└─────────────────────────────────────────────────────────────┘
```

### Power Management Features
- **Input Protection**: Reverse polarity, overvoltage, undervoltage
- **Voltage Regulation**: Multiple regulated outputs
- **Current Monitoring**: Overcurrent protection for all outputs
- **Battery Backup**: Uninterrupted operation during power loss
- **Power Sequencing**: Controlled startup and shutdown

## Component Specifications

### ECU Enclosure
- **Material**: Aluminum with thermal management
- **Protection**: IP67 (dust and water resistant)
- **Mounting**: DIN rail or direct mounting
- **Connectors**: Automotive grade, sealed
- **Thermal**: -40°C to +85°C operating temperature

### Cable Harness
- **Shielding**: EMI/RFI protection
- **Connectors**: Sealed, automotive grade
- **Wire Gauge**: Appropriate for current requirements
- **Routing**: Protected from heat and vibration

## Integration Points

### Vehicle Integration
- **Mounting**: Engine compartment or chassis
- **Cooling**: Natural convection or forced air
- **Vibration**: Isolated mounting system
- **EMC**: Proper grounding and shielding

### System Integration
- **CAN Bus**: Vehicle network integration
- **Power**: Vehicle electrical system
- **Sensors**: Existing vehicle sensors
- **Actuators**: Brake system integration

## Development Tools

### Hardware Development
- **ECU Development Kit**: Prototype hardware
- **Interface Modules**: Sensor and actuator simulators
- **Test Equipment**: Oscilloscope, multimeter, CAN analyzer

### Software Development
- **IDE**: Eclipse, IAR, or similar
- **Debugger**: JTAG/SWD interface
- **Simulator**: Hardware-in-the-loop testing
- **Version Control**: Git or similar

## Testing and Validation

### Hardware Testing
- **Environmental**: Temperature, humidity, vibration
- **EMC**: Electromagnetic compatibility
- **Electrical**: Power consumption, signal integrity
- **Mechanical**: Shock, vibration, thermal cycling

### Software Testing
- **Unit Testing**: Individual module testing
- **Integration Testing**: Module interaction testing
- **System Testing**: Complete system validation
- **Safety Testing**: Fault injection and response

## Documentation Requirements

### Design Documentation
- **Schematic Diagrams**: Electrical schematics
- **PCB Layout**: Printed circuit board design
- **Mechanical Drawings**: Enclosure and mounting
- **Interface Specifications**: Connector pinouts

### Software Documentation
- **Architecture Design**: Software structure
- **API Documentation**: Function interfaces
- **Configuration Guide**: Parameter settings
- **Troubleshooting Guide**: Fault diagnosis

## Change History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2024 | Architecture Team | Initial version |

## Approval

| Role | Name | Date | Signature |
|------|------|------|-----------|
| System Architect | | | |
| Hardware Engineer | | | |
| Software Engineer | | | |
| Project Manager | | | | 