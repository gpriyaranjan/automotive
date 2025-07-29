# Electronic Braking System (EBS) - System Architecture Specification

## Document Information
- **Document Title**: EBS System Architecture Specification
- **Version**: 1.0
- **Date**: 2025-07-29
- **Classification**: Technical Design Document
- **Related Documents**: EBS_Requirements_Specification.md

## Table of Contents
1. [Introduction](#introduction)
2. [System Architecture Overview](#system-architecture-overview)
3. [Hardware Architecture](#hardware-architecture)
4. [Software Architecture](#software-architecture)
5. [Network Architecture](#network-architecture)
6. [Safety Architecture](#safety-architecture)
7. [Data Flow Architecture](#data-flow-architecture)
8. [Deployment Architecture](#deployment-architecture)

---

## 1. Introduction

### 1.1 Purpose
This document defines the system architecture for the Electronic Braking System (EBS), providing detailed technical specifications for hardware, software, network, and safety architectures.

### 1.2 Scope
The architecture covers:
- System-level design and component interactions
- Hardware and software architecture patterns
- Communication protocols and data flows
- Safety mechanisms and redundancy strategies
- Deployment and integration considerations

### 1.3 Architecture Principles
- **Safety First**: All architectural decisions prioritize functional safety
- **Redundancy**: Critical functions have backup mechanisms
- **Modularity**: Components are designed for maintainability and testability
- **Scalability**: Architecture supports future enhancements
- **Real-time Performance**: Deterministic response times for safety-critical functions

---

## 2. System Architecture Overview

### 2.1 High-Level Architecture

```mermaid
graph TB
    subgraph "Driver Interface"
        BP[Brake Pedal]
        DI[Dashboard Indicators]
        SW[System Switches]
    end
    
    subgraph "EBS Control System"
        PECU[Primary ECU]
        SECU[Secondary ECU]
        HMU[Hydraulic Modulator Unit]
    end
    
    subgraph "Sensors"
        WS1[Wheel Speed Sensor FL]
        WS2[Wheel Speed Sensor FR]
        WS3[Wheel Speed Sensor RL]
        WS4[Wheel Speed Sensor RR]
        PS[Pressure Sensors]
        YR[Yaw Rate Sensor]
        LA[Lateral Acceleration]
        SA[Steering Angle]
    end
    
    subgraph "Actuators"
        BA1[Brake Actuator FL]
        BA2[Brake Actuator FR]
        BA3[Brake Actuator RL]
        BA4[Brake Actuator RR]
        HV[Hydraulic Valves]
    end
    
    subgraph "Vehicle Systems"
        EMS[Engine Management]
        IC[Instrument Cluster]
        BCM[Body Control Module]
        GW[Gateway]
    end
    
    BP --> PECU
    PECU <--> SECU
    PECU --> HMU
    
    WS1 --> PECU
    WS2 --> PECU
    WS3 --> PECU
    WS4 --> PECU
    PS --> PECU
    YR --> PECU
    LA --> PECU
    SA --> PECU
    
    PECU --> BA1
    PECU --> BA2
    PECU --> BA3
    PECU --> BA4
    HMU --> HV
    
    PECU <--> EMS
    PECU <--> IC
    PECU <--> BCM
    PECU <--> GW
    
    PECU --> DI
```

### 2.2 System Layers

| Layer | Components | Responsibility |
|-------|------------|----------------|
| **Application Layer** | ABS, ESC, TCS Algorithms | Safety functions and control logic |
| **Control Layer** | ECU Software, Real-time OS | System coordination and resource management |
| **Communication Layer** | CAN, SPI, PWM Interfaces | Inter-component communication |
| **Hardware Layer** | ECUs, Sensors, Actuators | Physical system components |

---

## 3. Hardware Architecture

### 3.1 ECU Architecture

#### 3.1.1 Primary ECU Specifications
- **Processor**: Dual-core ARM Cortex-R5F @ 300MHz
- **Memory**: 2MB Flash, 512KB RAM, 64KB EEPROM
- **Safety**: ASIL-D certified microcontroller
- **Interfaces**: 2x CAN, 4x SPI, 8x PWM, 16x ADC, 32x GPIO
- **Power**: 12V automotive supply with voltage regulation
- **Temperature Range**: -40°C to +125°C

#### 3.1.2 Secondary ECU (Backup)
- **Processor**: Single-core ARM Cortex-R4F @ 200MHz
- **Memory**: 1MB Flash, 256KB RAM, 32KB EEPROM
- **Safety**: ASIL-D certified microcontroller
- **Interfaces**: 1x CAN, 2x SPI, 4x PWM, 8x ADC, 16x GPIO
- **Function**: Monitors primary ECU and provides backup control

### 3.2 Sensor Architecture

#### 3.2.1 Wheel Speed Sensors
- **Type**: Hall Effect with magnetic encoder ring
- **Resolution**: 48 pulses per revolution
- **Frequency Range**: 0-10 kHz
- **Supply Voltage**: 5V ±5%
- **Output**: Digital square wave
- **Cable**: Twisted pair with shield

#### 3.2.2 Inertial Measurement Unit (IMU)
- **Components**: 3-axis gyroscope, 3-axis accelerometer
- **Range**: ±300°/s (yaw), ±16g (acceleration)
- **Resolution**: 16-bit ADC
- **Sample Rate**: 1000 Hz
- **Interface**: SPI
- **Calibration**: Factory calibrated with runtime compensation

#### 3.2.3 Pressure Sensors
- **Type**: Piezoresistive silicon sensor
- **Range**: 0-250 bar
- **Accuracy**: ±1% full scale
- **Response Time**: <1ms
- **Output**: 0.5-4.5V analog
- **Temperature Compensation**: Integrated

### 3.3 Actuator Architecture

#### 3.3.1 Hydraulic Modulator Unit
- **Valves**: 8x solenoid valves (inlet/outlet per wheel)
- **Pump**: Electric motor driven piston pump
- **Accumulator**: High-pressure brake fluid storage
- **Control**: PWM valve control (1-5 kHz)
- **Pressure Rating**: 300 bar maximum
- **Response Time**: <10ms valve switching

#### 3.3.2 Electric Brake Actuators (Future Enhancement)
- **Type**: Electromechanical brake calipers
- **Force**: 0-50 kN clamping force
- **Control**: CAN-based position/force control
- **Feedback**: Integrated position and force sensors
- **Redundancy**: Dual motor configuration

---

## 4. Software Architecture

### 4.1 Software Stack

```mermaid
graph TB
    subgraph "Application Layer"
        ABS[ABS Algorithm]
        ESC[ESC Algorithm]
        TCS[TCS Algorithm]
        DM[Diagnostic Manager]
    end
    
    subgraph "Service Layer"
        SM[Safety Manager]
        CM[Communication Manager]
        IM[Input Manager]
        OM[Output Manager]
    end
    
    subgraph "Platform Layer"
        RTOS[Real-Time OS]
        HAL[Hardware Abstraction Layer]
        BSW[Basic Software]
    end
    
    subgraph "Hardware Layer"
        MCU[Microcontroller]
        PERI[Peripherals]
    end
    
    ABS --> SM
    ESC --> SM
    TCS --> SM
    DM --> SM
    
    SM --> CM
    SM --> IM
    SM --> OM
    
    CM --> RTOS
    IM --> RTOS
    OM --> RTOS
    
    RTOS --> HAL
    HAL --> BSW
    BSW --> MCU
    MCU --> PERI
```

### 4.2 Real-Time Operating System
- **RTOS**: AUTOSAR Classic Platform
- **Scheduling**: Priority-based preemptive scheduling
- **Tasks**: 
  - Safety Task (1ms cycle, highest priority)
  - Control Task (5ms cycle, high priority)
  - Communication Task (10ms cycle, medium priority)
  - Diagnostic Task (100ms cycle, low priority)

### 4.3 Safety Architecture
- **Safety Concept**: Freedom from Interference (FFI)
- **Memory Protection**: MPU-based memory partitioning
- **Time Protection**: Watchdog timers and execution time monitoring
- **Communication Protection**: CRC and sequence number checking
- **Redundancy**: Dual-channel architecture with cross-checking

### 4.4 Algorithm Architecture

#### 4.4.1 ABS Algorithm
```mermaid
flowchart TD
    A[Wheel Speed Input] --> B[Slip Calculation]
    B --> C{Slip > Threshold?}
    C -->|Yes| D[Pressure Reduction]
    C -->|No| E[Normal Braking]
    D --> F[Monitor Wheel Recovery]
    F --> G{Wheel Accelerating?}
    G -->|Yes| H[Pressure Hold]
    G -->|No| D
    H --> I{Slip Acceptable?}
    I -->|Yes| J[Pressure Increase]
    I -->|No| D
    J --> B
    E --> B
```

#### 4.4.2 ESC Algorithm
```mermaid
flowchart TD
    A[Vehicle Sensors] --> B[Vehicle State Estimation]
    B --> C[Reference Model]
    C --> D[Deviation Calculation]
    D --> E{Deviation > Threshold?}
    E -->|Yes| F[Stability Control Active]
    E -->|No| G[Monitor Only]
    F --> H[Individual Wheel Braking]
    F --> I[Engine Torque Reduction]
    H --> J[Vehicle Response]
    I --> J
    J --> B
    G --> B
```

---

## 5. Network Architecture

### 5.1 CAN Network Topology

```mermaid
graph LR
    subgraph "High-Speed CAN (500 kbps)"
        EBS[EBS ECU]
        EMS[Engine Management]
        TCM[Transmission Control]
        IC[Instrument Cluster]
    end
    
    subgraph "Body CAN (125 kbps)"
        BCM[Body Control Module]
        HVAC[Climate Control]
        DOOR[Door Modules]
    end
    
    GW[Gateway]
    
    EBS <--> EMS
    EBS <--> TCM
    EBS <--> IC
    EBS <--> GW
    
    GW <--> BCM
    GW <--> HVAC
    GW <--> DOOR
```

### 5.2 Message Architecture

#### 5.2.1 Critical Messages (High Priority)
| Message ID | Source | Destination | Cycle Time | Data Length |
|------------|--------|-------------|------------|-------------|
| 0x100 | EBS | Engine | 10ms | 8 bytes |
| 0x101 | EBS | Instrument | 20ms | 8 bytes |
| 0x102 | Engine | EBS | 10ms | 8 bytes |
| 0x103 | Steering | EBS | 20ms | 8 bytes |

#### 5.2.2 Diagnostic Messages (Low Priority)
| Message ID | Source | Destination | Cycle Time | Data Length |
|------------|--------|-------------|------------|-------------|
| 0x7E0 | Tester | EBS | On-demand | 8 bytes |
| 0x7E8 | EBS | Tester | Response | 8 bytes |

---

## 6. Safety Architecture

### 6.1 Safety Concept

#### 6.1.1 Hazard Analysis Results
| Hazard | ASIL | Safety Goal | Safety Mechanism |
|--------|------|-------------|------------------|
| Unintended braking | D | Prevent false activation | Dual-channel validation |
| Loss of braking | D | Maintain stopping capability | Fallback to manual braking |
| Delayed braking | D | Ensure timely response | Watchdog monitoring |
| Asymmetric braking | C | Prevent vehicle instability | Cross-axle monitoring |

#### 6.1.2 Safety Mechanisms

```mermaid
graph TB
    subgraph "Input Validation"
        IV1[Sensor Plausibility Check]
        IV2[Range Validation]
        IV3[Rate Limit Check]
    end
    
    subgraph "Processing Safety"
        PS1[Dual-Channel Processing]
        PS2[Cross-Channel Comparison]
        PS3[Watchdog Monitoring]
    end
    
    subgraph "Output Safety"
        OS1[Actuator Feedback]
        OS2[Safe State Management]
        OS3[Degraded Mode Operation]
    end
    
    IV1 --> PS1
    IV2 --> PS1
    IV3 --> PS1
    
    PS1 --> PS2
    PS2 --> PS3
    
    PS3 --> OS1
    OS1 --> OS2
    OS2 --> OS3
```

### 6.2 Fault Tolerance Architecture

#### 6.2.1 Redundancy Levels
- **Level 1**: Sensor redundancy (multiple sensors for critical measurements)
- **Level 2**: Processing redundancy (dual ECU architecture)
- **Level 3**: Actuator redundancy (hydraulic backup for electric actuators)
- **Level 4**: System redundancy (manual brake backup)

#### 6.2.2 Degraded Operation Modes
1. **Normal Mode**: All systems operational
2. **Reduced Mode**: Non-critical functions disabled
3. **Limp Mode**: Basic braking only
4. **Safe Mode**: Manual braking fallback

---

## 7. Data Flow Architecture

### 7.1 Real-Time Data Flow

```mermaid
sequenceDiagram
    participant Driver
    participant BrakePedal
    participant EBS_ECU
    participant Sensors
    participant Actuators
    participant Wheels
    
    Driver->>BrakePedal: Apply brake force
    BrakePedal->>EBS_ECU: Brake request signal
    EBS_ECU->>Sensors: Request sensor data
    Sensors->>EBS_ECU: Wheel speeds, vehicle dynamics
    EBS_ECU->>EBS_ECU: Process control algorithms
    EBS_ECU->>Actuators: Brake commands
    Actuators->>Wheels: Apply brake force
    Wheels->>Sensors: Updated wheel speeds
    
    Note over EBS_ECU: Cycle time: 1-5ms
```

### 7.2 Diagnostic Data Flow

```mermaid
flowchart TD
    A[System Monitoring] --> B[Fault Detection]
    B --> C{Fault Detected?}
    C -->|Yes| D[Fault Classification]
    C -->|No| A
    D --> E[DTC Storage]
    E --> F[Warning Generation]
    F --> G[System Response]
    G --> H{Critical Fault?}
    H -->|Yes| I[Safe State Activation]
    H -->|No| J[Continued Operation]
    I --> K[Driver Notification]
    J --> A
    K --> A
```

---

## 8. Deployment Architecture

### 8.1 Physical Deployment

```mermaid
graph TB
    subgraph "Engine Bay"
        PECU[Primary ECU]
        HMU[Hydraulic Modulator]
        PS[Pressure Sensors]
    end
    
    subgraph "Dashboard"
        SECU[Secondary ECU]
        DI[Warning Lights]
        SW[System Switches]
    end
    
    subgraph "Wheels"
        WS1[WSS Front Left]
        WS2[WSS Front Right]
        WS3[WSS Rear Left]
        WS4[WSS Rear Right]
        BA1[Brake Actuator FL]
        BA2[Brake Actuator FR]
        BA3[Brake Actuator RL]
        BA4[Brake Actuator RR]
    end
    
    subgraph "Center Console"
        IMU[Inertial Sensors]
        SA[Steering Angle Sensor]
    end
    
    PECU <--> SECU
    PECU <--> HMU
    PECU <--> PS
    PECU <--> WS1
    PECU <--> WS2
    PECU <--> WS3
    PECU <--> WS4
    PECU <--> IMU
    PECU <--> SA
    HMU <--> BA1
    HMU <--> BA2
    HMU <--> BA3
    HMU <--> BA4
```

### 8.2 Installation Requirements

#### 8.2.1 ECU Mounting
- **Location**: Engine bay, protected from water and heat
- **Mounting**: Vibration-isolated bracket
- **Orientation**: Connector facing downward
- **Access**: Service access for diagnostics
- **Cooling**: Natural convection cooling

#### 8.2.2 Sensor Installation
- **Wheel Speed Sensors**: Integrated with wheel bearings
- **IMU**: Vehicle center of gravity location
- **Pressure Sensors**: Brake line integration points
- **Steering Sensor**: Steering column integration

#### 8.2.3 Wiring Harness
- **Protection**: Automotive-grade wire protection
- **Routing**: Away from heat sources and moving parts
- **Connectors**: Sealed automotive connectors
- **Shielding**: Twisted pair with shield for critical signals

---

## Document Control

### Revision History
| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2025-07-29 | System Architect | Initial architecture specification |

### Approval
- **Chief Architect**: [Signature Required]
- **Safety Engineer**: [Signature Required]
- **Technical Lead**: [Signature Required]
- **Date**: [Approval Date]

---

*This document contains proprietary and confidential information. Distribution is restricted to authorized personnel only.*