# EBS Hazard Analysis and Risk Assessment (HARA)
**Document ID:** EBS-HARA-001  
**Version:** 1.0  
**Date:** 2025-07-29  
**Status:** Draft  

## 1. Document Overview

### 1.1 Purpose
This document presents the Hazard Analysis and Risk Assessment (HARA) for the Electronic Braking System (EBS) in accordance with ISO 26262 functional safety standards. It identifies potential hazards, analyzes their causes and effects, and determines the required Automotive Safety Integrity Level (ASIL) for safety measures.

### 1.2 Scope
This HARA covers:
- Identification of hazardous events related to EBS malfunction
- Analysis of severity, exposure, and controllability for each hazard
- ASIL determination for identified hazards
- Safety goals derivation from hazard analysis
- Risk evaluation and acceptance criteria
- Hazard mitigation strategies

### 1.3 Related Documents
- EBS Item Definition (EBS-ID-001)
- EBS Safety Requirements (EBS-SR-001)
- EBS Functional Requirements (EBS-FR-001)
- ISO 26262 Functional Safety Standard
- Vehicle Hazard Analysis

## 2. HARA Methodology

### 2.1 HARA Process Overview
The HARA follows the ISO 26262 methodology:
1. **Item Definition:** Define the EBS system and its operational environment
2. **Hazard Identification:** Identify potential hazardous events
3. **Situation Analysis:** Analyze operational situations and driving scenarios
4. **Severity Classification:** Classify potential harm severity (S0-S3)
5. **Exposure Classification:** Classify probability of operational situations (E0-E4)
6. **Controllability Classification:** Classify controllability by driver (C0-C3)
7. **ASIL Determination:** Determine ASIL based on S, E, C classification
8. **Safety Goal Definition:** Define safety goals to address hazards

### 2.2 Classification Criteria

#### 2.2.1 Severity Classification (S)
- **S0:** No injuries - No impact on safety
- **S1:** Light to moderate injuries - Mild to moderate injuries
- **S2:** Severe to life-threatening injuries - Severe injuries, survival probable
- **S3:** Life-threatening to fatal injuries - Life-threatening to fatal injuries

#### 2.2.2 Exposure Classification (E)
- **E0:** Very low probability - Very unlikely to encounter
- **E1:** Low probability - Unlikely to encounter during vehicle lifetime
- **E2:** Medium probability - Likely to encounter a few times during vehicle lifetime
- **E3:** High probability - Likely to encounter sometimes during average trip
- **E4:** Very high probability - Likely to encounter during most trips

#### 2.2.3 Controllability Classification (C)
- **C0:** Controllable in general - Most drivers can act to avoid harm
- **C1:** Simply controllable - Most drivers can act to avoid harm with simple actions
- **C2:** Normally controllable - Most drivers can act to avoid harm with corrective action
- **C3:** Difficult to control or uncontrollable - Few drivers can act to avoid harm

### 2.3 ASIL Determination Matrix

| S\E×C | E4C1 | E4C2 | E4C3 | E3C1 | E3C2 | E3C3 | E2C1 | E2C2 | E2C3 | E1C1 | E1C2 | E1C3 |
|-------|------|------|------|------|------|------|------|------|------|------|------|------|
| **S1** | A | A | B | A | A | B | QM | A | A | QM | QM | A |
| **S2** | B | C | D | B | C | D | A | B | C | QM | A | B |
| **S3** | C | D | D | C | D | D | B | C | D | A | B | C |

## 3. System Definition and Operational Context

### 3.1 EBS System Definition
The Electronic Braking System (EBS) provides:
- Anti-lock Braking System (ABS) functionality
- Electronic Stability Control (ESC) functionality  
- Traction Control System (TCS) functionality
- Brake force distribution and optimization
- Integration with vehicle safety and control systems

### 3.2 Operational Environment
- **Vehicle Types:** Passenger cars (M1) and light commercial vehicles (N1)
- **Operating Conditions:** All weather conditions, various road surfaces
- **Speed Range:** 0-250 km/h vehicle speeds
- **Driver Population:** General driving population with varying skill levels
- **Traffic Conditions:** Urban, rural, and highway driving scenarios

### 3.3 System Boundaries
- **Included:** EBS ECU, sensors, actuators, hydraulic modulator, software
- **Excluded:** Brake pedal, master cylinder, brake calipers, vehicle chassis
- **Interfaces:** Vehicle CAN network, power supply, hydraulic brake system

## 4. Hazard Identification and Analysis

### 4.1 Hazard H-01: Unintended Braking

**Hazard Description:** EBS applies braking force when not intended by driver

#### 4.1.1 Hazardous Event
Unintended brake application during normal driving conditions

#### 4.1.2 Potential Causes
- ECU software malfunction
- Sensor false signals (brake pedal, wheel speed)
- Actuator malfunction (stuck valve, pump activation)
- Communication errors from other systems
- Power supply transients causing false activation

#### 4.1.3 Operational Situations
- **Situation 1:** Highway driving at high speed
  - **Severity:** S3 (Life-threatening) - Sudden braking at high speed can cause loss of control, rear-end collision
  - **Exposure:** E3 (High) - Highway driving is common
  - **Controllability:** C3 (Difficult to control) - Unexpected braking difficult to counteract
  - **ASIL:** D

- **Situation 2:** Urban driving at moderate speed
  - **Severity:** S2 (Severe) - Sudden braking can cause rear-end collision, injury likely
  - **Exposure:** E4 (Very high) - Urban driving very common
  - **Controllability:** C2 (Normally controllable) - Driver can react at lower speeds
  - **ASIL:** D

- **Situation 3:** Parking maneuvers at low speed
  - **Severity:** S1 (Light) - Low speed reduces injury severity
  - **Exposure:** E4 (Very high) - Parking is very common
  - **Controllability:** C1 (Simply controllable) - Easy to control at low speed
  - **ASIL:** A

#### 4.1.4 Safety Goal SG-01
The EBS system shall not apply unintended braking that could lead to vehicle instability or collision.
- **ASIL:** D (highest from situations above)

### 4.2 Hazard H-02: Loss of Braking Function

**Hazard Description:** EBS fails to provide adequate braking when requested by driver

#### 4.2.1 Hazardous Event
Insufficient or no braking response to driver brake pedal input

#### 4.2.2 Potential Causes
- ECU failure (hardware or software)
- Actuator failure (pump, valves)
- Sensor failure (brake pedal, wheel speed)
- Power supply failure
- Hydraulic system failure
- Communication system failure

#### 4.2.3 Operational Situations
- **Situation 1:** Emergency braking at high speed
  - **Severity:** S3 (Life-threatening) - Inability to brake can cause fatal collision
  - **Exposure:** E2 (Medium) - Emergency situations occur occasionally
  - **Controllability:** C3 (Difficult to control) - Limited alternatives to braking
  - **ASIL:** D

- **Situation 2:** Normal braking in traffic
  - **Severity:** S3 (Life-threatening) - Rear-end collision likely, potentially fatal
  - **Exposure:** E4 (Very high) - Traffic braking very common
  - **Controllability:** C3 (Difficult to control) - No immediate alternative
  - **ASIL:** D

- **Situation 3:** Gradual braking for traffic control
  - **Severity:** S2 (Severe) - Collision likely but may be less severe
  - **Exposure:** E4 (Very high) - Very common driving situation
  - **Controllability:** C2 (Normally controllable) - Driver may have time to react
  - **ASIL:** D

#### 4.2.4 Safety Goal SG-02
The EBS system shall maintain basic braking functionality even in the presence of single-point failures.
- **ASIL:** D

### 4.3 Hazard H-03: Incorrect ABS Function

**Hazard Description:** ABS system operates incorrectly during braking events

#### 4.3.1 Hazardous Event
ABS fails to prevent wheel lockup or operates when not needed

#### 4.3.2 Potential Causes
- Wheel speed sensor failure or incorrect signals
- ABS algorithm malfunction
- Hydraulic modulator valve failure
- ECU processing errors
- Incorrect calibration parameters

#### 4.3.3 Operational Situations
- **Situation 1:** Emergency braking on dry road
  - **Severity:** S2 (Severe) - Wheel lockup increases stopping distance, loss of steering
  - **Exposure:** E2 (Medium) - Emergency braking occurs occasionally
  - **Controllability:** C2 (Normally controllable) - Driver can release and reapply brakes
  - **ASIL:** C

- **Situation 2:** Braking on slippery surface
  - **Severity:** S3 (Life-threatening) - Wheel lockup on ice/snow can cause loss of control
  - **Exposure:** E3 (High) - Common in winter conditions
  - **Controllability:** C3 (Difficult to control) - Limited control on slippery surface
  - **ASIL:** D

- **Situation 3:** Normal braking in urban environment
  - **Severity:** S2 (Severe) - Increased stopping distance can cause collision
  - **Exposure:** E4 (Very high) - Urban braking very common
  - **Controllability:** C2 (Normally controllable) - Driver can adapt braking
  - **ASIL:** D

#### 4.3.4 Safety Goal SG-03
The ABS system shall prevent wheel lockup during braking while maintaining vehicle steerability and stability.
- **ASIL:** D

### 4.4 Hazard H-04: Incorrect ESC Function

**Hazard Description:** ESC system provides incorrect stability control intervention

#### 4.4.1 Hazardous Event
ESC fails to intervene when needed or intervenes incorrectly

#### 4.4.2 Potential Causes
- Yaw rate sensor failure
- Lateral acceleration sensor failure
- Steering angle sensor failure
- ESC algorithm malfunction
- Brake actuator failure during ESC intervention

#### 4.4.3 Operational Situations
- **Situation 1:** Oversteer condition at high speed
  - **Severity:** S3 (Life-threatening) - Loss of control can cause fatal accident
  - **Exposure:** E2 (Medium) - Oversteer situations occur occasionally
  - **Controllability:** C3 (Difficult to control) - Oversteer difficult for most drivers
  - **ASIL:** D

- **Situation 2:** Understeer condition in curve
  - **Severity:** S3 (Life-threatening) - Vehicle may leave roadway
  - **Exposure:** E2 (Medium) - Understeer in curves occurs occasionally
  - **Controllability:** C2 (Normally controllable) - Driver can reduce speed
  - **ASIL:** C

- **Situation 3:** Lane change maneuver
  - **Severity:** S2 (Severe) - Incorrect ESC can cause instability
  - **Exposure:** E4 (Very high) - Lane changes very common
  - **Controllability:** C2 (Normally controllable) - Driver can correct steering
  - **ASIL:** D

#### 4.4.4 Safety Goal SG-04
The ESC system shall not provide incorrect stability control interventions that could destabilize the vehicle.
- **ASIL:** D

### 4.5 Hazard H-05: Incorrect TCS Function

**Hazard Description:** TCS system operates incorrectly during acceleration

#### 4.5.1 Hazardous Event
TCS fails to control wheel spin or intervenes when not needed

#### 4.5.2 Potential Causes
- Wheel speed sensor failure
- TCS algorithm malfunction
- Brake actuator failure during TCS intervention
- Engine torque coordination failure

#### 4.5.3 Operational Situations
- **Situation 1:** Acceleration on slippery surface
  - **Severity:** S2 (Severe) - Excessive wheel spin can cause loss of control
  - **Exposure:** E3 (High) - Common in winter/wet conditions
  - **Controllability:** C2 (Normally controllable) - Driver can reduce throttle
  - **ASIL:** C

- **Situation 2:** Acceleration during cornering
  - **Severity:** S3 (Life-threatening) - Wheel spin in corner can cause spin-out
  - **Exposure:** E3 (High) - Cornering acceleration common
  - **Controllability:** C3 (Difficult to control) - Spin-out difficult to recover
  - **ASIL:** D

- **Situation 3:** Normal acceleration from stop
  - **Severity:** S1 (Light) - Wheel spin from stop less dangerous
  - **Exposure:** E4 (Very high) - Acceleration from stop very common
  - **Controllability:** C1 (Simply controllable) - Easy to control at low speed
  - **ASIL:** A

#### 4.5.4 Safety Goal SG-05
The TCS system shall prevent excessive wheel spin during acceleration without causing vehicle instability.
- **ASIL:** D

### 4.6 Hazard H-06: System Status Misrepresentation

**Hazard Description:** EBS system provides incorrect status information to driver

#### 4.6.1 Hazardous Event
Driver receives incorrect information about EBS system status or faults

#### 4.6.2 Potential Causes
- Communication failure to instrument cluster
- Warning lamp failure
- Diagnostic system malfunction
- Display system failure

#### 4.6.3 Operational Situations
- **Situation 1:** System fault not indicated to driver
  - **Severity:** S3 (Life-threatening) - Driver unaware of safety system failure
  - **Exposure:** E2 (Medium) - System faults occur occasionally
  - **Controllability:** C3 (Difficult to control) - Driver cannot compensate for unknown fault
  - **ASIL:** D

- **Situation 2:** False fault indication
  - **Severity:** S1 (Light) - May cause unnecessary service, driver distraction
  - **Exposure:** E1 (Low) - False indications should be rare
  - **Controllability:** C1 (Simply controllable) - Driver can continue driving
  - **ASIL:** A

#### 4.6.4 Safety Goal SG-06
The EBS system shall correctly inform the driver of system status and any safety-relevant failures.
- **ASIL:** D

## 5. Risk Evaluation and ASIL Summary

### 5.1 ASIL Summary Table

| Hazard | Safety Goal | ASIL | Rationale |
|--------|-------------|------|-----------|
| H-01 | SG-01: Unintended Braking Prevention | D | High severity and exposure, difficult to control |
| H-02 | SG-02: Brake Function Availability | D | Life-threatening consequences, high exposure |
| H-03 | SG-03: ABS Function Integrity | D | Critical for vehicle control, high exposure |
| H-04 | SG-04: ESC Function Integrity | D | Critical for stability, life-threatening consequences |
| H-05 | SG-05: TCS Function Integrity | D | Can cause loss of control, high exposure |
| H-06 | SG-06: System Status Awareness | D | Driver must know system status for safety |

### 5.2 Risk Acceptance Criteria
All identified hazards require ASIL D safety measures due to:
- Life-threatening potential consequences
- High exposure in normal driving conditions
- Limited controllability by average drivers
- Critical importance of braking system for vehicle safety

### 5.3 Residual Risk Assessment
After implementation of safety measures:
- Residual risk shall be reduced to acceptable levels
- Remaining risks shall be clearly communicated to users
- Regular risk reassessment required during system lifecycle

## 6. Safety Goals and Requirements Allocation

### 6.1 Safety Goal SG-01: Unintended Braking Prevention
**ASIL D Requirements:**
- Redundant brake request validation
- Plausibility checking of all brake-related inputs
- Independent monitoring of brake actuator commands
- Safe state transition upon detection of unintended braking

### 6.2 Safety Goal SG-02: Brake Function Availability  
**ASIL D Requirements:**
- Fault-tolerant system architecture
- Redundant brake pressure generation capability
- Independent monitoring of brake system performance
- Graceful degradation to basic braking function

### 6.3 Safety Goal SG-03: ABS Function Integrity
**ASIL D Requirements:**
- Redundant wheel speed sensing
- Independent ABS algorithm validation
- Hydraulic system integrity monitoring
- Fallback to conventional braking if ABS fails

### 6.4 Safety Goal SG-04: ESC Function Integrity
**ASIL D Requirements:**
- Redundant vehicle dynamics sensing
- Independent ESC algorithm validation
- Cross-checking of stability control interventions
- Safe state transition if ESC malfunction detected

### 6.5 Safety Goal SG-05: TCS Function Integrity
**ASIL D Requirements:**
- Redundant wheel speed monitoring for TCS
- Independent validation of TCS interventions
- Coordination with engine management system
- Safe disabling of TCS if malfunction detected

### 6.6 Safety Goal SG-06: System Status Awareness
**ASIL D Requirements:**
- Redundant warning system architecture
- Independent monitoring of warning system function
- Fail-safe warning activation upon system faults
- Clear indication of system operational status

## 7. Hazard Mitigation Strategies

### 7.1 Design-Based Mitigation
- **Redundancy:** Implement redundant sensors, processors, and actuators
- **Diversity:** Use diverse technologies and algorithms for critical functions
- **Fail-Safe Design:** Design system to fail to safe state
- **Fault Tolerance:** Implement fault-tolerant architectures

### 7.2 Verification-Based Mitigation
- **Comprehensive Testing:** Extensive testing of all hazardous scenarios
- **Fault Injection:** Systematic fault injection testing
- **Formal Verification:** Mathematical verification of critical algorithms
- **Independent Assessment:** Independent safety assessment

### 7.3 Process-Based Mitigation
- **Safety Lifecycle:** Follow ISO 26262 safety development lifecycle
- **Configuration Management:** Strict configuration control
- **Change Management:** Controlled change management process
- **Competence Management:** Ensure adequate safety competence

### 7.4 Operational Mitigation
- **Driver Training:** Educate drivers on system capabilities and limitations
- **Maintenance:** Regular maintenance and inspection procedures
- **Service Support:** Proper service and repair procedures
- **Monitoring:** Continuous monitoring of field performance

## 8. HARA Validation and Review

### 8.1 HARA Validation Requirements
- **Completeness:** Verify all relevant hazards identified
- **Accuracy:** Validate severity, exposure, and controllability assessments
- **Consistency:** Ensure consistent application of classification criteria
- **Traceability:** Maintain traceability from hazards to safety requirements

### 8.2 HARA Review Process
- **Internal Review:** Multi-disciplinary internal review team
- **Independent Review:** Independent safety expert review
- **Customer Review:** Review with vehicle manufacturer
- **Regulatory Review:** Review with regulatory authorities if required

### 8.3 HARA Maintenance
- **Regular Updates:** Regular review and update of HARA
- **Change Impact:** Assess impact of design changes on HARA
- **Field Experience:** Incorporate field experience and lessons learned
- **Technology Updates:** Update for new technologies and threats

## 9. Assumptions and Limitations

### 9.1 HARA Assumptions
- Driver is alert and capable of normal driving tasks
- Vehicle is properly maintained according to specifications
- EBS system is properly installed and calibrated
- Operating environment is within specified limits
- Other vehicle systems function as intended

### 9.2 HARA Limitations
- Analysis based on current understanding of system and environment
- Cannot predict all possible failure modes and scenarios
- Effectiveness depends on proper implementation of safety measures
- Requires regular review and update as system evolves

### 9.3 Exclusions
- Hazards due to misuse or abuse of system
- Hazards due to improper maintenance or service
- Hazards due to modification of system
- Hazards outside the defined operational environment

## 10. Document Control

### 10.1 Revision History
| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2025-07-29 | Safety Engineer | Initial HARA analysis |

### 10.2 Approval
| Role | Name | Signature | Date |
|------|------|-----------|------|
| Safety Engineer | | | |
| System Engineer | | | |
| Chief Engineer | | | |
| Safety Manager | | | |

### 10.3 Traceability
This document traces to:
- EBS Item Definition (EBS-ID-001)
- EBS Safety Requirements (EBS-SR-001)
- EBS Functional Requirements (EBS-FR-001)
- ISO 26262 Functional Safety Standard
- Vehicle-Level HARA Analysis