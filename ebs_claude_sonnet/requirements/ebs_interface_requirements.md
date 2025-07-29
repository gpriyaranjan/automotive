# EBS Interface Requirements
**Document ID:** EBS-IR-001  
**Version:** 1.0  
**Date:** 2025-07-29  
**Status:** Draft  

## 1. Document Overview

### 1.1 Purpose
This document specifies the interface requirements for the Electronic Braking System (EBS), defining all external interfaces, communication protocols, signal specifications, and data exchange requirements with other vehicle systems.

### 1.2 Scope
This document covers interface requirements for:
- Sensor interfaces and signal conditioning
- Actuator control interfaces
- Vehicle network communication (CAN, LIN)
- Diagnostic interfaces
- Power and ground interfaces
- Human-machine interfaces
- Inter-system communication protocols

### 1.3 Related Documents
- EBS Item Definition (EBS-ID-001)
- EBS Functional Requirements (EBS-FR-001)
- EBS Electrical Requirements (EBS-EL-001)
- Vehicle Network Architecture Specification

## 2. Interface Requirements Structure

### 2.1 Requirement Identification
Interface requirements are identified using the format: **EBS-IR-XXX-YY**
- EBS: Electronic Braking System
- IR: Interface Requirements
- XXX: Interface type (SEN, ACT, CAN, etc.)
- YY: Sequential number

### 2.2 Interface Attributes
Each interface requirement includes:
- **Signal Type:** Analog, Digital, PWM, CAN, LIN
- **Electrical Specifications:** Voltage levels, current, impedance
- **Timing Requirements:** Update rates, response times
- **Data Format:** Message structure, encoding
- **Error Handling:** Detection and recovery mechanisms

## 3. Sensor Interface Requirements

### 3.1 Wheel Speed Sensor Interfaces

**EBS-IR-SEN-01: Wheel Speed Sensor Signal Type**
- **Description:** The system shall interface with four wheel speed sensors using digital Hall-effect or variable reluctance sensors.
- **Signal Type:** Digital pulse train or analog sinusoidal
- **Frequency Range:** 0 Hz to 10 kHz
- **Voltage Levels:** 0V to 12V (digital), ±2V (analog)
- **Update Rate:** Continuous
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-SEN-02: Wheel Speed Signal Processing**
- **Description:** The system shall process wheel speed signals with noise filtering and signal conditioning.
- **Input Impedance:** ≥ 10 kΩ (digital), ≥ 1 MΩ (analog)
- **Noise Immunity:** ≥ 40 dB common mode rejection
- **Signal Conditioning:** Low-pass filter, Schmitt trigger for digital
- **Sampling Rate:** ≥ 20 kHz
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-SEN-03: Wheel Speed Sensor Power Supply**
- **Description:** The system shall provide regulated power supply to active wheel speed sensors.
- **Supply Voltage:** 12V ± 0.5V
- **Supply Current:** ≤ 50 mA per sensor
- **Short Circuit Protection:** Current limiting at 100 mA
- **Reverse Polarity Protection:** Required
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 3.2 Pressure Sensor Interfaces

**EBS-IR-SEN-04: Brake Pressure Sensor Interface**
- **Description:** The system shall interface with brake pressure sensors in the hydraulic circuit.
- **Signal Type:** Analog voltage (ratiometric)
- **Pressure Range:** 0 to 200 bar
- **Output Range:** 0.5V to 4.5V
- **Supply Voltage:** 5V ± 0.25V
- **Accuracy:** ±1% full scale
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-SEN-05: Pressure Sensor Signal Conditioning**
- **Description:** The system shall provide signal conditioning for pressure sensor inputs.
- **ADC Resolution:** ≥ 12 bits
- **Sampling Rate:** ≥ 1 kHz
- **Input Protection:** ±30V overvoltage protection
- **Filtering:** Anti-aliasing filter, fc = 500 Hz
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

### 3.3 Inertial Sensor Interfaces

**EBS-IR-SEN-06: Yaw Rate Sensor Interface**
- **Description:** The system shall interface with a yaw rate sensor for vehicle dynamics measurement.
- **Signal Type:** Analog voltage or digital (SPI/I2C)
- **Measurement Range:** ±120°/s
- **Resolution:** ≤ 0.1°/s
- **Supply Voltage:** 5V ± 0.25V or 3.3V ± 0.15V
- **Update Rate:** ≥ 100 Hz
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-SEN-07: Lateral Acceleration Sensor Interface**
- **Description:** The system shall interface with a lateral acceleration sensor.
- **Signal Type:** Analog voltage or digital (SPI/I2C)
- **Measurement Range:** ±2g
- **Resolution:** ≤ 0.01g
- **Bandwidth:** ≥ 50 Hz
- **Temperature Compensation:** Integrated or software-based
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-SEN-08: Steering Angle Sensor Interface**
- **Description:** The system shall receive steering angle information via CAN bus.
- **Data Source:** Steering column sensor via CAN
- **Message Rate:** ≥ 50 Hz
- **Resolution:** ≤ 0.1°
- **Range:** ±720° (multiple turns)
- **Validity Check:** Message counter and checksum
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

## 4. Actuator Interface Requirements

### 4.1 Hydraulic Modulator Interfaces

**EBS-IR-ACT-01: Solenoid Valve Control**
- **Description:** The system shall control hydraulic solenoid valves for brake pressure modulation.
- **Control Type:** PWM control
- **Voltage:** 12V nominal
- **Current:** 0.5A to 2A per valve
- **PWM Frequency:** 100 Hz to 1 kHz
- **Response Time:** ≤ 10 ms
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-ACT-02: Pump Motor Control**
- **Description:** The system shall control the hydraulic pump motor for pressure generation.
- **Control Type:** On/off or PWM speed control
- **Voltage:** 12V nominal
- **Current:** ≤ 20A peak, ≤ 10A continuous
- **Protection:** Overcurrent, thermal protection
- **Feedback:** Motor current monitoring
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-ACT-03: Valve Position Feedback**
- **Description:** The system shall monitor valve position feedback where available.
- **Feedback Type:** Position sensor or current monitoring
- **Resolution:** ≤ 5% of full travel
- **Update Rate:** ≥ 1 kHz
- **Fault Detection:** Position vs. command comparison
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 4.2 Warning and Indication Interfaces

**EBS-IR-ACT-04: Warning Lamp Control**
- **Description:** The system shall control warning lamps to indicate system status.
- **Control Type:** Digital on/off control
- **Voltage:** 12V nominal
- **Current:** ≤ 2A per lamp
- **Protection:** Short circuit and open circuit detection
- **Lamp Types:** ABS, ESC, TCS, general fault
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-ACT-05: Audible Warning Control**
- **Description:** The system shall control audible warning devices when required.
- **Control Type:** Digital on/off or PWM for tone control
- **Voltage:** 12V nominal
- **Current:** ≤ 1A
- **Frequency Range:** 500 Hz to 4 kHz
- **Duration Control:** Programmable on/off patterns
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

## 5. Vehicle Network Communication

### 5.1 CAN Bus Interface Requirements

**EBS-IR-CAN-01: CAN Bus Physical Interface**
- **Description:** The system shall implement CAN 2.0B physical interface.
- **Bus Speed:** 500 kbps (high-speed CAN)
- **Voltage Levels:** CAN_H: 2.5V to 3.5V, CAN_L: 1.5V to 2.5V
- **Termination:** 120Ω termination resistor
- **Isolation:** Galvanic isolation ≥ 1 kV
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-CAN-02: CAN Message Format**
- **Description:** The system shall use standardized CAN message formats.
- **Frame Type:** Extended frame (29-bit identifier)
- **Data Length:** 0 to 8 bytes per message
- **Byte Order:** Motorola (big-endian) format
- **Signal Encoding:** Intel or Motorola byte order as specified
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-CAN-03: CAN Message Timing**
- **Description:** The system shall transmit CAN messages at specified intervals.
- **Periodic Messages:** 10 ms, 20 ms, 100 ms cycles
- **Event-Driven Messages:** ≤ 10 ms response time
- **Message Timeout:** 3x nominal period
- **Bus Load:** ≤ 30% of bus capacity
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 5.2 CAN Message Definitions

**EBS-IR-CAN-04: Vehicle Speed Message**
- **Description:** The system shall broadcast vehicle speed information.
- **Message ID:** 0x1A1 (example)
- **Transmission Rate:** 20 ms
- **Data Content:** Vehicle speed, wheel speeds, validity flags
- **Resolution:** 0.1 km/h
- **Range:** 0 to 655.3 km/h
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-CAN-05: System Status Message**
- **Description:** The system shall broadcast system status and fault information.
- **Message ID:** 0x2A1 (example)
- **Transmission Rate:** 100 ms
- **Data Content:** System state, active functions, fault codes
- **Fault Encoding:** DTC format (ISO 14229)
- **Status Bits:** ABS active, ESC active, TCS active, system fault
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-CAN-06: Brake Request Message**
- **Description:** The system shall receive brake requests from other systems.
- **Message ID:** 0x3A1 (example)
- **Reception Rate:** 20 ms
- **Data Content:** Brake force request, priority level, requesting system ID
- **Arbitration:** Priority-based request handling
- **Timeout Handling:** Default to driver input if timeout
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 5.3 LIN Bus Interface Requirements

**EBS-IR-LIN-01: LIN Bus Physical Interface**
- **Description:** The system shall implement LIN 2.1 interface for sensor communication.
- **Bus Speed:** 19.2 kbps
- **Voltage Levels:** 0V (dominant), 12V (recessive)
- **Pull-up Resistor:** 1 kΩ to 30 kΩ
- **Master/Slave:** EBS ECU as LIN master
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-IR-LIN-02: LIN Message Scheduling**
- **Description:** The system shall implement LIN message scheduling.
- **Schedule Table:** Fixed 20 ms cycle time
- **Slave Response:** ≤ 10 ms response time
- **Error Handling:** Retry mechanism for failed transmissions
- **Sleep/Wake-up:** Support for LIN sleep/wake-up protocol
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

## 6. Diagnostic Interface Requirements

### 6.1 OBD-II Interface

**EBS-IR-DIAG-01: OBD-II Protocol Support**
- **Description:** The system shall support OBD-II diagnostic protocols.
- **Protocols:** ISO 15765 (CAN), ISO 14230 (KWP2000)
- **Baud Rate:** 500 kbps (CAN), 10.4 kbps (K-Line)
- **Service Support:** Services 0x01, 0x02, 0x03, 0x04, 0x07, 0x0A
- **DTC Format:** P0xxx, P2xxx codes for brake system
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-IR-DIAG-02: Diagnostic Data Availability**
- **Description:** The system shall provide diagnostic data via OBD-II interface.
- **Real-time Data:** Wheel speeds, brake pressure, system status
- **Freeze Frame Data:** Conditions when DTC was set
- **Readiness Monitors:** System self-test completion status
- **Data Update Rate:** ≤ 100 ms for real-time data
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

### 6.2 UDS Diagnostic Interface

**EBS-IR-DIAG-03: UDS Protocol Implementation**
- **Description:** The system shall implement UDS (ISO 14229) diagnostic services.
- **Transport Protocol:** ISO 15765-2 (CAN-TP)
- **Session Types:** Default, programming, extended diagnostic
- **Security Access:** Seed/key algorithm for protected services
- **Service Support:** 0x10, 0x11, 0x14, 0x19, 0x22, 0x27, 0x2E, 0x31, 0x34, 0x36, 0x37
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-DIAG-04: Diagnostic Data Identifiers**
- **Description:** The system shall support reading diagnostic data identifiers.
- **System Information:** Part number, software version, calibration ID
- **Live Data:** Sensor values, actuator states, internal variables
- **Statistical Data:** Operating hours, cycle counts, fault statistics
- **Access Control:** Public, protected, and secured data categories
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 7. Power Interface Requirements

### 7.1 Power Supply Interface

**EBS-IR-PWR-01: Main Power Supply**
- **Description:** The system shall operate from the vehicle 12V electrical system.
- **Nominal Voltage:** 12V
- **Operating Range:** 9V to 16V
- **Survival Range:** 6V to 32V (no damage)
- **Reverse Polarity Protection:** Required up to -16V
- **Transient Protection:** ISO 7637-2 pulses
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-IR-PWR-02: Power Consumption Limits**
- **Description:** The system shall limit power consumption within specified ranges.
- **Standby Current:** ≤ 50 mA
- **Normal Operation:** ≤ 15W average
- **Peak Power:** ≤ 100W for ≤ 1 second
- **Inrush Current:** ≤ 50A for ≤ 10 ms
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-PWR-03: Ground Interface**
- **Description:** The system shall implement proper grounding strategy.
- **Ground Types:** Chassis ground, signal ground, power ground
- **Ground Resistance:** ≤ 0.1Ω to chassis
- **Ground Loop Prevention:** Single-point grounding for sensitive circuits
- **EMC Grounding:** RF ground plane for high-frequency circuits
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 7.2 Wake-up and Sleep Interface

**EBS-IR-PWR-04: Wake-up Signal Interface**
- **Description:** The system shall support wake-up from external signals.
- **Wake-up Sources:** Ignition, CAN wake-up, brake pedal switch
- **Wake-up Time:** ≤ 100 ms to operational state
- **Signal Levels:** 0V (inactive), 12V (active)
- **Debounce Time:** 10 ms minimum
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-IR-PWR-05: Sleep Mode Interface**
- **Description:** The system shall enter sleep mode to minimize power consumption.
- **Sleep Trigger:** No activity for 30 minutes after ignition off
- **Sleep Current:** ≤ 5 mA
- **Wake-up Capability:** Maintain wake-up signal monitoring
- **State Preservation:** Critical data saved in non-volatile memory
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

## 8. Human-Machine Interface Requirements

### 8.1 Driver Information Interface

**EBS-IR-HMI-01: Warning Lamp Interface**
- **Description:** The system shall interface with dashboard warning lamps.
- **Lamp Types:** ABS, ESC, TCS, brake system fault
- **Control Method:** Direct control or CAN message
- **Lamp Test:** Self-test during system startup
- **Brightness Control:** Automatic or manual dimming support
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-HMI-02: Display Interface**
- **Description:** The system shall provide information to vehicle displays.
- **Interface Type:** CAN bus messages
- **Information Types:** System status, fault messages, service reminders
- **Message Format:** Standardized display protocol
- **Language Support:** Multiple language capability
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

### 8.2 Driver Control Interface

**EBS-IR-HMI-03: ESC Disable Switch Interface**
- **Description:** The system shall interface with ESC disable switch.
- **Switch Type:** Momentary or maintained contact
- **Signal Level:** 0V (pressed), 12V (released)
- **Debounce Time:** 50 ms
- **Function:** Disable ESC until next ignition cycle
- **Priority:** Low
- **ASIL:** A
- **Verification:** Test

**EBS-IR-HMI-04: Brake Pedal Switch Interface**
- **Description:** The system shall interface with brake pedal position switches.
- **Switch Types:** Brake light switch, brake pedal position sensor
- **Signal Types:** Digital on/off, analog position
- **Redundancy:** Dual switch configuration for safety
- **Response Time:** ≤ 10 ms
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 9. Environmental Interface Requirements

### 9.1 EMC Interface Requirements

**EBS-IR-EMC-01: Electromagnetic Immunity**
- **Description:** The system shall maintain functionality under electromagnetic interference.
- **Standards:** ISO 11452 series, CISPR 25
- **Immunity Levels:** 200 V/m radiated, 150 V conducted
- **Frequency Range:** 10 kHz to 18 GHz
- **Performance Criteria:** No loss of function during and after exposure
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-EMC-02: Electromagnetic Emissions**
- **Description:** The system shall limit electromagnetic emissions.
- **Standards:** CISPR 25 Class 5
- **Frequency Range:** 150 kHz to 1 GHz
- **Measurement Methods:** CISPR 25 ALSE and LISN methods
- **Limits:** Class 5 limits for all frequency bands
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 9.2 Environmental Protection

**EBS-IR-ENV-01: Ingress Protection**
- **Description:** The system shall provide protection against ingress of solids and liquids.
- **Protection Level:** IP67 for ECU housing
- **Test Standards:** IEC 60529
- **Connector Sealing:** IP67 when mated
- **Vent Requirements:** Pressure equalization with moisture protection
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-ENV-02: Vibration Interface**
- **Description:** The system shall maintain functionality under vehicle vibrations.
- **Standards:** ISO 16750-3
- **Frequency Range:** 10 Hz to 2000 Hz
- **Acceleration Levels:** Up to 30g peak
- **Mounting Requirements:** Secure mounting with vibration isolation
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 10. Interface Testing and Validation

### 10.1 Interface Verification Methods

**EBS-IR-TEST-01: Signal Integrity Testing**
- **Description:** All interfaces shall be verified for signal integrity.
- **Test Methods:** Oscilloscope measurement, eye diagram analysis
- **Parameters:** Rise/fall times, overshoot, noise margins
- **Conditions:** Minimum and maximum cable lengths
- **Acceptance Criteria:** Meet interface specification limits
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-IR-TEST-02: Communication Protocol Testing**
- **Description:** Communication interfaces shall be tested for protocol compliance.
- **Test Tools:** Protocol analyzers, conformance test tools
- **Test Cases:** Normal operation, error conditions, boundary cases
- **Standards Compliance:** CAN, LIN, UDS, OBD-II standards
- **Interoperability:** Testing with other vehicle systems
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 10.2 Interface Fault Testing

**EBS-IR-TEST-03: Fault Injection Testing**
- **Description:** Interface fault handling shall be verified through fault injection.
- **Fault Types:** Open circuit, short circuit, signal corruption
- **Response Verification:** Proper fault detection and handling
- **Recovery Testing:** System recovery after fault removal
- **Safety Verification:** No unsafe behavior during faults
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

## 11. Document Control

### 11.1 Revision History
| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2025-07-29 | System Engineer | Initial version |

### 11.2 Approval
| Role | Name | Signature | Date |
|------|------|-----------|------|
| System Engineer | | | |
| Hardware Engineer | | | |
| Software Engineer | | | |
| Test Engineer | | | |

### 11.3 Traceability
This document traces to:
- EBS Item Definition (EBS-ID-001)
- EBS Functional Requirements (EBS-FR-001)
- EBS Electrical Requirements (EBS-EL-001)
- Vehicle Network Architecture Specification