# EBS Functional Requirements
**Document ID:** EBS-FR-001  
**Version:** 1.0  
**Date:** 2025-07-29  
**Status:** Draft  

## 1. Document Overview

### 1.1 Purpose
This document specifies the functional requirements for the Electronic Braking System (EBS), defining what the system shall do under various operating conditions and scenarios.

### 1.2 Scope
This document covers functional requirements for:
- Anti-lock Braking System (ABS)
- Electronic Stability Control (ESC)
- Traction Control System (TCS)
- Brake force distribution and optimization
- System monitoring and diagnostics
- Human-machine interface functions

### 1.3 Related Documents
- EBS Item Definition (EBS-ID-001)
- EBS Safety Requirements (EBS-SR-001)
- EBS Performance Requirements (EBS-PR-001)

## 2. Functional Requirements Structure

### 2.1 Requirement Identification
Requirements are identified using the format: **EBS-FR-XXX-YY**
- EBS: Electronic Braking System
- FR: Functional Requirements
- XXX: Function area (ABS, ESC, TCS, etc.)
- YY: Sequential number

### 2.2 Requirement Attributes
Each requirement includes:
- **ID:** Unique identifier
- **Title:** Brief description
- **Description:** Detailed requirement statement
- **Rationale:** Justification for the requirement
- **Priority:** Critical, High, Medium, Low
- **ASIL:** Safety integrity level (A, B, C, D)
- **Verification Method:** Test, Analysis, Inspection, Review

## 3. Anti-Lock Braking System (ABS) Requirements

### 3.1 ABS Core Functions

**EBS-FR-ABS-01: Wheel Lock Prevention**
- **Description:** The system shall prevent wheel lockup by modulating brake pressure when wheel deceleration exceeds the threshold indicating impending lockup.
- **Rationale:** Maintain vehicle steerability and stability during braking.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ABS-02: Wheel Speed Monitoring**
- **Description:** The system shall continuously monitor wheel speed from all four wheels with a sampling rate of at least 100 Hz.
- **Rationale:** Accurate wheel speed data is essential for ABS function.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ABS-03: Brake Pressure Modulation**
- **Description:** The system shall modulate brake pressure through pressure build-up, hold, and release phases to prevent wheel lockup.
- **Rationale:** Control brake force to maintain optimal slip ratio.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ABS-04: ABS Activation Threshold**
- **Description:** The system shall activate ABS when wheel deceleration exceeds 1.5g or when wheel slip exceeds 15% of optimal slip ratio.
- **Rationale:** Early detection prevents wheel lockup.
- **Priority:** High
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ABS-05: ABS Deactivation**
- **Description:** The system shall deactivate ABS when vehicle speed drops below 5 km/h or when brake pedal is released.
- **Rationale:** ABS not effective at very low speeds.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 3.2 ABS Performance Requirements

**EBS-FR-ABS-06: Response Time**
- **Description:** The system shall initiate brake pressure modulation within 10ms of detecting impending wheel lockup.
- **Rationale:** Fast response prevents wheel lockup.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ABS-07: Pressure Modulation Frequency**
- **Description:** The system shall modulate brake pressure at a frequency between 4-20 Hz depending on road surface conditions.
- **Rationale:** Optimal modulation frequency for different surfaces.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-ABS-08: Stopping Distance Optimization**
- **Description:** The system shall maintain stopping distance within 110% of optimal braking performance on dry surfaces.
- **Rationale:** Minimize stopping distance while preventing lockup.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 4. Electronic Stability Control (ESC) Requirements

### 4.1 ESC Core Functions

**EBS-FR-ESC-01: Vehicle Stability Monitoring**
- **Description:** The system shall continuously monitor vehicle yaw rate, lateral acceleration, and steering angle to detect loss of stability.
- **Rationale:** Early detection of instability enables corrective action.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ESC-02: Understeer Detection**
- **Description:** The system shall detect understeer conditions when actual yaw rate is less than 80% of desired yaw rate for more than 200ms.
- **Rationale:** Identify when front wheels lose grip.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ESC-03: Oversteer Detection**
- **Description:** The system shall detect oversteer conditions when actual yaw rate exceeds desired yaw rate by more than 20% for more than 100ms.
- **Rationale:** Identify when rear wheels lose grip.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ESC-04: Selective Brake Application**
- **Description:** The system shall apply brakes to individual wheels to generate corrective yaw moment and restore vehicle stability.
- **Rationale:** Create stabilizing forces through differential braking.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ESC-05: Engine Torque Reduction Request**
- **Description:** The system shall request engine torque reduction when brake intervention alone is insufficient to restore stability.
- **Rationale:** Reduce driving forces to aid stability control.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 4.2 ESC Performance Requirements

**EBS-FR-ESC-06: ESC Response Time**
- **Description:** The system shall initiate stability control intervention within 50ms of detecting instability.
- **Rationale:** Quick response prevents loss of control.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-ESC-07: Yaw Rate Control Accuracy**
- **Description:** The system shall maintain actual yaw rate within ±10% of desired yaw rate during ESC intervention.
- **Rationale:** Precise control maintains intended vehicle path.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 5. Traction Control System (TCS) Requirements

### 5.1 TCS Core Functions

**EBS-FR-TCS-01: Wheel Spin Detection**
- **Description:** The system shall detect wheel spin when driven wheel speed exceeds non-driven wheel speed by more than 10% or when wheel acceleration exceeds 2g.
- **Rationale:** Identify loss of traction during acceleration.
- **Priority:** Critical
- **ASIL:** C
- **Verification:** Test

**EBS-FR-TCS-02: Brake Application for Traction Control**
- **Description:** The system shall apply brakes to spinning wheels to restore traction and transfer torque to wheels with grip.
- **Rationale:** Prevent wheel spin and maintain vehicle control.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-TCS-03: Engine Torque Reduction for TCS**
- **Description:** The system shall request engine torque reduction when brake intervention is insufficient to control wheel spin.
- **Rationale:** Reduce driving torque to prevent excessive wheel spin.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-TCS-04: TCS Deactivation Conditions**
- **Description:** The system shall deactivate TCS when vehicle speed exceeds 100 km/h or when manually disabled by driver (if permitted).
- **Rationale:** TCS primarily needed at lower speeds and during acceleration.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

## 6. Brake Force Distribution Requirements

### 6.1 Electronic Brake Distribution (EBD)

**EBS-FR-EBD-01: Optimal Brake Force Distribution**
- **Description:** The system shall distribute brake force between front and rear axles to maximize braking efficiency while maintaining stability.
- **Rationale:** Optimize braking performance and prevent rear wheel lockup.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-EBD-02: Load-Dependent Distribution**
- **Description:** The system shall adjust brake force distribution based on vehicle loading conditions detected through suspension sensors or brake pressure analysis.
- **Rationale:** Adapt to changing weight distribution.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-FR-EBD-03: Cornering Brake Control**
- **Description:** The system shall adjust brake force distribution during cornering to maintain vehicle stability and optimal braking performance.
- **Rationale:** Prevent instability during combined braking and cornering.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 7. Advanced Braking Functions

### 7.1 Brake Assist Functions

**EBS-FR-BA-01: Emergency Brake Detection**
- **Description:** The system shall detect emergency braking situations based on brake pedal application rate exceeding 5 bar/s.
- **Rationale:** Identify driver's emergency braking intent.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-BA-02: Brake Assist Activation**
- **Description:** The system shall provide maximum available brake force when emergency braking is detected and pedal force is insufficient.
- **Rationale:** Assist driver in achieving maximum braking performance.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

### 7.2 Hill Hold Control

**EBS-FR-HHC-01: Hill Detection**
- **Description:** The system shall detect hill conditions when vehicle inclination exceeds 5% grade.
- **Rationale:** Identify situations where hill hold is beneficial.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-FR-HHC-02: Brake Hold Function**
- **Description:** The system shall maintain brake pressure for up to 2 seconds after brake pedal release on hills to prevent rollback.
- **Rationale:** Prevent vehicle rollback during hill starts.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

## 8. System Monitoring and Diagnostics

### 8.1 Self-Monitoring Functions

**EBS-FR-MON-01: Continuous Self-Test**
- **Description:** The system shall continuously monitor all sensors, actuators, and internal functions for proper operation.
- **Rationale:** Ensure system integrity and detect faults.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-MON-02: Sensor Plausibility Checks**
- **Description:** The system shall perform plausibility checks on all sensor inputs and detect inconsistent or invalid data.
- **Rationale:** Identify sensor failures or malfunctions.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-MON-03: Actuator Feedback Monitoring**
- **Description:** The system shall monitor actuator responses and detect failures to achieve commanded positions or pressures.
- **Rationale:** Verify actuator functionality.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

### 8.2 Fault Management

**EBS-FR-FLT-01: Fault Detection and Classification**
- **Description:** The system shall detect, classify, and store fault information with timestamps and operating conditions.
- **Rationale:** Enable effective fault diagnosis and repair.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-FLT-02: Degraded Mode Operation**
- **Description:** The system shall continue to provide basic braking functions when non-critical components fail.
- **Rationale:** Maintain essential safety functions during failures.
- **Priority:** Critical
- **ASIL:** D
- **Verification:** Test

**EBS-FR-FLT-03: Fault Warning**
- **Description:** The system shall activate warning indicators when faults are detected that affect system performance.
- **Rationale:** Inform driver of system status.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

## 9. Human-Machine Interface Requirements

### 9.1 Driver Information

**EBS-FR-HMI-01: System Status Indication**
- **Description:** The system shall provide visual indication of system status through dashboard warning lamps.
- **Rationale:** Keep driver informed of system operation.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-HMI-02: ABS Activity Indication**
- **Description:** The system shall provide tactile feedback through brake pedal pulsation during ABS operation.
- **Rationale:** Inform driver that ABS is active.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-FR-HMI-03: ESC Activity Indication**
- **Description:** The system shall provide visual indication when ESC is actively controlling vehicle stability.
- **Rationale:** Inform driver of stability intervention.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

### 9.2 Driver Controls

**EBS-FR-HMI-04: ESC Disable Function**
- **Description:** The system shall allow driver to disable ESC function through a dedicated switch, with automatic re-enable at next ignition cycle.
- **Rationale:** Allow driver control for specific driving situations.
- **Priority:** Low
- **ASIL:** A
- **Verification:** Test

**EBS-FR-HMI-05: TCS Disable Function**
- **Description:** The system shall allow driver to disable TCS function through vehicle menu system or dedicated switch.
- **Rationale:** Allow driver control for specific driving conditions.
- **Priority:** Low
- **ASIL:** A
- **Verification:** Test

## 10. Communication Requirements

### 10.1 Vehicle Network Communication

**EBS-FR-COM-01: CAN Bus Communication**
- **Description:** The system shall communicate with other vehicle systems via CAN bus using standardized protocols.
- **Rationale:** Enable system integration and coordination.
- **Priority:** High
- **ASIL:** C
- **Verification:** Test

**EBS-FR-COM-02: Diagnostic Communication**
- **Description:** The system shall support diagnostic communication protocols (UDS, OBD-II) for service and maintenance.
- **Rationale:** Enable effective service and troubleshooting.
- **Priority:** Medium
- **ASIL:** B
- **Verification:** Test

**EBS-FR-COM-03: Data Broadcasting**
- **Description:** The system shall broadcast vehicle speed, wheel speeds, and system status on CAN bus for other systems.
- **Rationale:** Provide data for other vehicle functions.
- **Priority:** Medium
- **ASIL:** B
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
| Safety Engineer | | | |
| Software Engineer | | | |
| Test Engineer | | | |

### 11.3 Traceability
This document traces to:
- EBS Item Definition (EBS-ID-001)
- EBS Safety Requirements (EBS-SR-001)
- EBS Performance Requirements (EBS-PR-001)
- EBS Test Specification (EBS-TS-001)