# Electronic Power Steering (EPS) Performance Requirements

## 1. Introduction

### 1.1 Purpose
This document defines the performance requirements for the Electronic Power Steering (EPS) system. These requirements specify the quantitative performance characteristics that the system must achieve to meet customer expectations and safety requirements.

### 1.2 Scope
This document covers all performance aspects of the EPS system including:
- Torque performance requirements
- Response time and latency requirements
- Accuracy and precision requirements
- Dynamic performance requirements
- Efficiency and power consumption requirements
- Noise, vibration, and harshness (NVH) requirements

### 1.3 Requirements Notation
- **SHALL**: Mandatory performance requirement
- **SHOULD**: Recommended performance requirement
- **REQ-ID**: Unique requirement identifier format: EPS-PR-XXX

## 2. Torque Performance Requirements

### 2.1 Assistance Torque Range

**EPS-PR-001**: The EPS system SHALL provide assistance torque in the range of 0 to 8 Nm.

**EPS-PR-002**: The EPS system SHALL provide maximum assistance torque of 8 Nm at motor output shaft.

**EPS-PR-003**: The EPS system SHALL provide minimum detectable assistance torque of 0.1 Nm.

**EPS-PR-004**: The EPS system SHALL provide assistance torque resolution of ≤0.05 Nm.

### 2.2 Torque Accuracy and Precision

**EPS-PR-005**: The EPS system SHALL provide assistance torque with accuracy of ±5% of commanded value.

**EPS-PR-006**: The EPS system SHALL maintain torque accuracy across the operating temperature range (-40°C to +85°C).

**EPS-PR-007**: The EPS system SHALL provide torque repeatability within ±2% for identical input conditions.

**EPS-PR-008**: The EPS system SHALL maintain torque linearity with deviation <3% from ideal linear response.

### 2.3 Torque Sensing Performance

**EPS-PR-009**: The torque sensor SHALL measure driver input torque in the range of -10 Nm to +10 Nm.

**EPS-PR-010**: The torque sensor SHALL provide measurement accuracy of ±2% of full scale.

**EPS-PR-011**: The torque sensor SHALL provide measurement resolution of ≤0.02 Nm.

**EPS-PR-012**: The torque sensor SHALL have hysteresis <1% of full scale range.

**EPS-PR-013**: The torque sensor SHALL provide temperature coefficient <0.02%/°C.

## 3. Response Time and Latency Requirements

### 3.1 System Response Time

**EPS-PR-014**: The EPS system SHALL respond to driver torque input within 50ms (10-90% rise time).

**EPS-PR-015**: The EPS system SHALL achieve 90% of commanded assistance torque within 100ms.

**EPS-PR-016**: The EPS system SHALL achieve steady-state assistance within 200ms.

**EPS-PR-017**: The EPS system SHALL respond to step torque input with overshoot <10%.

### 3.2 Signal Processing Latency

**EPS-PR-018**: The torque sensor signal processing SHALL introduce latency <10ms.

**EPS-PR-019**: The motor control loop SHALL have execution cycle time ≤1ms.

**EPS-PR-020**: The assistance calculation SHALL be completed within 5ms of sensor reading.

**EPS-PR-021**: The CAN communication SHALL introduce latency <20ms for critical signals.

### 3.3 Fault Detection Response Time

**EPS-PR-022**: The EPS system SHALL detect critical faults within 100ms.

**EPS-PR-023**: The EPS system SHALL detect sensor faults within 50ms.

**EPS-PR-024**: The EPS system SHALL transition to safe state within fault tolerance time specified in safety requirements.

## 4. Dynamic Performance Requirements

### 4.1 Frequency Response

**EPS-PR-025**: The EPS system SHALL have bandwidth ≥10 Hz for assistance function.

**EPS-PR-026**: The EPS system SHALL maintain phase margin >45° for stability.

**EPS-PR-027**: The EPS system SHALL have gain margin >6 dB for stability.

**EPS-PR-028**: The EPS system SHALL not exhibit resonance peaks >3 dB in frequency response.

### 4.2 Steering Feel and Road Feel

**EPS-PR-029**: The EPS system SHALL transmit road surface information to driver with attenuation <50%.

**EPS-PR-030**: The EPS system SHALL provide consistent steering feel across speed range 0-200 km/h.

**EPS-PR-031**: The EPS system SHALL maintain steering feel consistency with temperature variation <20%.

**EPS-PR-032**: The EPS system SHALL provide smooth torque transitions without perceptible steps.

### 4.3 Return-to-Center Performance

**EPS-PR-033**: The EPS system SHALL return steering wheel to center ±5° from 90° deflection within 3 seconds at 50 km/h.

**EPS-PR-034**: The EPS system SHALL provide return-to-center torque proportional to steering angle with gain 0.02-0.05 Nm/°.

**EPS-PR-035**: The EPS system SHALL adjust return-to-center characteristics based on vehicle speed.

**EPS-PR-036**: The EPS system SHALL not overshoot center position by more than 2° during return.

### 4.4 Damping Performance

**EPS-PR-037**: The EPS system SHALL provide steering damping coefficient in range 0.01-0.1 Nm·s/°.

**EPS-PR-038**: The EPS system SHALL adjust damping based on vehicle speed with higher damping at high speeds.

**EPS-PR-039**: The EPS system SHALL provide damping to suppress steering wheel oscillations >0.5 Hz.

## 5. Speed-Sensitive Performance

### 5.1 Speed-Based Assistance Curve

**EPS-PR-040**: The EPS system SHALL provide maximum assistance at vehicle speeds 0-10 km/h.

**EPS-PR-041**: The EPS system SHALL reduce assistance linearly from 10-60 km/h to 50% of maximum.

**EPS-PR-042**: The EPS system SHALL maintain minimum 30% assistance at speeds >100 km/h.

**EPS-PR-043**: The EPS system SHALL provide smooth assistance transitions with speed changes.

### 5.2 Speed Signal Processing

**EPS-PR-044**: The EPS system SHALL process vehicle speed signals with update rate ≥10 Hz.

**EPS-PR-045**: The EPS system SHALL filter speed signals to prevent assistance fluctuations.

**EPS-PR-046**: The EPS system SHALL handle speed signal loss with appropriate fallback behavior.

## 6. Position and Angle Performance

### 6.1 Steering Angle Measurement

**EPS-PR-047**: The steering angle sensor SHALL measure absolute angle in range -720° to +720°.

**EPS-PR-048**: The steering angle sensor SHALL provide measurement accuracy of ±1°.

**EPS-PR-049**: The steering angle sensor SHALL provide measurement resolution of ≤0.1°.

**EPS-PR-050**: The steering angle sensor SHALL maintain accuracy over full temperature range.

### 6.2 Motor Position Sensing

**EPS-PR-051**: The motor position sensor SHALL provide resolution ≤1° electrical.

**EPS-PR-052**: The motor position sensor SHALL provide position accuracy ±2° electrical.

**EPS-PR-053**: The motor position sensor SHALL support motor speeds up to 3000 RPM.

**EPS-PR-054**: The motor position sensor SHALL provide commutation signals with jitter <0.5° electrical.

## 7. Power and Efficiency Requirements

### 7.1 Power Consumption

**EPS-PR-055**: The EPS system SHALL limit continuous power consumption to 150W.

**EPS-PR-056**: The EPS system SHALL limit peak power consumption to 300W for duration <10 seconds.

**EPS-PR-057**: The EPS system SHALL limit standby power consumption to <50mW.

**EPS-PR-058**: The EPS system SHALL optimize power consumption based on assistance demand.

### 7.2 System Efficiency

**EPS-PR-059**: The EPS system SHALL achieve overall efficiency >80% at rated load.

**EPS-PR-060**: The motor drive efficiency SHALL be >90% at rated operating point.

**EPS-PR-061**: The EPS system SHALL maintain efficiency >70% across full load range.

**EPS-PR-062**: The EPS system SHALL minimize losses during low assistance conditions.

### 7.3 Thermal Performance

**EPS-PR-063**: The EPS system SHALL operate continuously at ambient temperature up to 85°C.

**EPS-PR-064**: The motor SHALL not exceed 150°C winding temperature during continuous operation.

**EPS-PR-065**: The ECU SHALL not exceed 105°C junction temperature during operation.

**EPS-PR-066**: The EPS system SHALL implement thermal derating when temperature limits are approached.

## 8. Noise, Vibration, and Harshness (NVH) Requirements

### 8.1 Acoustic Noise Requirements

**EPS-PR-067**: The EPS system SHALL generate acoustic noise <40 dBA at 1m distance during operation.

**EPS-PR-068**: The EPS system SHALL not generate tonal noise >35 dBA in any 1/3 octave band.

**EPS-PR-069**: The EPS system SHALL minimize noise during parking maneuvers (<45 dBA).

**EPS-PR-070**: The EPS system SHALL not generate audible noise during standby operation.

### 8.2 Vibration Requirements

**EPS-PR-071**: The EPS system SHALL not transmit vibrations >0.5 m/s² to steering wheel in frequency range 10-100 Hz.

**EPS-PR-072**: The EPS system SHALL minimize motor cogging torque to <2% of rated torque.

**EPS-PR-073**: The EPS system SHALL not generate steering wheel vibrations during motor commutation.

**EPS-PR-074**: The EPS system SHALL isolate motor vibrations from steering system mechanically.

### 8.3 Steering Feel Quality

**EPS-PR-075**: The EPS system SHALL provide smooth steering feel without notchiness or roughness.

**EPS-PR-076**: The EPS system SHALL not introduce perceptible torque ripple during operation.

**EPS-PR-077**: The EPS system SHALL maintain consistent steering feel across all operating conditions.

## 9. Environmental Performance Requirements

### 9.1 Temperature Performance

**EPS-PR-078**: The EPS system SHALL operate within specifications from -40°C to +85°C ambient.

**EPS-PR-079**: The EPS system SHALL survive storage temperatures from -50°C to +95°C.

**EPS-PR-080**: The EPS system SHALL maintain performance during temperature transients.

**EPS-PR-081**: The EPS system SHALL compensate for temperature effects on sensors and actuators.

### 9.2 Humidity and Contamination

**EPS-PR-082**: The EPS system SHALL operate in humidity up to 95% relative humidity (non-condensing).

**EPS-PR-083**: The EPS system SHALL resist contamination from dust, salt spray, and automotive fluids.

**EPS-PR-084**: The EPS system SHALL maintain sealing integrity throughout service life.

### 9.3 Vibration and Shock

**EPS-PR-085**: The EPS system SHALL withstand automotive vibration per ISO 16750-3.

**EPS-PR-086**: The EPS system SHALL survive shock loads per ISO 16750-3.

**EPS-PR-087**: The EPS system SHALL maintain performance during vibration exposure.

## 10. Electromagnetic Compatibility (EMC) Performance

### 10.1 EMC Immunity

**EPS-PR-088**: The EPS system SHALL meet automotive EMC immunity requirements per CISPR 25.

**EPS-PR-089**: The EPS system SHALL operate correctly during EMC test conditions.

**EPS-PR-090**: The EPS system SHALL not degrade performance due to electromagnetic interference.

### 10.2 EMC Emissions

**EPS-PR-091**: The EPS system SHALL meet automotive EMC emission limits per CISPR 25.

**EPS-PR-092**: The EPS system SHALL not interfere with other vehicle electronic systems.

**EPS-PR-093**: The EPS system SHALL minimize conducted and radiated emissions.

## 11. Reliability and Durability Performance

### 11.1 Reliability Targets

**EPS-PR-094**: The EPS system SHALL achieve Mean Time Between Failures (MTBF) >100,000 hours.

**EPS-PR-095**: The EPS system SHALL achieve failure rate <10 FIT (Failures in Time).

**EPS-PR-096**: The EPS system SHALL maintain performance over 15-year service life.

**EPS-PR-097**: The EPS system SHALL survive 300,000 km vehicle operation.

### 11.2 Durability Testing

**EPS-PR-098**: The EPS system SHALL pass accelerated life testing equivalent to 15 years operation.

**EPS-PR-099**: The EPS system SHALL survive 10 million steering cycles at full deflection.

**EPS-PR-100**: The EPS system SHALL maintain performance after thermal cycling per automotive standards.

### 11.3 Wear and Degradation

**EPS-PR-101**: The EPS system SHALL show <10% performance degradation over service life.

**EPS-PR-102**: The EPS system SHALL maintain torque accuracy within ±7% at end of life.

**EPS-PR-103**: The EPS system SHALL not exhibit excessive wear in mechanical components.

## 12. Calibration and Adjustment Performance

### 12.1 Calibration Capability

**EPS-PR-104**: The EPS system SHALL support calibration of assistance characteristics.

**EPS-PR-105**: The EPS system SHALL allow adjustment of speed-sensitive parameters.

**EPS-PR-106**: The EPS system SHALL support sensor offset calibration procedures.

**EPS-PR-107**: The EPS system SHALL validate calibration parameters before use.

### 12.2 Manufacturing Tolerances

**EPS-PR-108**: The EPS system SHALL accommodate component tolerances through calibration.

**EPS-PR-109**: The EPS system SHALL provide consistent performance across production units.

**EPS-PR-110**: The EPS system SHALL support end-of-line testing and calibration.

## 13. Diagnostic Performance Requirements

### 13.1 Self-Diagnostic Capability

**EPS-PR-111**: The EPS system SHALL perform continuous self-diagnostics during operation.

**EPS-PR-112**: The EPS system SHALL detect performance degradation and report status.

**EPS-PR-113**: The EPS system SHALL provide diagnostic information for service support.

### 13.2 Diagnostic Coverage

**EPS-PR-114**: The EPS system SHALL achieve >95% diagnostic coverage for performance-related faults.

**EPS-PR-115**: The EPS system SHALL detect sensor drift and calibration errors.

**EPS-PR-116**: The EPS system SHALL monitor system performance parameters continuously.

## 14. Performance Verification Requirements

### 14.1 Test Methods

**EPS-PR-117**: Performance requirements SHALL be verified through standardized test procedures.

**EPS-PR-118**: Test conditions SHALL cover full range of operating environments.

**EPS-PR-119**: Performance tests SHALL include both steady-state and dynamic conditions.

### 14.2 Acceptance Criteria

**EPS-PR-120**: All performance requirements SHALL be met for system acceptance.

**EPS-PR-121**: Performance margins SHALL be maintained for production variability.

**EPS-PR-122**: Performance degradation limits SHALL be established for service life.

## 15. Performance Monitoring and Reporting

### 15.1 Performance Metrics

**EPS-PR-123**: Key performance indicators SHALL be defined and monitored.

**EPS-PR-124**: Performance data SHALL be collected during development and validation.

**EPS-PR-125**: Field performance SHALL be monitored through diagnostic data.

### 15.2 Performance Improvement

**EPS-PR-126**: Performance feedback SHALL be used for continuous improvement.

**EPS-PR-127**: Performance issues SHALL be analyzed and corrected systematically.

**EPS-PR-128**: Performance lessons learned SHALL be documented and shared.

## 16. Document Control

### 16.1 Document Information
- **Document ID**: EPS-PR-001
- **Version**: 1.0
- **Status**: Draft
- **Classification**: Internal Use

### 16.2 Approval Requirements
- **Chief Engineer**: [Signature Required]
- **Performance Engineering Manager**: [Signature Required]
- **Program Manager**: [Signature Required]
- **Quality Manager**: [Signature Required]

### 16.3 Change Control
All changes to performance requirements SHALL be evaluated for impact on system design, safety, and customer satisfaction before approval.

## 17. References

- ISO 16750 series - Road vehicles — Environmental conditions and testing
- CISPR 25 - Vehicles, boats and internal combustion engines — Radio disturbance characteristics
- SAE J1113 series - Electromagnetic Compatibility Measurement Procedures
- EPS Functional Requirements Document (EPS-FR-001)
- EPS Safety Requirements Document (EPS-SR-001)
- EPS Item Definition Document (EPS-ITEM-DEF-001)
- Automotive industry performance standards and best practices