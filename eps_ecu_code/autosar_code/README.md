# AUTOSAR Electric Power Steering (EPS) System

This project implements an Electric Power Steering system following the AUTOSAR (AUTomotive Open System ARchitecture) standard.

## Project Structure

```
autosar_code/
├── bsw/                    # Basic Software
│   ├── mcal/              # Microcontroller Abstraction Layer
│   ├── ecual/             # ECU Abstraction Layer
│   ├── services/          # AUTOSAR Services
│   └── os/                # Operating System
├── swc/                   # Software Components
│   ├── eps_control/       # Main EPS Control Algorithm
│   ├── sensor_interface/  # Sensor Data Acquisition
│   ├── motor_control/     # Motor Control Interface
│   └── fault_management/  # Fault Detection and Handling
├── config/                # Configuration Files
│   ├── mcal/             # MCAL Configuration
│   ├── ecual/            # ECUAL Configuration
│   ├── services/         # Services Configuration
│   ├── os/               # OS Configuration
│   └── swc/              # SWC Configuration
└── doc/                  # Documentation
```

## Key Features

- **Sensor Data Acquisition**: Torque sensor, steering angle sensor, vehicle speed sensor
- **EPS Control Algorithm**: Assist torque calculation with speed-dependent mapping
- **Motor Control**: Electric motor control with PID regulation
- **Fault Management**: Comprehensive fault detection and failsafe modes
- **ADAS Integration**: Support for advanced driver assistance systems

## Implementation Details

Based on the EPS design document, this AUTOSAR implementation includes:
- Real-time sensor data processing
- Adaptive assist torque calculation
- Motor control with feedback loops
- Fault detection and management
- Integration capabilities for ADAS features

## Building and Deployment

Refer to individual component documentation for build instructions and configuration details. 