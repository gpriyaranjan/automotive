# Electronic Power Steering (EPS) Hazard Analysis and Risk Assessment (HARA)

## 1. Introduction

### 1.1 Purpose
This document presents the Hazard Analysis and Risk Assessment (HARA) for the Electronic Power Steering (EPS) system in accordance with ISO 26262-3. The HARA identifies potential hazards, analyzes associated risks, and determines safety goals with corresponding Automotive Safety Integrity Levels (ASILs).

### 1.2 Scope
This HARA covers the EPS system as defined in the Item Definition, including all functions that could potentially lead to hazardous events during vehicle operation.

### 1.3 Methodology
The HARA follows the ISO 26262-3 methodology:
1. Define item functions and malfunctions
2. Identify operational situations
3. Determine hazardous events
4. Assess Severity (S), Exposure (E), and Controllability (C)
5. Determine ASIL ratings
6. Formulate safety goals

## 2. EPS System Functions and Malfunctions

### 2.1 Primary Functions

#### 2.1.1 Steering Assistance Function
**Function**: Provide electric motor assistance to reduce driver steering effort

**Potential Malfunctions**:
- **M1**: Loss of steering assistance
- **M2**: Excessive steering assistance
- **M3**: Insufficient steering assistance
- **M4**: Unintended steering assistance
- **M5**: Oscillating/unstable assistance
- **M6**: Assistance in wrong direction

#### 2.1.2 Torque Sensing Function
**Function**: Measure and interpret driver steering input torque

**Potential Malfunctions**:
- **M7**: Loss of torque signal
- **M8**: Incorrect torque measurement
- **M9**: Noisy/unstable torque signal
- **M10**: Torque sensor offset drift

#### 2.1.3 Position Sensing Function
**Function**: Measure steering wheel angle and motor position

**Potential Malfunctions**:
- **M11**: Loss of position signal
- **M12**: Incorrect position measurement
- **M13**: Position sensor drift

### 2.2 Secondary Functions

#### 2.2.1 Speed-Sensitive Steering
**Function**: Adjust assistance based on vehicle speed

**Potential Malfunctions**:
- **M14**: Incorrect speed-based assistance
- **M15**: Loss of speed signal processing

#### 2.2.2 Return-to-Center Function
**Function**: Assist steering wheel return to center

**Potential Malfunctions**:
- **M16**: Excessive return-to-center force
- **M17**: Insufficient return-to-center force
- **M18**: Return-to-center in wrong direction

## 3. Operational Situations

### 3.1 Driving Scenarios

**OS1**: **Urban Driving**
- Speed: 0-50 km/h
- Frequent steering inputs
- Parking maneuvers
- Traffic congestion

**OS2**: **Highway Driving**
- Speed: 80-130 km/h
- Straight line driving
- Lane changes
- Overtaking maneuvers

**OS3**: **Rural/Country Roads**
- Speed: 50-100 km/h
- Curved roads
- Variable road conditions
- Limited visibility

**OS4**: **Parking/Low Speed Maneuvering**
- Speed: 0-10 km/h
- Full lock steering
- Tight spaces
- Frequent direction changes

**OS5**: **Emergency Situations**
- Sudden obstacle avoidance
- Emergency braking with steering
- Loss of vehicle control scenarios
- Adverse weather conditions

### 3.2 Environmental Conditions

**EC1**: **Normal Weather**
- Dry road surface
- Good visibility
- Normal temperature

**EC2**: **Adverse Weather**
- Wet/icy road surface
- Reduced visibility
- Extreme temperatures

**EC3**: **Road Conditions**
- Smooth asphalt
- Rough/uneven surfaces
- Gravel roads
- Construction zones

## 4. Hazardous Events Analysis

### 4.1 Hazardous Event 1: Unintended Self-Steering

**Malfunction**: M4 - Unintended steering assistance
**Operational Situation**: OS2 - Highway driving
**Hazardous Event**: Vehicle steers unintentionally while driving at high speed

**Effect**: Vehicle deviates from intended path, potential collision with other vehicles or roadside obstacles

**Risk Assessment**:
- **Severity (S3)**: Life-threatening injuries (survival uncertain), fatal injuries
- **Exposure (E4)**: High probability - highway driving is common
- **Controllability (C3)**: Difficult to control - unexpected steering at high speed

**ASIL Determination**: S3 + E4 + C3 = **ASIL D**

**Safety Goal SG-01**: "Unintended self-steering shall be prevented"

### 4.2 Hazardous Event 2: Loss of Steering Capability

**Malfunction**: M1 - Loss of steering assistance + mechanical binding
**Operational Situation**: OS4 - Parking/Low speed maneuvering
**Hazardous Event**: Complete loss of steering capability during parking

**Effect**: Unable to steer vehicle, potential collision with obstacles or pedestrians

**Risk Assessment**:
- **Severity (S2)**: Severe and life-threatening injuries (survival probable)
- **Exposure (E3)**: Medium probability - parking situations are frequent
- **Controllability (C3)**: Difficult to control - no steering capability

**ASIL Determination**: S2 + E3 + C3 = **ASIL C**

**Safety Goal SG-02**: "Loss of steering capability shall be prevented"

### 4.3 Hazardous Event 3: Excessive Steering Assistance

**Malfunction**: M2 - Excessive steering assistance
**Operational Situation**: OS1 - Urban driving
**Hazardous Event**: Over-assistance causes vehicle to oversteer during normal steering input

**Effect**: Vehicle path deviates more than intended, potential collision

**Risk Assessment**:
- **Severity (S2)**: Severe and life-threatening injuries (survival probable)
- **Exposure (E4)**: High probability - urban driving is very common
- **Controllability (C2)**: Normally controllable - driver can compensate

**ASIL Determination**: S2 + E4 + C2 = **ASIL B**

**Safety Goal SG-03**: "Excessive steering assistance shall be prevented"

### 4.4 Hazardous Event 4: Oscillating Steering Assistance

**Malfunction**: M5 - Oscillating/unstable assistance
**Operational Situation**: OS2 - Highway driving
**Hazardous Event**: Steering wheel oscillates uncontrollably at highway speeds

**Effect**: Driver loses control of vehicle, potential for severe accident

**Risk Assessment**:
- **Severity (S3)**: Life-threatening injuries (survival uncertain), fatal injuries
- **Exposure (E3)**: Medium probability - highway driving with specific conditions
- **Controllability (C3)**: Difficult to control - oscillations are hard to counteract

**ASIL Determination**: S3 + E3 + C3 = **ASIL D**

**Safety Goal SG-04**: "Oscillating steering assistance shall be prevented"

### 4.5 Hazardous Event 5: Delayed Steering Response

**Malfunction**: M3 - Insufficient steering assistance + system lag
**Operational Situation**: OS5 - Emergency situations
**Hazardous Event**: Delayed or insufficient steering response during emergency avoidance

**Effect**: Unable to avoid obstacle, collision occurs

**Risk Assessment**:
- **Severity (S3)**: Life-threatening injuries (survival uncertain), fatal injuries
- **Exposure (E2)**: Low probability - emergency situations are infrequent
- **Controllability (C3)**: Difficult to control - emergency situations require immediate response

**ASIL Determination**: S3 + E2 + C3 = **ASIL C**

**Safety Goal SG-05**: "Adequate steering response shall be maintained during emergency situations"

### 4.6 Hazardous Event 6: Wrong Direction Assistance

**Malfunction**: M6 - Assistance in wrong direction
**Operational Situation**: OS3 - Rural/Country roads
**Hazardous Event**: EPS provides assistance opposite to driver input on curved road

**Effect**: Vehicle steers away from intended path, potential roadway departure

**Risk Assessment**:
- **Severity (S3)**: Life-threatening injuries (survival uncertain), fatal injuries
- **Exposure (E2)**: Low probability - specific fault condition
- **Controllability (C3)**: Difficult to control - counterintuitive system behavior

**ASIL Determination**: S3 + E2 + C3 = **ASIL C**

**Safety Goal SG-06**: "Steering assistance shall be provided in the correct direction"

### 4.7 Hazardous Event 7: Sudden Loss of Assistance

**Malfunction**: M1 - Loss of steering assistance (sudden)
**Operational Situation**: OS2 - Highway driving
**Hazardous Event**: Sudden complete loss of power steering assistance at highway speed

**Effect**: Sudden increase in steering effort, potential loss of vehicle control

**Risk Assessment**:
- **Severity (S2)**: Severe and life-threatening injuries (survival probable)
- **Exposure (E3)**: Medium probability - highway driving is common
- **Controllability (C2)**: Normally controllable - driver can adapt to manual steering

**ASIL Determination**: S2 + E3 + C2 = **ASIL B**

**Safety Goal SG-07**: "Sudden loss of steering assistance shall be prevented"

### 4.8 Hazardous Event 8: Excessive Return-to-Center Force

**Malfunction**: M16 - Excessive return-to-center force
**Operational Situation**: OS1 - Urban driving
**Hazardous Event**: Strong return-to-center force interferes with intended steering

**Effect**: Difficulty maintaining intended steering angle, potential path deviation

**Risk Assessment**:
- **Severity (S1)**: Light and moderate injuries
- **Exposure (E4)**: High probability - urban driving is very common
- **Controllability (C1)**: Simply controllable - driver can overcome the force

**ASIL Determination**: S1 + E4 + C1 = **QM (Quality Managed)**

**Safety Goal SG-08**: "Excessive return-to-center force shall be limited"

## 5. HARA Summary Table

| Hazardous Event | Malfunction | Op. Situation | Severity | Exposure | Controllability | ASIL | Safety Goal |
|-----------------|-------------|---------------|----------|----------|-----------------|------|-------------|
| HE-01: Unintended self-steering | M4 | OS2 | S3 | E4 | C3 | **D** | SG-01 |
| HE-02: Loss of steering capability | M1 | OS4 | S2 | E3 | C3 | **C** | SG-02 |
| HE-03: Excessive steering assistance | M2 | OS1 | S2 | E4 | C2 | **B** | SG-03 |
| HE-04: Oscillating steering assistance | M5 | OS2 | S3 | E3 | C3 | **D** | SG-04 |
| HE-05: Delayed steering response | M3 | OS5 | S3 | E2 | C3 | **C** | SG-05 |
| HE-06: Wrong direction assistance | M6 | OS3 | S3 | E2 | C3 | **C** | SG-06 |
| HE-07: Sudden loss of assistance | M1 | OS2 | S2 | E3 | C2 | **B** | SG-07 |
| HE-08: Excessive return-to-center | M16 | OS1 | S1 | E4 | C1 | **QM** | SG-08 |

## 6. Safety Goals

### 6.1 ASIL D Safety Goals

**SG-01**: "Unintended self-steering shall be prevented"
- **ASIL**: D
- **Safe State**: Manual steering capability maintained
- **Fault Tolerance Time**: <100ms

**SG-04**: "Oscillating steering assistance shall be prevented"
- **ASIL**: D
- **Safe State**: Stable assistance or manual steering
- **Fault Tolerance Time**: <200ms

### 6.2 ASIL C Safety Goals

**SG-02**: "Loss of steering capability shall be prevented"
- **ASIL**: C
- **Safe State**: Manual steering capability maintained
- **Fault Tolerance Time**: <500ms

**SG-05**: "Adequate steering response shall be maintained during emergency situations"
- **ASIL**: C
- **Safe State**: Sufficient steering response available
- **Fault Tolerance Time**: <100ms

**SG-06**: "Steering assistance shall be provided in the correct direction"
- **ASIL**: C
- **Safe State**: No assistance or manual steering
- **Fault Tolerance Time**: <100ms

### 6.3 ASIL B Safety Goals

**SG-03**: "Excessive steering assistance shall be prevented"
- **ASIL**: B
- **Safe State**: Limited or no assistance
- **Fault Tolerance Time**: <200ms

**SG-07**: "Sudden loss of steering assistance shall be prevented"
- **ASIL**: B
- **Safe State**: Gradual reduction of assistance
- **Fault Tolerance Time**: <1000ms

### 6.4 QM Safety Goals

**SG-08**: "Excessive return-to-center force shall be limited"
- **ASIL**: QM
- **Safe State**: Reduced or no return-to-center assistance
- **Fault Tolerance Time**: <2000ms

## 7. Assumptions and Dependencies

### 7.1 Vehicle System Assumptions
- Manual steering capability is always maintained through mechanical connection
- Driver is alert and capable of responding to system warnings
- Vehicle speed information is available and accurate
- Basic vehicle systems (brakes, suspension) are functioning normally

### 7.2 Driver Assumptions
- Driver has normal physical capabilities and reaction times
- Driver is properly trained in vehicle operation
- Driver will respond appropriately to warning signals
- Driver maintains hands on steering wheel during normal operation

### 7.3 Environmental Assumptions
- Road conditions are within normal operating parameters
- Weather conditions do not exceed system design limits
- Vehicle is operated within design speed limits
- Maintenance is performed according to schedule

## 8. HARA Validation

### 8.1 Review Process
This HARA has been developed through:
- Multi-disciplinary team review (safety, systems, design engineers)
- Comparison with industry best practices and standards
- Analysis of field data and accident statistics
- Expert judgment and experience

### 8.2 Confirmation Measures
- **Independent Review**: Safety assessment by independent safety assessor
- **Peer Review**: Review by experienced HARA practitioners
- **Stakeholder Review**: Review by OEM customer and regulatory bodies
- **Update Process**: Regular updates based on new information and experience

## 9. Document Control

### 9.1 Document Information
- **Document ID**: EPS-HARA-001
- **Version**: 1.0
- **Status**: Draft
- **Classification**: Confidential

### 9.2 Approval
- **Safety Manager**: [Signature Required]
- **Chief Engineer**: [Signature Required]
- **Program Manager**: [Signature Required]
- **Date**: [Date Required]

### 9.3 Change Control
All changes to this HARA shall be subject to change control process with safety impact assessment and appropriate approvals.

## 10. References

- ISO 26262-1:2018 - Road vehicles — Functional safety — Part 1: Vocabulary
- ISO 26262-3:2018 - Road vehicles — Functional safety — Part 3: Concept phase
- EPS Item Definition Document (EPS-ITEM-DEF-001)
- EPS Functional Requirements Document (EPS-FR-001)
- Industry accident data and field experience reports