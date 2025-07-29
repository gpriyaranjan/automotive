# EBS Safety Requirements
**Document ID:** EBS-SR-001  
**Version:** 1.0  
**Date:** 2025-07-29  
**Status:** Draft  

## 1. Document Overview

### 1.1 Purpose
This document specifies the safety requirements for the Electronic Braking System (EBS) in accordance with ISO 26262 functional safety standards. It defines safety goals, safety requirements, and safety mechanisms to ensure the system operates safely throughout its lifecycle.

### 1.2 Scope
This document covers:
- Safety goals and ASIL classification
- Functional safety requirements
- Technical safety requirements
- Safety mechanisms and fault handling
- Safe states and degraded operation modes
- Safety validation requirements

### 1.3 Related Documents
- EBS Item Definition (EBS-ID-001)
- EBS Functional Requirements (EBS-FR-001)
- EBS HARA Analysis (EBS-HARA-001)
- ISO 26262 Functional Safety Standard

## 2. Safety Goals and ASIL Classification

### 2.1 Safety Goal Definition

**SG-01: Unintended Braking Prevention**
- **Description:** The EBS system shall not apply unintended braking that could lead to vehicle instability or collision.
- **ASIL:** D
- **Rationale:** Unintended braking can cause loss of vehicle control and rear-end collisions.

**SG-02: Brake Function Availability**
- **Description:** The EBS system shall maintain basic braking functionality even in the presence of single-point failures.
- **ASIL:** D
- **Rationale:** Loss of braking capability directly threatens occupant and road user safety.

**SG-03: Stability Control Integrity**
- **Description:** The EBS system shall not provide incorrect stability control interventions that could destabilize the vehicle.
- **ASIL:** D
- **Rationale:** Incorrect ESC intervention can cause loss of vehicle control.

**SG-04: System State Awareness**
- **Description:** The EBS system shall correctly inform the driver of system status and any safety-relevant failures.
- **ASIL:** C
- **Rationale:** Driver must be aware of system limitations to take appropriate action.

### 2.2 ASIL Decomposition

**High-Level ASIL D Functions:**
- Brake pressure control and modulation
- Wheel lockup prevention (ABS core function)
- Vehicle stability control (ESC core function)
- Safety-critical fault detection

**ASIL C Functions:**
- Traction control system
- Brake force distribution
- System status monitoring
- Driver warning systems

**ASIL B Functions:**
- Advanced comfort functions
- Hill hold control
- Non-critical diagnostics

## 3. Functional Safety Requirements

### 3.1 Safe State Definition

**EBS-SR-SS-01: Primary Safe State**
- **Description:** The primary safe state shall be conventional braking with EBS functions disabled and driver warning active.
- **ASIL:** D
- **Rationale:** Maintains basic braking capability while alerting driver.
- **Verification:** Test

**EBS-SR-SS-02: Secondary Safe State**
- **Description:** If conventional braking is not available, the secondary safe state shall be controlled system shutdown with maximum warning to driver.
- **ASIL:** D
- **Rationale:** Prevents dangerous system behavior when repair is required.
- **Verification:** Test

**EBS-SR-SS-03: Safe State Transition Time**
- **Description:** The system shall transition to safe state within 100ms of detecting a safety-critical fault.
- **ASIL:** D
- **Rationale:** Minimize exposure time to hazardous conditions.
- **Verification:** Test

### 3.2 Fault Detection and Handling

**EBS-SR-FD-01: Single Point Fault Detection**
- **Description:** The system shall detect all single-point faults that could lead to violation of safety goals within one driving cycle.
- **ASIL:** D
- **Rationale:** Early fault detection prevents safety goal violations.
- **Verification:** Test, Analysis

**EBS-SR-FD-02: Latent Fault Detection**
- **Description:** The system shall detect latent faults with a diagnostic coverage of at least 99% for ASIL D functions.
- **ASIL:** D
- **Rationale:** Prevent accumulation of undetected faults.
- **Verification:** Analysis

**EBS-SR-FD-03: Fault Reaction Time**
- **Description:** The system shall react to detected safety-critical faults within 50ms.
- **ASIL:** D
- **Rationale:** Rapid fault response minimizes hazard exposure.
- **Verification:** Test

**EBS-SR-FD-04: Fault Memory**
- **Description:** The system shall store safety-relevant fault information in non-volatile memory with error detection and correction.
- **ASIL:** C
- **Rationale:** Ensure fault information survives power cycles for service.
- **Verification:** Test

### 3.3 Redundancy and Diversity

**EBS-SR-RED-01: Sensor Redundancy**
- **Description:** Critical sensor inputs shall be provided through diverse and redundant sensing methods where feasible.
- **ASIL:** D
- **Rationale:** Prevent single sensor failures from causing safety goal violations.
- **Verification:** Analysis, Test

**EBS-SR-RED-02: Processing Redundancy**
- **Description:** Safety-critical calculations shall be performed using diverse algorithms or redundant processing paths.
- **ASIL:** D
- **Rationale:** Detect systematic faults in software algorithms.
- **Verification:** Analysis, Test

**EBS-SR-RED-03: Actuator Monitoring**
- **Description:** All safety-critical actuators shall have independent monitoring to verify correct operation.
- **ASIL:** D
- **Rationale:** Detect actuator failures that could cause safety goal violations.
- **Verification:** Test

## 4. Technical Safety Requirements

### 4.1 Hardware Safety Requirements

**EBS-SR-HW-01: Hardware Fault Tolerance**
- **Description:** The hardware architecture shall tolerate single-point hardware failures without violating safety goals.
- **ASIL:** D
- **Rationale:** Prevent hardware failures from causing hazardous situations.
- **Verification:** Analysis, Test

**EBS-SR-HW-02: Hardware Diagnostic Coverage**
- **Description:** Hardware diagnostics shall achieve at least 99% diagnostic coverage for safety-critical functions.
- **ASIL:** D
- **Rationale:** Detect hardware faults before they cause safety goal violations.
- **Verification:** Analysis

**EBS-SR-HW-03: Memory Protection**
- **Description:** Safety-critical software shall be protected from corruption by non-safety software through memory protection mechanisms.
- **ASIL:** D
- **Rationale:** Prevent interference between safety and non-safety functions.
- **Verification:** Test

**EBS-SR-HW-04: Watchdog Monitoring**
- **Description:** An independent watchdog shall monitor the main processor and force safe state if malfunction is detected.
- **ASIL:** D
- **Rationale:** Detect processor failures and ensure safe state transition.
- **Verification:** Test

### 4.2 Software Safety Requirements

**EBS-SR-SW-01: Software Partitioning**
- **Description:** Safety-critical software functions shall be partitioned from non-safety functions with defined interfaces.
- **ASIL:** D
- **Rationale:** Prevent interference between safety and non-safety software.
- **Verification:** Analysis, Review

**EBS-SR-SW-02: Control Flow Monitoring**
- **Description:** Safety-critical software shall implement control flow monitoring to detect software execution errors.
- **ASIL:** D
- **Rationale:** Detect software execution faults that could cause safety goal violations.
- **Verification:** Test

**EBS-SR-SW-03: Data Integrity Protection**
- **Description:** Safety-critical data shall be protected by checksums, signatures, or other integrity protection mechanisms.
- **ASIL:** D
- **Rationale:** Detect data corruption that could cause incorrect system behavior.
- **Verification:** Test

**EBS-SR-SW-04: Timing Monitoring**
- **Description:** Safety-critical software tasks shall be monitored for timing violations with appropriate fault responses.
- **ASIL:** D
- **Rationale:** Ensure real-time requirements are met for safety functions.
- **Verification:** Test

### 4.3 Communication Safety Requirements

**EBS-SR-COM-01: Message Authentication**
- **Description:** Safety-critical CAN messages shall include authentication mechanisms to detect corruption or unauthorized messages.
- **ASIL:** C
- **Rationale:** Prevent incorrect data from causing safety goal violations.
- **Verification:** Test

**EBS-SR-COM-02: Message Timeout Detection**
- **Description:** The system shall detect missing or delayed safety-critical messages and react appropriately.
- **ASIL:** D
- **Rationale:** Ensure system operates safely when communication fails.
- **Verification:** Test

**EBS-SR-COM-03: Message Sequence Monitoring**
- **Description:** Safety-critical message sequences shall be monitored for correct order and timing.
- **ASIL:** C
- **Rationale:** Detect communication errors that could cause incorrect system behavior.
- **Verification:** Test

## 5. Safety Mechanisms

### 5.1 Monitoring and Supervision

**EBS-SR-MON-01: Sensor Plausibility Checking**
- **Description:** All sensor inputs shall be checked for plausibility against physical limits and cross-checked with other sensors.
- **ASIL:** D
- **Rationale:** Detect sensor failures and prevent use of invalid data.
- **Verification:** Test

**EBS-SR-MON-02: Actuator Response Monitoring**
- **Description:** All actuator commands shall be verified through independent feedback monitoring.
- **ASIL:** D
- **Rationale:** Ensure actuators respond correctly to commands.
- **Verification:** Test

**EBS-SR-MON-03: System Health Monitoring**
- **Description:** The system shall continuously monitor its own health and performance against defined thresholds.
- **ASIL:** D
- **Rationale:** Detect degradation before it leads to safety goal violations.
- **Verification:** Test

### 5.2 Fault Injection and Testing

**EBS-SR-FI-01: Built-in Test Functions**
- **Description:** The system shall include built-in test functions to verify correct operation of safety mechanisms.
- **ASIL:** D
- **Rationale:** Ensure safety mechanisms remain functional throughout system life.
- **Verification:** Test

**EBS-SR-FI-02: Periodic Self-Test**
- **Description:** Safety-critical functions shall perform periodic self-tests to verify correct operation.
- **ASIL:** D
- **Rationale:** Detect latent faults in safety mechanisms.
- **Verification:** Test

## 6. Degraded Operation Modes

### 6.1 Fault-Tolerant Operation

**EBS-SR-DEG-01: Graceful Degradation**
- **Description:** The system shall continue to provide reduced functionality when non-critical components fail.
- **ASIL:** C
- **Rationale:** Maintain maximum available functionality while ensuring safety.
- **Verification:** Test

**EBS-SR-DEG-02: Function Prioritization**
- **Description:** When resources are limited due to faults, safety-critical functions shall have priority over comfort functions.
- **ASIL:** D
- **Rationale:** Ensure safety functions remain available when system is degraded.
- **Verification:** Test

**EBS-SR-DEG-03: Driver Notification**
- **Description:** The system shall clearly inform the driver when operating in degraded mode and what functions are affected.
- **ASIL:** C
- **Rationale:** Enable driver to adapt behavior to system limitations.
- **Verification:** Test

### 6.2 Emergency Operation

**EBS-SR-EMG-01: Emergency Brake Function**
- **Description:** Basic brake function shall remain available even when EBS control functions fail.
- **ASIL:** D
- **Rationale:** Maintain minimum braking capability for vehicle safety.
- **Verification:** Test

**EBS-SR-EMG-02: Fail-Safe Valve Operation**
- **Description:** Hydraulic valves shall fail to positions that maintain basic braking capability.
- **ASIL:** D
- **Rationale:** Ensure brake system remains functional after valve failures.
- **Verification:** Test

## 7. Safety Validation Requirements

### 7.1 Safety Case Development

**EBS-SR-VAL-01: Safety Case Documentation**
- **Description:** A comprehensive safety case shall be developed demonstrating that safety goals are achieved.
- **ASIL:** D
- **Rationale:** Provide evidence that system meets safety requirements.
- **Verification:** Review

**EBS-SR-VAL-02: Hazard Analysis Validation**
- **Description:** The hazard analysis shall be validated through testing and analysis to confirm completeness and accuracy.
- **ASIL:** D
- **Rationale:** Ensure all relevant hazards have been identified and addressed.
- **Verification:** Analysis, Test

### 7.2 Safety Testing

**EBS-SR-TST-01: Fault Injection Testing**
- **Description:** Safety mechanisms shall be validated through systematic fault injection testing.
- **ASIL:** D
- **Rationale:** Verify that safety mechanisms detect and handle faults correctly.
- **Verification:** Test

**EBS-SR-TST-02: Boundary Condition Testing**
- **Description:** System behavior at operational boundaries shall be tested to verify safe operation.
- **ASIL:** D
- **Rationale:** Ensure system remains safe at limits of operation.
- **Verification:** Test

**EBS-SR-TST-03: Environmental Stress Testing**
- **Description:** Safety functions shall be validated under environmental stress conditions.
- **ASIL:** D
- **Rationale:** Ensure safety is maintained under adverse conditions.
- **Verification:** Test

## 8. Safety Lifecycle Requirements

### 8.1 Development Process

**EBS-SR-DEV-01: Safety Development Process**
- **Description:** System development shall follow ISO 26262 safety development processes appropriate for ASIL D.
- **ASIL:** D
- **Rationale:** Ensure systematic approach to safety throughout development.
- **Verification:** Review

**EBS-SR-DEV-02: Safety Reviews**
- **Description:** Safety reviews shall be conducted at each development phase with independent safety assessment.
- **ASIL:** D
- **Rationale:** Verify safety requirements are correctly implemented.
- **Verification:** Review

### 8.2 Configuration Management

**EBS-SR-CFG-01: Safety Configuration Management**
- **Description:** All safety-relevant items shall be under strict configuration management with traceability.
- **ASIL:** D
- **Rationale:** Ensure safety integrity is maintained throughout lifecycle.
- **Verification:** Review

**EBS-SR-CFG-02: Change Impact Analysis**
- **Description:** All changes to safety-relevant items shall undergo safety impact analysis.
- **ASIL:** D
- **Rationale:** Prevent changes from introducing new hazards.
- **Verification:** Analysis, Review

## 9. Production and Service Requirements

### 9.1 Production Safety

**EBS-SR-PROD-01: Production Testing**
- **Description:** Each produced unit shall undergo safety-relevant testing to verify correct operation.
- **ASIL:** D
- **Rationale:** Ensure production units meet safety requirements.
- **Verification:** Test

**EBS-SR-PROD-02: Calibration Verification**
- **Description:** Safety-critical calibration parameters shall be verified during production.
- **ASIL:** D
- **Rationale:** Ensure system operates safely with production variations.
- **Verification:** Test

### 9.2 Service and Maintenance

**EBS-SR-SRV-01: Service Diagnostics**
- **Description:** Service tools shall be able to verify correct operation of all safety functions.
- **ASIL:** C
- **Rationale:** Enable verification of safety after service.
- **Verification:** Test

**EBS-SR-SRV-02: Safety-Critical Component Identification**
- **Description:** Safety-critical components shall be clearly identified for service personnel.
- **ASIL:** C
- **Rationale:** Prevent incorrect service procedures that could affect safety.
- **Verification:** Review

## 10. Document Control

### 10.1 Revision History
| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2025-07-29 | Safety Engineer | Initial version |

### 10.2 Approval
| Role | Name | Signature | Date |
|------|------|-----------|------|
| Safety Engineer | | | |
| System Engineer | | | |
| Safety Manager | | | |
| Project Manager | | | |

### 10.3 Traceability
This document traces to:
- EBS Item Definition (EBS-ID-001)
- EBS Functional Requirements (EBS-FR-001)
- EBS HARA Analysis (EBS-HARA-001)
- ISO 26262 Standard Requirements