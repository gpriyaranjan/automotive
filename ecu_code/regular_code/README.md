# Electric Power Steering (EPS) Control System

This repository contains a C implementation of an Electric Power Steering control algorithm based on the design specifications in `eps_design.md`.

## Overview

The EPS control system is a real-time embedded control algorithm that provides intelligent steering assistance based on driver input and vehicle conditions. The system operates at 1kHz and implements all the key components described in the design document:

- **Sensor Data Acquisition**: Reads torque, steering angle, and vehicle speed sensors
- **Data Processing**: Applies filtering and calculates derived values
- **Assist Torque Calculation**: Core logic combining multiple control components
- **Motor Control**: Converts torque commands to motor current commands
- **Feedback Monitoring**: Monitors motor performance and adjusts control
- **Fault Detection**: Comprehensive self-diagnosis and error handling

## Key Features

### Control Components
- **Base Assist Mapping**: Maps driver torque and vehicle speed to base assist torque
- **Damping Control**: Prevents oscillations during rapid steering movements
- **Inertia Compensation**: Compensates for steering system inertia
- **Return-to-Center (RTC)**: Assists steering wheel return at low speeds
- **ADAS Integration**: Supports advanced driver assistance system commands
- **Active Damping**: Suppresses road vibrations transmitted to steering wheel

### Safety Features
- **Torque Limiting**: Clamps assist torque within safe operational limits
- **Fault Detection**: Monitors sensors, motor, and system health
- **Failsafe Operation**: Graceful degradation in fault conditions
- **Self-Diagnosis**: Continuous system health monitoring

### Performance Characteristics
- **Sampling Rate**: 1kHz (1ms loop time)
- **Response Time**: < 10ms for assist torque changes
- **Torque Range**: ±50 Nm assist torque
- **Speed Range**: 0-200 km/h vehicle speed support

## File Structure

```
ecu_code/
├── eps_design.md          # Original design specification
├── eps_control.h          # Header file with declarations and structures
├── eps_control.c          # Main implementation file
├── Makefile              # Build configuration
└── README.md             # This documentation
```

## Building and Running

### Prerequisites
- GCC compiler
- Make build system
- Math library (linked automatically)

### Build Commands
```bash
# Build the system
make

# Build and run
make run

# Build debug version
make debug

# Build optimized release version
make release

# Clean build artifacts
make clean
```

### Running the Program
```bash
./eps_control
```

The program will start the EPS control loop and display status information every second. Press Ctrl+C to stop.

## Implementation Details

### Data Structures

#### `sensor_data_t`
Contains raw sensor readings:
- `driver_torque`: Driver applied torque (Nm)
- `steering_angle`: Steering wheel angle (degrees)
- `vehicle_speed`: Vehicle speed (km/h)
- `motor_current`: Motor current feedback (A)
- `motor_position`: Motor position feedback (degrees)

#### `filtered_data_t`
Contains processed sensor data:
- `filtered_torque`: Low-pass filtered driver torque
- `filtered_angle`: Low-pass filtered steering angle
- `filtered_speed`: Low-pass filtered vehicle speed
- `angular_velocity`: Calculated steering angular velocity (deg/s)
- `angular_acceleration`: Calculated steering angular acceleration (deg/s²)

#### `control_params_t`
Contains control system outputs:
- `target_assist_torque`: Calculated assist torque (Nm)
- `motor_current_command`: Motor current command (A)
- `adas_active`: ADAS system active flag
- `adas_command_torque`: ADAS torque command (Nm)

#### `system_state_t`
Contains system status:
- `system_initialized`: System initialization flag
- `fault_detected`: Fault detection flag
- `fault_code`: Specific fault code
- `loop_counter`: Control loop iteration counter

### Key Functions

#### `eps_control_loop()`
Main control loop implementing the complete EPS algorithm. This function should be called at 1kHz.

#### `eps_calculate_assist_torque()`
Core logic combining all assist torque components:
1. Base assist from lookup table
2. Damping component
3. Inertia compensation
4. Return-to-center component
5. ADAS integration
6. Safety limiting

#### `eps_perform_self_diagnosis()`
Performs comprehensive system health checks:
- Sensor range validation
- Motor current monitoring
- Communication health
- System integrity checks

## Configuration

The system can be configured by modifying the constants in `eps_control.h`:

```c
#define SAMPLING_RATE_HZ          1000    // Control loop frequency
#define LOW_SPEED_THRESHOLD       10.0f   // RTC activation speed
#define MIN_ASSIST_LIMIT          -50.0f  // Minimum assist torque
#define MAX_ASSIST_LIMIT          50.0f   // Maximum assist torque
#define FILTER_ALPHA              0.1f    // Low-pass filter coefficient
#define DAMPING_COEFFICIENT       0.5f    // Damping strength
#define INERTIA_COEFFICIENT       0.2f    // Inertia compensation strength
#define RTC_COEFFICIENT           0.3f    // Return-to-center strength
```

## Integration Notes

### Hardware Integration
In a real implementation, the following hardware interfaces would need to be implemented:

1. **Sensor Interfaces**:
   - ADC for torque sensor
   - CAN bus for vehicle speed
   - Encoder interface for steering angle
   - Current sensor for motor feedback

2. **Motor Control**:
   - PWM generation for motor driver
   - Current control loop
   - Position feedback processing

3. **Communication**:
   - CAN bus for vehicle communication
   - Diagnostic interface
   - ADAS system interface

### Real-Time Requirements
- **Loop Time**: Must complete within 1ms
- **Jitter**: < 10μs timing variation
- **Priority**: High priority real-time task
- **Interrupts**: Timer-based execution

### Safety Considerations
- **Redundancy**: Critical sensors should have backup
- **Watchdog**: System watchdog for fault recovery
- **Power Management**: Graceful shutdown on power loss
- **EMC**: Electromagnetic compatibility considerations

## Testing and Validation

### Unit Testing
Each function can be unit tested independently:
```c
// Example test for assist torque calculation
void test_assist_torque_calculation() {
    // Set up test conditions
    filtered.filtered_torque = 5.0f;
    filtered.filtered_speed = 30.0f;
    
    // Execute function
    eps_calculate_assist_torque();
    
    // Verify results
    assert(control.target_assist_torque > 0.0f);
    assert(control.target_assist_torque <= MAX_ASSIST_LIMIT);
}
```

### Integration Testing
Test the complete control loop with simulated sensor inputs and verify motor commands.

### Hardware-in-the-Loop Testing
Test with actual EPS hardware in a controlled environment.

## Future Enhancements

1. **Advanced Control Algorithms**:
   - Model predictive control
   - Adaptive control
   - Fuzzy logic control

2. **Enhanced Safety Features**:
   - Redundant sensor validation
   - Advanced fault detection
   - Predictive maintenance

3. **ADAS Integration**:
   - Lane keeping assist
   - Automated parking
   - Collision avoidance

4. **Performance Optimization**:
   - Fixed-point arithmetic
   - Lookup table optimization
   - Memory usage optimization

## License

This implementation is provided as a reference for educational and development purposes. For commercial use, ensure compliance with relevant automotive safety standards (ISO 26262, ASIL requirements).

## Contributing

When contributing to this project:
1. Follow the existing code style
2. Add appropriate documentation
3. Include unit tests for new features
4. Ensure real-time performance requirements are met
5. Validate safety-critical changes thoroughly 