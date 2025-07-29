# Electronic Power Steering (EPS) System Requirements Document

## Document Information

- **Document Title**: Electronic Power Steering System Requirements Document
- **Document ID**: EPS-SRD-001
- **Version**: 1.0
- **Status**: Draft
- **Classification**: Internal Use
- **Date**: 2025-07-29

## Executive Summary

This document presents the complete system requirements for the Electronic Power Steering (EPS) system. The EPS system is a safety-critical automotive component that provides steering assistance to the driver through an electric motor-based system, reducing steering effort while maintaining vehicle controllability and road feel.

The requirements have been developed following ISO 26262 functional safety standards and automotive industry best practices. The system has been analyzed for hazards and risks, with appropriate safety goals and ASIL classifications established. The requirements cover all aspects of the system including functional, performance, safety, electrical, interface, diagnostic, environmental, integration, and validation requirements.

## Table of Contents

1. [Introduction](#1-introduction)
2. [System Overview](#2-system-overview)
3. [Requirements Structure](#3-requirements-structure)
4. [System Architecture and Research](#4-system-architecture-and-research)
5. [Item Definition and System Boundaries](#5-item-definition-and-system-boundaries)
6. [Functional Requirements](#6-functional-requirements)
7. [Safety Analysis and Requirements](#7-safety-analysis-and-requirements)
8. [Performance Requirements](#8-performance-requirements)
9. [Electrical and Power Requirements](#9-electrical-and-power-requirements)
10. [Interface Requirements](#10-interface-requirements)
11. [Diagnostic and Monitoring Requirements](#11-diagnostic-and-monitoring-requirements)
12. [Environmental and Durability Requirements](#12-environmental-and-durability-requirements)
13. [System Integration Requirements](#13-system-integration-requirements)
14. [Validation and Verification Requirements](#14-validation-and-verification-requirements)
15. [Requirements Traceability](#15-requirements-traceability)
16. [Compliance and Standards](#16-compliance-and-standards)
17. [Document Control](#17-document-control)

## 1. Introduction

### 1.1 Purpose

This document defines the complete system requirements for the Electronic Power Steering (EPS) system. It serves as the authoritative source for all system requirements and provides the foundation for system design, development, testing, and validation.

### 1.2 Scope

This document covers all aspects of the EPS system requirements including:
- System functionality and performance
- Safety and reliability requirements
- Electrical and power specifications
- Interface and integration requirements
- Environmental and durability specifications
- Diagnostic and monitoring capabilities
- Validation and verification requirements

### 1.3 Audience

This document is intended for:
- System engineers and architects
- Design and development teams
- Safety and reliability engineers
- Test and validation engineers
- Program and project managers
- Customers and regulatory bodies

### 1.4 Document Structure

This master document references and integrates multiple detailed requirements documents, each covering specific aspects of the EPS system. The structure follows a logical progression from system definition through detailed requirements to validation and verification.

## 2. System Overview

### 2.1 System Description

The Electronic Power Steering (EPS) system is a safety-critical automotive component that provides steering assistance to the driver through an electric motor. The system reduces steering effort while maintaining vehicle controllability, road feel, and safety across all driving conditions.

### 2.2 Key System Functions

- **Primary Steering Assistance**: Provide electric motor assistance based on driver input
- **Speed-Sensitive Control**: Adjust assistance based on vehicle speed
- **Return-to-Center**: Assist steering wheel return to center position
- **Safety Monitoring**: Continuous system health monitoring and fault detection
- **Diagnostic Capability**: Comprehensive diagnostic and service support functions

### 2.3 System Benefits

- Improved fuel efficiency compared to hydraulic power steering
- Enhanced steering feel and responsiveness
- Reduced maintenance requirements
- Advanced diagnostic capabilities
- Integration with vehicle electronic systems
- Support for advanced driver assistance systems

## 3. Requirements Structure

### 3.1 Requirements Hierarchy

The EPS system requirements are organized in a hierarchical structure:

```
EPS System Requirements
├── System Architecture and Research
├── Item Definition and Boundaries
├── Functional Requirements
├── Safety Analysis and Requirements
│   ├── HARA Analysis
│   └── Safety Requirements (ASIL A-D)
├── Performance Requirements
├── Electrical and Power Requirements
├── Interface Requirements
├── Diagnostic and Monitoring Requirements
├── Environmental and Durability Requirements
├── System Integration Requirements
└── Validation and Verification Requirements
```

### 3.2 Requirements Identification

Each requirement is uniquely identified using the following format:
- **EPS-XXX-NNN**: Where XXX is the requirement category and NNN is the sequential number
- Categories include: FR (Functional), SR (Safety), PR (Performance), ER (Electrical), IR (Interface), DR (Diagnostic), EDR (Environmental/Durability), SIR (System Integration), VVR (Validation/Verification)

### 3.3 Requirements Attributes

Each requirement includes the following attributes:
- Unique identifier
- Requirement statement
- Rationale and source
- Verification method
- Validation approach
- Priority and criticality
- Traceability links

## 4. System Architecture and Research

### 4.1 Reference Document
**Document**: [`eps_system_research.md`](eps_system_research.md)

### 4.2 Key Content
This document provides comprehensive research and analysis of EPS system architecture including:
- EPS system overview and types (C-EPS, P-EPS, R-EPS)
- Main system components (ECU, motor, sensors, power electronics)
- System interfaces and integration aspects
- Key performance characteristics
- Safety considerations and failure modes
- Environmental requirements overview
- Regulatory standards and compliance
- Technology trends and future developments

### 4.3 Architecture Decisions
Based on the research, key architectural decisions include:
- Brushless DC motor with field-oriented control
- Dual-channel torque sensing for safety
- CAN bus communication with vehicle systems
- AUTOSAR-compliant software architecture
- ISO 26262 functional safety compliance

## 5. Item Definition and System Boundaries

### 5.1 Reference Document
**Document**: [`eps_item_definition.md`](eps_item_definition.md)

### 5.2 Key Content
This document defines the EPS system boundaries and interfaces according to ISO 26262 requirements:
- Item overview and classification
- Physical and functional boundaries
- System interfaces (electrical, mechanical, software)
- Operational environment and conditions
- Performance requirements overview
- Assumptions and dependencies
- Success criteria and constraints

### 5.3 System Boundaries
The EPS item includes:
- **Included**: ECU, motor, sensors, power electronics, wiring harness, software
- **Excluded**: Steering wheel, mechanical steering components, vehicle power supply, other vehicle ECUs

## 6. Functional Requirements

### 6.1 Reference Document
**Document**: [`eps_functional_requirements.md`](eps_functional_requirements.md)

### 6.2 Key Content
This document defines all functional requirements for the EPS system including:
- Primary steering functions (assistance, torque sensing, motor control)
- Speed-sensitive steering functionality
- Return-to-center and damping functions
- System operating modes (normal, degraded, fail-safe, sleep)
- Communication functions (CAN, diagnostic)
- Safety functions (fault detection, fault response, redundancy)
- Driver monitoring and calibration functions

### 6.3 Requirements Summary
- **Total Functional Requirements**: 105 requirements (EPS-FR-001 to EPS-FR-105)
- **Primary Functions**: 25 requirements
- **Secondary Functions**: 30 requirements
- **Safety Functions**: 25 requirements
- **Support Functions**: 25 requirements

## 7. Safety Analysis and Requirements

### 7.1 HARA Analysis
**Reference Document**: [`eps_hara_analysis.md`](eps_hara_analysis.md)

#### 7.1.1 Key Hazardous Events
The HARA identified 8 key hazardous events with ASIL classifications:
- **ASIL D**: Unintended self-steering, Oscillating steering assistance
- **ASIL C**: Loss of steering capability, Delayed steering response, Wrong direction assistance
- **ASIL B**: Excessive steering assistance, Sudden loss of assistance
- **QM**: Excessive return-to-center force

#### 7.1.2 Safety Goals
Eight safety goals were derived from the HARA:
- SG-01: Unintended self-steering shall be prevented (ASIL D)
- SG-02: Loss of steering capability shall be prevented (ASIL C)
- SG-03: Excessive steering assistance shall be prevented (ASIL B)
- SG-04: Oscillating steering assistance shall be prevented (ASIL D)
- SG-05: Adequate steering response shall be maintained (ASIL C)
- SG-06: Steering assistance shall be provided in correct direction (ASIL C)
- SG-07: Sudden loss of steering assistance shall be prevented (ASIL B)
- SG-08: Excessive return-to-center force shall be limited (QM)

### 7.2 Safety Requirements
**Reference Document**: [`eps_safety_requirements.md`](eps_safety_requirements.md)

#### 7.2.1 Safety Requirements Summary
- **Total Safety Requirements**: 98 requirements (EPS-SR-001 to EPS-SR-098)
- **ASIL D Requirements**: 20 requirements
- **ASIL C Requirements**: 25 requirements
- **ASIL B Requirements**: 15 requirements
- **QM Requirements**: 5 requirements
- **General Safety Requirements**: 33 requirements

#### 7.2.2 Key Safety Mechanisms
- Dual-channel torque sensing with cross-checking
- Independent motor control monitoring
- Hardware-based motor disconnect capability
- Redundant power supply paths
- Comprehensive fault detection and diagnosis
- Safe state management and transitions

## 8. Performance Requirements

### 8.1 Reference Document
**Document**: [`eps_performance_requirements.md`](eps_performance_requirements.md)

### 8.2 Key Performance Specifications
- **Assistance Torque Range**: 0 to 8 Nm with ±5% accuracy
- **System Response Time**: <50ms (10-90% rise time)
- **Torque Sensor Accuracy**: ±2% of full scale
- **Steering Angle Accuracy**: ±1° resolution
- **Power Consumption**: 150W continuous, 300W peak
- **System Efficiency**: >80% at rated load
- **Operating Temperature**: -40°C to +85°C
- **Service Life**: 15 years, 300,000 km minimum

### 8.3 Requirements Summary
- **Total Performance Requirements**: 128 requirements (EPS-PR-001 to EPS-PR-128)
- **Torque Performance**: 25 requirements
- **Dynamic Performance**: 30 requirements
- **Efficiency and Power**: 20 requirements
- **Environmental Performance**: 25 requirements
- **Reliability and Durability**: 28 requirements

## 9. Electrical and Power Requirements

### 9.1 Reference Document
**Document**: [`eps_electrical_power_requirements.md`](eps_electrical_power_requirements.md)

### 9.2 Key Electrical Specifications
- **Supply Voltage**: 12V nominal (9V-16V operating range)
- **Power Consumption**: 150W continuous, 300W peak
- **Motor Drive**: Three-phase inverter, >20 kHz switching
- **Protection**: Reverse polarity, overcurrent, overvoltage
- **EMC Compliance**: CISPR 25 automotive standards
- **Grounding**: Star grounding architecture, <10mΩ resistance

### 9.3 Requirements Summary
- **Total Electrical Requirements**: 151 requirements (EPS-ER-001 to EPS-ER-151)
- **Power Supply**: 35 requirements
- **Motor Drive**: 25 requirements
- **Protection and Safety**: 30 requirements
- **EMC and Grounding**: 25 requirements
- **Testing and Validation**: 36 requirements

## 10. Interface Requirements

### 10.1 Reference Document
**Document**: [`eps_interface_requirements.md`](eps_interface_requirements.md)

### 10.2 Key Interface Specifications
- **CAN Communication**: CAN 2.0B, 250/500 kbps
- **LIN Communication**: LIN 2.1, 19.2 kbps for steering wheel controls
- **Torque Sensor**: Differential analog ±5V, 16-bit ADC
- **Position Sensors**: Digital interfaces with error detection
- **Motor Control**: Three-phase PWM with space vector modulation
- **Diagnostic**: UDS (ISO 14229) and KWP2000 protocols

### 10.3 Requirements Summary
- **Total Interface Requirements**: 174 requirements (EPS-IR-001 to EPS-IR-174)
- **Communication Interfaces**: 45 requirements
- **Sensor Interfaces**: 40 requirements
- **Motor Drive Interfaces**: 25 requirements
- **Mechanical Interfaces**: 30 requirements
- **Software Interfaces**: 34 requirements

## 11. Diagnostic and Monitoring Requirements

### 11.1 Reference Document
**Document**: [`eps_diagnostic_monitoring_requirements.md`](eps_diagnostic_monitoring_requirements.md)

### 11.2 Key Diagnostic Capabilities
- **Continuous Self-Diagnostics**: All safety-critical functions monitored
- **Fault Detection**: >95% coverage with specified detection times
- **Diagnostic Trouble Codes**: ISO/SAE compliant DTC management
- **Real-Time Monitoring**: Performance and health assessment
- **Service Support**: Comprehensive diagnostic and calibration tools
- **Data Logging**: Event logging and performance data collection

### 11.3 Requirements Summary
- **Total Diagnostic Requirements**: 143 requirements (EPS-DR-001 to EPS-DR-143)
- **Self-Diagnostic**: 30 requirements
- **Fault Detection**: 35 requirements
- **DTC Management**: 25 requirements
- **Service Support**: 30 requirements
- **Data Logging**: 23 requirements

## 12. Environmental and Durability Requirements

### 12.1 Reference Document
**Document**: [`eps_environmental_durability_requirements.md`](eps_environmental_durability_requirements.md)

### 12.2 Key Environmental Specifications
- **Operating Temperature**: -40°C to +85°C (ECU), -40°C to +125°C (motor)
- **Storage Temperature**: -50°C to +95°C
- **Humidity**: Up to 95% RH (non-condensing)
- **Vibration**: Per ISO 16750-3 automotive standards
- **EMC**: CISPR 25 immunity and emission requirements
- **Durability**: 15-year service life, 300,000 km operation
- **Reliability**: MTBF >100,000 hours, <10 FIT failure rate

### 12.3 Requirements Summary
- **Total Environmental Requirements**: 163 requirements (EPS-EDR-001 to EPS-EDR-163)
- **Temperature Requirements**: 35 requirements
- **Environmental Protection**: 40 requirements
- **Mechanical Durability**: 30 requirements
- **EMC Requirements**: 25 requirements
- **Reliability and Lifecycle**: 33 requirements

## 13. System Integration Requirements

### 13.1 Reference Document
**Document**: [`eps_system_integration_requirements.md`](eps_system_integration_requirements.md)

### 13.2 Key Integration Aspects
- **Vehicle Integration**: Seamless integration with target vehicle platforms
- **Mechanical Integration**: Rigid connection to steering system with manual backup
- **Electrical Integration**: Compatible with 12V vehicle electrical architecture
- **Communication Integration**: CAN network integration with proper timing
- **Software Integration**: AUTOSAR-compliant architecture
- **Safety Integration**: Coordinated with vehicle safety systems
- **Manufacturing Integration**: Optimized for production line integration

### 13.3 Requirements Summary
- **Total Integration Requirements**: 180 requirements (EPS-SIR-001 to EPS-SIR-180)
- **Vehicle Integration**: 40 requirements
- **Interface Integration**: 50 requirements
- **Safety Integration**: 30 requirements
- **Manufacturing Integration**: 35 requirements
- **Service Integration**: 25 requirements

## 14. Validation and Verification Requirements

### 14.1 Reference Document
**Document**: [`eps_validation_verification_requirements.md`](eps_validation_verification_requirements.md)

### 14.2 Key V&V Approaches
- **Verification Methods**: Analysis, inspection, testing, demonstration
- **Validation Testing**: Operational environment validation
- **Safety V&V**: ISO 26262 compliant verification and validation
- **Performance Testing**: Comprehensive performance verification
- **Integration Testing**: System and vehicle-level integration validation
- **Field Testing**: Real-world operational validation
- **Compliance Testing**: Standards and regulatory compliance verification

### 14.3 Requirements Summary
- **Total V&V Requirements**: 199 requirements (EPS-VVR-001 to EPS-VVR-199)
- **Verification Requirements**: 60 requirements
- **Validation Requirements**: 50 requirements
- **Testing Requirements**: 45 requirements
- **Safety V&V**: 25 requirements
- **Process Management**: 19 requirements

## 15. Requirements Traceability

### 15.1 Traceability Matrix

The following table shows the traceability between different requirement categories:

| From/To | FR | SR | PR | ER | IR | DR | EDR | SIR | VVR |
|---------|----|----|----|----|----|----|-----|-----|-----|
| **FR**  | -  | ✓  | ✓  | ✓  | ✓  | ✓  | ✓   | ✓   | ✓   |
| **SR**  | ✓  | -  | ✓  | ✓  | ✓  | ✓  | ✓   | ✓   | ✓   |
| **PR**  | ✓  | ✓  | -  | ✓  | ✓  | ✓  | ✓   | ✓   | ✓   |
| **ER**  | ✓  | ✓  | ✓  | -  | ✓  | ✓  | ✓   | ✓   | ✓   |
| **IR**  | ✓  | ✓  | ✓  | ✓  | -  | ✓  | ✓   | ✓   | ✓   |
| **DR**  | ✓  | ✓  | ✓  | ✓  | ✓  | -  | ✓   | ✓   | ✓   |
| **EDR** | ✓  | ✓  | ✓  | ✓  | ✓  | ✓  | -   | ✓   | ✓   |
| **SIR** | ✓  | ✓  | ✓  | ✓  | ✓  | ✓  | ✓   | -   | ✓   |
| **VVR** | ✓  | ✓  | ✓  | ✓  | ✓  | ✓  | ✓   | ✓   | -   |

### 15.2 Requirements Coverage

- **Total System Requirements**: 1,341 requirements across all categories
- **Safety-Critical Requirements**: 143 requirements (ASIL A-D)
- **Performance-Critical Requirements**: 128 requirements
- **Interface Requirements**: 174 requirements
- **Verification Requirements**: 199 requirements

### 15.3 Traceability Tools

Requirements traceability is maintained using:
- Requirements management tools (DOORS, Polarion, etc.)
- Traceability matrices linking requirements to design, test, and validation
- Change impact analysis capabilities
- Coverage analysis and gap identification

## 16. Compliance and Standards

### 16.1 Functional Safety Standards

- **ISO 26262**: Road vehicles — Functional safety
  - Part 1: Vocabulary
  - Part 3: Concept phase (HARA, safety goals)
  - Part 4: Product development at system level
  - Part 5: Product development at hardware level
  - Part 6: Product development at software level

### 16.2 Automotive Standards

- **ISO 16750 series**: Environmental conditions and testing
- **CISPR 25**: Radio disturbance characteristics
- **ISO 11898**: Controller Area Network (CAN)
- **ISO 14229**: Unified Diagnostic Services (UDS)
- **SAE J1939**: Heavy duty vehicle network

### 16.3 Regulatory Requirements

- **FMVSS 135**: Light vehicle brake systems (steering-related)
- **ECE R79**: Steering equipment
- **GB Standards**: Chinese automotive regulations
- **Regional Requirements**: Market-specific regulations

### 16.4 Quality Standards

- **ISO/TS 16949**: Automotive quality management systems
- **ISO 9001**: Quality management systems
- **IATF 16949**: Automotive quality management system requirements

## 17. Document Control

### 17.1 Document Hierarchy

This master document references the following detailed requirements documents:

1. [`eps_system_research.md`](eps_system_research.md) - System Architecture and Research
2. [`eps_item_definition.md`](eps_item_definition.md) - Item Definition and Boundaries
3. [`eps_functional_requirements.md`](eps_functional_requirements.md) - Functional Requirements
4. [`eps_hara_analysis.md`](eps_hara_analysis.md) - Hazard Analysis and Risk Assessment
5. [`eps_safety_requirements.md`](eps_safety_requirements.md) - Safety Requirements
6. [`eps_performance_requirements.md`](eps_performance_requirements.md) - Performance Requirements
7. [`eps_electrical_power_requirements.md`](eps_electrical_power_requirements.md) - Electrical and Power Requirements
8. [`eps_interface_requirements.md`](eps_interface_requirements.md) - Interface Requirements
9. [`eps_diagnostic_monitoring_requirements.md`](eps_diagnostic_monitoring_requirements.md) - Diagnostic and Monitoring Requirements
10. [`eps_environmental_durability_requirements.md`](eps_environmental_durability_requirements.md) - Environmental and Durability Requirements
11. [`eps_system_integration_requirements.md`](eps_system_integration_requirements.md) - System Integration Requirements
12. [`eps_validation_verification_requirements.md`](eps_validation_verification_requirements.md) - Validation and Verification Requirements

### 17.2 Version Control

- **Document Version**: 1.0
- **Release Date**: 2025-07-29
- **Next Review Date**: 2025-10-29
- **Change Control**: All changes require formal change control process

### 17.3 Approval Matrix

| Role | Name | Signature | Date |
|------|------|-----------|------|
| **Chief Engineer** | [Name Required] | [Signature Required] | [Date Required] |
| **Safety Manager** | [Name Required] | [Signature Required] | [Date Required] |
| **Program Manager** | [Name Required] | [Signature Required] | [Date Required] |
| **Quality Manager** | [Name Required] | [Signature Required] | [Date Required] |
| **Customer Representative** | [Name Required] | [Signature Required] | [Date Required] |

### 17.4 Distribution List

This document is distributed to:
- Engineering teams (systems, hardware, software, safety)
- Program and project management
- Quality assurance and validation teams
- Customer and regulatory representatives
- Manufacturing and service organizations

### 17.5 Change History

| Version | Date | Author | Description |
|---------|------|--------|-------------|
| 1.0 | 2025-07-29 | System Architect | Initial release of complete EPS system requirements |

---

**End of Document**

*This document represents the complete Electronic Power Steering System Requirements specification, integrating all aspects of system functionality, safety, performance, and validation requirements necessary for successful system development and deployment.*