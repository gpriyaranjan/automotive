# Electronic Power Steering (EPS) Functional Requirements

## 1. Introduction

### 1.1 Purpose
This document defines the functional requirements for the Electronic Power Steering (EPS) system. These requirements specify what the system shall do from a functional perspective, serving as the basis for system design, implementation, and verification.

### 1.2 Scope
This document covers all functional requirements for the EPS system as defined in the Item Definition. It includes primary steering functions, secondary comfort functions, safety functions, and diagnostic functions.

### 1.3 Requirements Notation
- **SHALL**: Mandatory requirement
- **SHOULD**: Recommended requirement
- **MAY**: Optional requirement
- **REQ-ID**: Unique requirement identifier format: EPS-FR-XXX

## 2. Primary Steering Functions

### 2.1 Steering Assistance Function

**EPS-FR-001**: The EPS system SHALL provide steering assistance torque to reduce driver steering effort.

**EPS-FR-002**: The EPS system SHALL calculate the required assistance torque based on:
- Driver input torque (from torque sensor)
- Vehicle speed
- Steering wheel angle
- System operating mode

**EPS-FR-003**: The EPS system SHALL provide assistance torque in the same direction as the driver's steering input.

**EPS-FR-004**: The EPS system SHALL limit the maximum assistance torque to prevent over-assistance.

**EPS-FR-005**: The EPS system SHALL provide smooth torque transitions without abrupt changes that could affect vehicle stability.

**EPS-FR-006**: The EPS system SHALL maintain steering assistance capability across the full range of steering wheel angles (-720° to +720°).

### 2.2 Torque Sensing Function

**EPS-FR-007**: The EPS system SHALL continuously monitor driver steering input torque through the torque sensor.

**EPS-FR-008**: The EPS system SHALL detect the direction of driver steering input (clockwise or counterclockwise).

**EPS-FR-009**: The EPS system SHALL measure torque with sufficient resolution to provide smooth assistance response.

**EPS-FR-010**: The EPS system SHALL compensate for torque sensor temperature effects to maintain accuracy.

**EPS-FR-011**: The EPS system SHALL detect torque sensor faults and respond appropriately.

### 2.3 Motor Control Function

**EPS-FR-012**: The EPS system SHALL control the electric motor to provide the calculated assistance torque.

**EPS-FR-013**: The EPS system SHALL use closed-loop control to achieve accurate torque output.

**EPS-FR-014**: The EPS system SHALL monitor motor position for precise control.

**EPS-FR-015**: The EPS system SHALL limit motor current to prevent overheating and component damage.

**EPS-FR-016**: The EPS system SHALL provide motor control with minimal noise and vibration.

## 3. Speed-Sensitive Steering Function

### 3.1 Speed-Based Assistance Adjustment

**EPS-FR-017**: The EPS system SHALL adjust steering assistance based on vehicle speed.

**EPS-FR-018**: The EPS system SHALL provide maximum assistance at low speeds (parking, maneuvering).

**EPS-FR-019**: The EPS system SHALL reduce assistance at high speeds to maintain road feel and stability.

**EPS-FR-020**: The EPS system SHALL use a smooth transition curve for speed-based assistance adjustment.

**EPS-FR-021**: The EPS system SHALL receive vehicle speed information from the vehicle CAN network.

**EPS-FR-022**: The EPS system SHALL handle vehicle speed signal loss gracefully with appropriate fallback behavior.

## 4. Return-to-Center Function

### 4.1 Passive Return-to-Center

**EPS-FR-023**: The EPS system SHALL assist the steering wheel return to center position when driver input is removed.

**EPS-FR-024**: The EPS system SHALL calculate return-to-center torque based on:
- Current steering wheel angle
- Vehicle speed
- Return-to-center gain settings

**EPS-FR-025**: The EPS system SHALL provide stronger return-to-center assistance at higher speeds.

### 4.2 Active Return Function

**EPS-FR-026**: The EPS system SHALL provide active return assistance during low-speed maneuvers.

**EPS-FR-027**: The EPS system SHALL modulate active return based on driver activity detection.

**EPS-FR-028**: The EPS system SHALL disable active return when driver torque input is detected.

## 5. Damping Function

### 5.1 Steering Damping

**EPS-FR-029**: The EPS system SHALL provide steering damping to improve steering stability and feel.

**EPS-FR-030**: The EPS system SHALL calculate damping torque based on steering wheel angular velocity.

**EPS-FR-031**: The EPS system SHALL adjust damping characteristics based on vehicle speed.

**EPS-FR-032**: The EPS system SHALL provide higher damping at high speeds for stability.

## 6. System Operating Modes

### 6.1 Normal Operation Mode

**EPS-FR-033**: The EPS system SHALL operate in normal mode when all system components are functioning correctly.

**EPS-FR-034**: In normal mode, the EPS system SHALL provide full steering assistance functionality.

**EPS-FR-035**: The EPS system SHALL continuously monitor system health during normal operation.

### 6.2 Degraded Operation Mode

**EPS-FR-036**: The EPS system SHALL enter degraded mode when non-critical faults are detected.

**EPS-FR-037**: In degraded mode, the EPS system SHALL maintain basic steering assistance with reduced functionality.

**EPS-FR-038**: The EPS system SHALL inform the driver of degraded operation through appropriate warning signals.

### 6.3 Fail-Safe Mode

**EPS-FR-039**: The EPS system SHALL enter fail-safe mode when critical faults are detected.

**EPS-FR-040**: In fail-safe mode, the EPS system SHALL ensure manual steering capability is maintained.

**EPS-FR-041**: The EPS system SHALL provide maximum warning to the driver when in fail-safe mode.

### 6.4 Sleep Mode

**EPS-FR-042**: The EPS system SHALL enter sleep mode when the vehicle is turned off.

**EPS-FR-043**: In sleep mode, the EPS system SHALL minimize power consumption.

**EPS-FR-044**: The EPS system SHALL wake up when ignition is turned on or CAN wake-up signal is received.

## 7. Communication Functions

### 7.1 CAN Communication

**EPS-FR-045**: The EPS system SHALL communicate with other vehicle systems via CAN bus.

**EPS-FR-046**: The EPS system SHALL transmit the following information on CAN:
- System status
- Steering wheel angle
- Assistance torque
- Fault codes
- System temperature

**EPS-FR-047**: The EPS system SHALL receive the following information from CAN:
- Vehicle speed
- Engine status
- Diagnostic commands
- Calibration parameters

**EPS-FR-048**: The EPS system SHALL handle CAN communication errors gracefully.

### 7.2 Diagnostic Communication

**EPS-FR-049**: The EPS system SHALL support diagnostic communication protocols (UDS/KWP2000).

**EPS-FR-050**: The EPS system SHALL provide access to diagnostic trouble codes (DTCs).

**EPS-FR-051**: The EPS system SHALL support parameter reading and writing for calibration.

**EPS-FR-052**: The EPS system SHALL support actuator tests for diagnostic purposes.

## 8. Safety Functions

### 8.1 Fault Detection

**EPS-FR-053**: The EPS system SHALL continuously monitor all critical system components.

**EPS-FR-054**: The EPS system SHALL detect the following fault conditions:
- Torque sensor faults
- Motor faults
- Position sensor faults
- Power supply faults
- Communication faults
- Software faults

**EPS-FR-055**: The EPS system SHALL classify faults by severity and respond appropriately.

### 8.2 Fault Response

**EPS-FR-056**: The EPS system SHALL respond to faults within the specified reaction time.

**EPS-FR-057**: The EPS system SHALL prioritize maintaining manual steering capability above all other functions.

**EPS-FR-058**: The EPS system SHALL store fault information for diagnostic purposes.

**EPS-FR-059**: The EPS system SHALL clear faults when the fault condition is no longer present.

### 8.3 Redundancy Functions

**EPS-FR-060**: The EPS system SHALL implement redundant sensing for critical measurements.

**EPS-FR-061**: The EPS system SHALL use diverse monitoring techniques for fault detection.

**EPS-FR-062**: The EPS system SHALL provide backup functionality for critical system functions.

## 9. Driver Monitoring Functions

### 9.1 Hands-Off Detection

**EPS-FR-063**: The EPS system SHALL detect when the driver's hands are not on the steering wheel.

**EPS-FR-064**: The EPS system SHALL use torque sensor signals to determine driver presence.

**EPS-FR-065**: The EPS system SHALL provide hands-off detection information to other vehicle systems.

**EPS-FR-066**: The EPS system SHALL adjust system behavior based on driver presence detection.

### 9.2 Driver Activity Monitoring

**EPS-FR-067**: The EPS system SHALL monitor driver steering activity patterns.

**EPS-FR-068**: The EPS system SHALL detect unusual steering patterns that may indicate driver impairment.

**EPS-FR-069**: The EPS system SHALL provide driver activity information to appropriate vehicle systems.

## 10. Calibration Functions

### 10.1 System Calibration

**EPS-FR-070**: The EPS system SHALL support calibration of system parameters.

**EPS-FR-071**: The EPS system SHALL store calibration parameters in non-volatile memory.

**EPS-FR-072**: The EPS system SHALL validate calibration parameters before use.

**EPS-FR-073**: The EPS system SHALL use default parameters if calibration data is invalid.

### 10.2 Sensor Calibration

**EPS-FR-074**: The EPS system SHALL support torque sensor zero-point calibration.

**EPS-FR-075**: The EPS system SHALL support steering angle sensor calibration.

**EPS-FR-076**: The EPS system SHALL perform automatic calibration procedures when possible.

**EPS-FR-077**: The EPS system SHALL indicate calibration status to diagnostic tools.

## 11. Performance Functions

### 11.1 Response Time Requirements

**EPS-FR-078**: The EPS system SHALL respond to driver input within 50ms.

**EPS-FR-079**: The EPS system SHALL achieve steady-state assistance within 100ms.

**EPS-FR-080**: The EPS system SHALL detect and respond to faults within 100ms.

### 11.2 Accuracy Requirements

**EPS-FR-081**: The EPS system SHALL provide assistance torque with ±5% accuracy.

**EPS-FR-082**: The EPS system SHALL maintain torque accuracy across the operating temperature range.

**EPS-FR-083**: The EPS system SHALL provide steering angle measurement with ±1° accuracy.

### 11.3 Stability Requirements

**EPS-FR-084**: The EPS system SHALL maintain stable operation without oscillations.

**EPS-FR-085**: The EPS system SHALL provide consistent steering feel across all operating conditions.

**EPS-FR-086**: The EPS system SHALL not introduce unwanted steering wheel vibrations.

## 12. Environmental Functions

### 12.1 Temperature Management

**EPS-FR-087**: The EPS system SHALL monitor component temperatures.

**EPS-FR-088**: The EPS system SHALL reduce assistance when temperature limits are approached.

**EPS-FR-089**: The EPS system SHALL protect components from overheating.

**EPS-FR-090**: The EPS system SHALL resume normal operation when temperatures return to safe levels.

### 12.2 EMC Functions

**EPS-FR-091**: The EPS system SHALL operate correctly in the presence of electromagnetic interference.

**EPS-FR-092**: The EPS system SHALL not generate electromagnetic interference that affects other systems.

**EPS-FR-093**: The EPS system SHALL maintain functionality during EMC test conditions.

## 13. Power Management Functions

### 13.1 Power Consumption

**EPS-FR-094**: The EPS system SHALL limit power consumption to specified maximum values.

**EPS-FR-095**: The EPS system SHALL optimize power consumption based on assistance demand.

**EPS-FR-096**: The EPS system SHALL monitor supply voltage and adjust operation accordingly.

### 13.2 Low Voltage Operation

**EPS-FR-097**: The EPS system SHALL operate correctly down to minimum supply voltage.

**EPS-FR-098**: The EPS system SHALL provide graceful degradation at low voltages.

**EPS-FR-099**: The EPS system SHALL protect against undervoltage conditions.

## 14. Software Functions

### 14.1 Software Architecture

**EPS-FR-100**: The EPS system software SHALL follow AUTOSAR architecture standards.

**EPS-FR-101**: The EPS system SHALL implement safety mechanisms in software.

**EPS-FR-102**: The EPS system SHALL support software updates through secure bootloader.

### 14.2 Data Management

**EPS-FR-103**: The EPS system SHALL manage configuration data securely.

**EPS-FR-104**: The EPS system SHALL maintain data integrity through checksums or similar methods.

**EPS-FR-105**: The EPS system SHALL log critical events for analysis.

## 15. Requirements Traceability

### 15.1 Traceability Matrix
Each functional requirement SHALL be traceable to:
- System requirements
- Safety requirements
- Test cases
- Design elements
- Verification methods

### 15.2 Requirements Verification
Each functional requirement SHALL be verified through:
- Analysis
- Inspection
- Testing
- Demonstration

## 16. Document Control

### 16.1 Document Information
- **Document ID**: EPS-FR-001
- **Version**: 1.0
- **Status**: Draft
- **Classification**: Internal Use

### 16.2 Change Control
All changes to functional requirements SHALL follow the established change control process with appropriate impact assessment and approval.