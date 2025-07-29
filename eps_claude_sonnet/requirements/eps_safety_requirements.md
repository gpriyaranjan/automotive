# Electronic Power Steering (EPS) Safety Requirements

## 1. Introduction

### 1.1 Purpose
This document defines the safety requirements for the Electronic Power Steering (EPS) system derived from the Hazard Analysis and Risk Assessment (HARA). These requirements specify the safety mechanisms and measures needed to achieve the determined Automotive Safety Integrity Levels (ASILs).

### 1.2 Scope
This document covers all safety requirements for the EPS system, including:
- Safety goals derived from HARA
- Technical safety requirements
- Safety mechanisms and measures
- ASIL decomposition strategies
- Verification and validation requirements

### 1.3 Safety Requirements Notation
- **SHALL**: Mandatory safety requirement
- **SHOULD**: Recommended safety requirement
- **REQ-ID**: Unique requirement identifier format: EPS-SR-XXX
- **ASIL**: Associated Automotive Safety Integrity Level

## 2. Safety Goals and Technical Safety Requirements

### 2.1 ASIL D Safety Requirements

#### 2.1.1 Safety Goal SG-01: Unintended Self-Steering Prevention (ASIL D)

**EPS-SR-001** [ASIL D]: The EPS system SHALL prevent unintended steering torque that could cause vehicle path deviation greater than 0.5m within 2 seconds.

**EPS-SR-002** [ASIL D]: The EPS system SHALL detect unintended steering assistance within 100ms of occurrence.

**EPS-SR-003** [ASIL D]: The EPS system SHALL transition to a safe state within 100ms when unintended steering is detected.

**EPS-SR-004** [ASIL D]: The EPS system SHALL implement dual-channel monitoring of motor torque commands with diverse algorithms.

**EPS-SR-005** [ASIL D]: The EPS system SHALL limit maximum motor torque to prevent uncontrollable steering forces.

#### 2.1.2 Safety Goal SG-04: Oscillating Steering Assistance Prevention (ASIL D)

**EPS-SR-006** [ASIL D]: The EPS system SHALL prevent steering oscillations with frequency >0.5Hz and amplitude >2Nm.

**EPS-SR-007** [ASIL D]: The EPS system SHALL monitor steering system stability using frequency domain analysis.

**EPS-SR-008** [ASIL D]: The EPS system SHALL implement active damping to prevent oscillations.

**EPS-SR-009** [ASIL D]: The EPS system SHALL disable assistance when unstable oscillations are detected within 200ms.

### 2.2 ASIL C Safety Requirements

#### 2.2.1 Safety Goal SG-02: Loss of Steering Capability Prevention (ASIL C)

**EPS-SR-010** [ASIL C]: The EPS system SHALL maintain manual steering capability at all times through mechanical connection.

**EPS-SR-011** [ASIL C]: The EPS system SHALL detect motor seizure or mechanical binding within 500ms.

**EPS-SR-012** [ASIL C]: The EPS system SHALL implement motor disconnect mechanism for mechanical failures.

**EPS-SR-013** [ASIL C]: The EPS system SHALL monitor steering system friction and detect abnormal increases.

#### 2.2.2 Safety Goal SG-05: Adequate Steering Response (ASIL C)

**EPS-SR-014** [ASIL C]: The EPS system SHALL provide minimum assistance torque of 2Nm when driver input exceeds 5Nm.

**EPS-SR-015** [ASIL C]: The EPS system SHALL respond to driver input within 100ms during emergency situations.

**EPS-SR-016** [ASIL C]: The EPS system SHALL maintain assistance capability down to 9V supply voltage.

**EPS-SR-017** [ASIL C]: The EPS system SHALL implement redundant power supply paths for critical functions.

#### 2.2.3 Safety Goal SG-06: Correct Direction Assistance (ASIL C)

**EPS-SR-018** [ASIL C]: The EPS system SHALL verify assistance direction matches driver input direction.

**EPS-SR-019** [ASIL C]: The EPS system SHALL implement dual-channel torque sensing with cross-checking.

**EPS-SR-020** [ASIL C]: The EPS system SHALL disable assistance when direction mismatch is detected within 100ms.

### 2.3 ASIL B Safety Requirements

#### 2.3.1 Safety Goal SG-03: Excessive Steering Assistance Prevention (ASIL B)

**EPS-SR-021** [ASIL B]: The EPS system SHALL limit assistance torque to maximum 8Nm under all conditions.

**EPS-SR-022** [ASIL B]: The EPS system SHALL implement torque limiting with independent monitoring.

**EPS-SR-023** [ASIL B]: The EPS system SHALL reduce assistance when excessive torque is detected within 200ms.

#### 2.3.2 Safety Goal SG-07: Sudden Loss of Assistance Prevention (ASIL B)

**EPS-SR-024** [ASIL B]: The EPS system SHALL implement gradual assistance reduction over minimum 1000ms.

**EPS-SR-025** [ASIL B]: The EPS system SHALL provide driver warning before assistance reduction.

**EPS-SR-026** [ASIL B]: The EPS system SHALL maintain partial assistance during degraded operation.

### 2.4 QM Safety Requirements

#### 2.4.1 Safety Goal SG-08: Excessive Return-to-Center Force Limitation (QM)

**EPS-SR-027** [QM]: The EPS system SHALL limit return-to-center torque to maximum 3Nm.

**EPS-SR-028** [QM]: The EPS system SHALL disable return-to-center function when excessive force is detected.

## 3. Safety Mechanisms and Measures

### 3.1 Hardware Safety Mechanisms

#### 3.1.1 Redundant Sensing (ASIL D)

**EPS-SR-029** [ASIL D]: The EPS system SHALL implement dual-channel torque sensing with diverse technologies.

**EPS-SR-030** [ASIL D]: The EPS system SHALL implement dual-channel position sensing for motor and steering wheel.

**EPS-SR-031** [ASIL D]: The EPS system SHALL cross-check sensor signals and detect discrepancies within 50ms.

#### 3.1.2 Motor Control Safety (ASIL D)

**EPS-SR-032** [ASIL D]: The EPS system SHALL implement dual-channel motor control with independent processors.

**EPS-SR-033** [ASIL D]: The EPS system SHALL monitor motor current with independent measurement circuits.

**EPS-SR-034** [ASIL D]: The EPS system SHALL implement hardware-based motor disconnect capability.

#### 3.1.3 Power Supply Monitoring (ASIL C)

**EPS-SR-035** [ASIL C]: The EPS system SHALL monitor supply voltage with independent circuits.

**EPS-SR-036** [ASIL C]: The EPS system SHALL implement undervoltage and overvoltage protection.

**EPS-SR-037** [ASIL C]: The EPS system SHALL provide power supply redundancy for critical functions.

### 3.2 Software Safety Mechanisms

#### 3.2.1 Software Architecture (ASIL D)

**EPS-SR-038** [ASIL D]: The EPS system SHALL implement software partitioning between safety and non-safety functions.

**EPS-SR-039** [ASIL D]: The EPS system SHALL use memory protection to prevent corruption of safety-critical data.

**EPS-SR-040** [ASIL D]: The EPS system SHALL implement diverse software channels for critical calculations.

#### 3.2.2 Runtime Monitoring (ASIL D)

**EPS-SR-041** [ASIL D]: The EPS system SHALL implement watchdog monitoring with independent timer.

**EPS-SR-042** [ASIL D]: The EPS system SHALL perform runtime checks on critical variables and calculations.

**EPS-SR-043** [ASIL D]: The EPS system SHALL implement control flow monitoring for safety-critical functions.

#### 3.2.3 Data Integrity (ASIL C)

**EPS-SR-044** [ASIL C]: The EPS system SHALL implement checksums for safety-critical data.

**EPS-SR-045** [ASIL C]: The EPS system SHALL verify data integrity before use in safety functions.

**EPS-SR-046** [ASIL C]: The EPS system SHALL implement error correction for critical parameters.

### 3.3 System-Level Safety Mechanisms

#### 3.3.1 Fault Detection and Diagnosis (ASIL D)

**EPS-SR-047** [ASIL D]: The EPS system SHALL detect all single-point faults within specified fault detection time.

**EPS-SR-048** [ASIL D]: The EPS system SHALL achieve >99% diagnostic coverage for safety-critical functions.

**EPS-SR-049** [ASIL D]: The EPS system SHALL classify faults by severity and respond appropriately.

#### 3.3.2 Fault Reaction and Safe State (ASIL D)

**EPS-SR-050** [ASIL D]: The EPS system SHALL transition to safe state within fault tolerance time for each hazard.

**EPS-SR-051** [ASIL D]: The EPS system SHALL maintain manual steering capability in all safe states.

**EPS-SR-052** [ASIL D]: The EPS system SHALL provide appropriate driver warnings for each fault condition.

#### 3.3.3 Fault Tolerance (ASIL C)

**EPS-SR-053** [ASIL C]: The EPS system SHALL continue operation with single sensor failures.

**EPS-SR-054** [ASIL C]: The EPS system SHALL provide degraded functionality with non-critical component failures.

**EPS-SR-055** [ASIL C]: The EPS system SHALL implement graceful degradation strategies.

## 4. ASIL Decomposition

### 4.1 ASIL D Decomposition Strategy

**EPS-SR-056**: ASIL D requirements MAY be decomposed into:
- ASIL B(D) + ASIL B(D) with independence
- ASIL C(D) + ASIL A(D) with independence
- QM(D) + ASIL D with sufficient independence

### 4.2 Independence Requirements

**EPS-SR-057**: Decomposed elements SHALL demonstrate sufficient independence through:
- Separate development teams
- Diverse technologies or algorithms
- Independent verification and validation
- Separate failure modes

### 4.3 Decomposition Examples

**EPS-SR-058**: Torque sensing function (ASIL D) SHALL be decomposed into:
- Primary torque sensor (ASIL B(D))
- Secondary torque sensor with diverse technology (ASIL B(D))

**EPS-SR-059**: Motor control function (ASIL D) SHALL be decomposed into:
- Primary control processor (ASIL C(D))
- Independent monitoring processor (ASIL A(D))

## 5. Safety Validation Requirements

### 5.1 Hardware Validation

**EPS-SR-060** [ASIL D]: Hardware components SHALL be validated according to ISO 26262-5 requirements.

**EPS-SR-061** [ASIL D]: Hardware safety analysis SHALL include FMEA, FTA, and DFA.

**EPS-SR-062** [ASIL D]: Hardware metrics SHALL meet target values for SPFM and LFM.

### 5.2 Software Validation

**EPS-SR-063** [ASIL D]: Software SHALL be developed according to ISO 26262-6 requirements.

**EPS-SR-064** [ASIL D]: Software safety analysis SHALL include software FMEA and fault injection testing.

**EPS-SR-065** [ASIL D]: Software verification SHALL achieve MC/DC coverage for safety-critical code.

### 5.3 System Validation

**EPS-SR-066** [ASIL D]: System integration SHALL be validated according to ISO 26262-4 requirements.

**EPS-SR-067** [ASIL D]: Safety validation SHALL include fault injection testing at system level.

**EPS-SR-068** [ASIL D]: Field testing SHALL validate safety mechanisms under real-world conditions.

## 6. Safety Metrics and Targets

### 6.1 Hardware Metrics

**EPS-SR-069**: Single Point Fault Metric (SPFM) SHALL be ≥99% for ASIL D functions.

**EPS-SR-070**: Latent Fault Metric (LFM) SHALL be ≥90% for ASIL D functions.

**EPS-SR-071**: Probabilistic Metric for Hardware Failures (PMHF) SHALL be <10 FIT for ASIL D.

### 6.2 Software Metrics

**EPS-SR-072**: Structural coverage SHALL achieve MC/DC for ASIL D software.

**EPS-SR-073**: Functional coverage SHALL achieve 100% for safety-critical functions.

**EPS-SR-074**: Software complexity metrics SHALL meet ASIL D targets.

### 6.3 System Metrics

**EPS-SR-075**: Fault detection time SHALL meet specified targets for each hazard.

**EPS-SR-076**: Fault tolerance time SHALL meet specified targets for each hazard.

**EPS-SR-077**: System availability SHALL be >99.9% during vehicle operation.

## 7. Safety Case Requirements

### 7.1 Safety Case Structure

**EPS-SR-078**: A safety case SHALL be developed demonstrating compliance with all safety requirements.

**EPS-SR-079**: The safety case SHALL include evidence from all development phases.

**EPS-SR-080**: The safety case SHALL address all identified hazards and safety goals.

### 7.2 Evidence Requirements

**EPS-SR-081**: Safety evidence SHALL include verification and validation results.

**EPS-SR-082**: Safety evidence SHALL include safety analysis results and conclusions.

**EPS-SR-083**: Safety evidence SHALL include field experience and lessons learned.

## 8. Functional Safety Management

### 8.1 Safety Lifecycle

**EPS-SR-084**: Development SHALL follow ISO 26262 safety lifecycle processes.

**EPS-SR-085**: Safety activities SHALL be planned and tracked throughout development.

**EPS-SR-086**: Safety reviews SHALL be conducted at each lifecycle phase.

### 8.2 Safety Culture

**EPS-SR-087**: Personnel SHALL be qualified for their safety-related activities.

**EPS-SR-088**: Safety training SHALL be provided to all team members.

**EPS-SR-089**: Safety culture SHALL be promoted throughout the organization.

### 8.3 Configuration Management

**EPS-SR-090**: Safety-related work products SHALL be under configuration management.

**EPS-SR-091**: Changes to safety requirements SHALL follow change control process.

**EPS-SR-092**: Traceability SHALL be maintained between all safety work products.

## 9. Production and Operation

### 9.1 Production Safety

**EPS-SR-093**: Production processes SHALL ensure safety integrity is maintained.

**EPS-SR-094**: Production testing SHALL verify safety mechanisms functionality.

**EPS-SR-095**: Production quality metrics SHALL meet safety targets.

### 9.2 Field Monitoring

**EPS-SR-096**: Field performance SHALL be monitored for safety-related failures.

**EPS-SR-097**: Safety-related field issues SHALL be analyzed and addressed.

**EPS-SR-098**: Lessons learned SHALL be fed back into development process.

## 10. Document Control

### 10.1 Document Information
- **Document ID**: EPS-SR-001
- **Version**: 1.0
- **Status**: Draft
- **Classification**: Confidential

### 10.2 Approval Requirements
- **Functional Safety Manager**: [Signature Required]
- **Chief Safety Engineer**: [Signature Required]
- **Program Manager**: [Signature Required]
- **Independent Safety Assessor**: [Signature Required]

### 10.3 Change Control
All changes to safety requirements SHALL be subject to safety impact assessment and appropriate approvals according to the change control process.

## 11. References

- ISO 26262-1:2018 - Road vehicles — Functional safety — Part 1: Vocabulary
- ISO 26262-3:2018 - Road vehicles — Functional safety — Part 3: Concept phase
- ISO 26262-4:2018 - Road vehicles — Functional safety — Part 4: Product development at the system level
- ISO 26262-5:2018 - Road vehicles — Functional safety — Part 5: Product development at the hardware level
- ISO 26262-6:2018 - Road vehicles — Functional safety — Part 6: Product development at the software level
- EPS HARA Analysis Document (EPS-HARA-001)
- EPS Item Definition Document (EPS-ITEM-DEF-001)
- EPS Functional Requirements Document (EPS-FR-001)