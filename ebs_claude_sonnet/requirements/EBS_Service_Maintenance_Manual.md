# Electronic Braking System (EBS) - Service and Maintenance Manual

## Document Information
- **Document Title**: EBS Service and Maintenance Manual
- **Version**: 1.0
- **Date**: 2025-07-29
- **Classification**: Service Document
- **Related Documents**: EBS_Requirements_Specification.md, EBS_Hardware_Design_Specifications.md

## Table of Contents
1. [Introduction](#introduction)
2. [System Overview](#system-overview)
3. [Safety Precautions](#safety-precautions)
4. [Service Tools and Equipment](#service-tools-and-equipment)
5. [Diagnostic Procedures](#diagnostic-procedures)
6. [Maintenance Procedures](#maintenance-procedures)
7. [Repair Procedures](#repair-procedures)
8. [Calibration Procedures](#calibration-procedures)
9. [Software Updates](#software-updates)
10. [Troubleshooting Guide](#troubleshooting-guide)
11. [Parts and Components](#parts-and-components)
12. [Service Documentation](#service-documentation)

---

## 1. Introduction

### 1.1 Purpose
This Service and Maintenance Manual provides comprehensive instructions for the proper service, maintenance, diagnosis, and repair of the Electronic Braking System (EBS). It is intended for use by qualified automotive technicians and service personnel.

### 1.2 Scope
This manual covers:
- System operation and component identification
- Safety procedures and precautions
- Diagnostic procedures and fault finding
- Preventive maintenance procedures
- Repair and replacement procedures
- Calibration and adjustment procedures
- Software update procedures
- Troubleshooting and problem resolution

### 1.3 Target Audience
- **Certified Automotive Technicians**: ASE certified brake system technicians
- **Dealership Service Personnel**: Factory-trained service technicians
- **Fleet Maintenance Personnel**: Commercial fleet maintenance technicians
- **Training Instructors**: Technical training and education personnel

### 1.4 Safety Warning
⚠️ **CRITICAL SAFETY WARNING**: The EBS is a safety-critical system. Improper service or repair can result in brake system failure, leading to serious injury or death. Only qualified technicians with proper training and equipment should service this system.

### 1.5 Required Qualifications
- ASE certification in Brake Systems (A5)
- EBS-specific training certification
- Familiarity with automotive diagnostic equipment
- Understanding of CAN bus systems and diagnostics
- Knowledge of automotive electrical systems

---

## 2. System Overview

### 2.1 EBS System Description
The Electronic Braking System (EBS) integrates Anti-lock Braking System (ABS), Electronic Stability Control (ESC), and Traction Control System (TCS) functions into a unified safety-critical system.

### 2.2 Major Components

#### 2.2.1 Electronic Control Unit (ECU)
- **Location**: Engine compartment, mounted on firewall
- **Function**: Central processing unit for all EBS functions
- **Identification**: Part number label on housing
- **Connections**: Two 64-pin connectors (A and B)

#### 2.2.2 Hydraulic Modulator Unit (HMU)
- **Location**: Engine compartment, near brake master cylinder
- **Function**: Brake pressure modulation for ABS/ESC operation
- **Components**: Solenoid valves, pump motor, accumulator
- **Connections**: Hydraulic lines and electrical connector

#### 2.2.3 Sensors
| Sensor Type | Quantity | Location | Function |
|-------------|----------|----------|----------|
| **Wheel Speed Sensors** | 4 | Each wheel hub | Wheel speed measurement |
| **Yaw Rate Sensor** | 1 | Center console area | Vehicle yaw rate |
| **Lateral Acceleration** | 1 | Center console area | Lateral acceleration |
| **Steering Angle Sensor** | 1 | Steering column | Steering wheel angle |
| **Brake Pressure Sensors** | 2 | Master cylinder | Brake pressure |

#### 2.2.4 Warning Systems
- **ABS Warning Lamp**: Dashboard amber lamp
- **ESC Warning Lamp**: Dashboard amber lamp with ESC symbol
- **ESC OFF Switch**: Driver-operated disable switch
- **Brake Warning Lamp**: Dashboard red brake warning lamp

### 2.3 System Operation Modes

#### 2.3.1 Normal Operation Mode
- All systems functional and active
- Continuous monitoring of vehicle dynamics
- Ready to intervene when necessary
- All warning lamps off (except during bulb check)

#### 2.3.2 Degraded Operation Mode
- Non-critical component failure detected
- Reduced functionality but basic braking maintained
- Appropriate warning lamps illuminated
- System continues to operate with limitations

#### 2.3.3 Fail-Safe Mode
- Critical component failure detected
- System defaults to conventional braking
- All electronic functions disabled
- Multiple warning lamps illuminated

---

## 3. Safety Precautions

### 3.1 General Safety Requirements

#### 3.1.1 Personal Protective Equipment (PPE)
- **Safety Glasses**: ANSI Z87.1 approved safety glasses required
- **Work Gloves**: Cut-resistant gloves when handling sharp components
- **Safety Shoes**: Non-slip, steel-toe safety shoes
- **Hearing Protection**: When using pneumatic tools or in noisy environments

#### 3.1.2 Vehicle Safety Procedures
- **Vehicle Securing**: Ensure vehicle is on level surface with parking brake applied
- **Wheel Chocks**: Use wheel chocks when lifting vehicle
- **Jack Stands**: Never work under vehicle supported only by jack
- **Battery Disconnect**: Disconnect battery negative terminal before electrical work

#### 3.1.3 Brake System Safety
- **Brake Fluid Handling**: Use only specified DOT 4 brake fluid
- **System Pressure**: Relieve brake system pressure before opening hydraulic connections
- **Contamination Prevention**: Keep brake system components clean and free from contamination
- **Air in System**: Ensure complete air removal from brake system after service

### 3.2 Electrical Safety

#### 3.2.1 High Voltage Precautions
- **System Voltage**: 12V system - low voltage but high current possible
- **Short Circuit Prevention**: Prevent short circuits that could damage ECU
- **ESD Protection**: Use ESD protection when handling electronic components
- **Connector Care**: Handle connectors carefully to prevent damage

#### 3.2.2 Diagnostic Equipment Safety
- **Equipment Grounding**: Ensure diagnostic equipment is properly grounded
- **Connection Verification**: Verify correct connections before powering up
- **Software Updates**: Use only approved software and update procedures
- **Data Backup**: Backup ECU data before performing updates or calibrations

### 3.3 Environmental Safety

#### 3.3.1 Brake Fluid Disposal
- **Environmental Protection**: Dispose of brake fluid according to local regulations
- **Contamination Prevention**: Prevent brake fluid spills and contamination
- **Recycling**: Use approved brake fluid recycling procedures where available
- **Documentation**: Maintain records of brake fluid disposal

#### 3.3.2 Component Disposal
- **Electronic Components**: Dispose of electronic components according to WEEE regulations
- **Metal Components**: Recycle metal components through approved recyclers
- **Plastic Components**: Dispose of plastic components according to local regulations
- **Hazardous Materials**: Handle any hazardous materials according to MSDS requirements

---

## 4. Service Tools and Equipment

### 4.1 Required Diagnostic Equipment

#### 4.1.1 Scan Tool Requirements
- **OBD-II Compatibility**: Full OBD-II diagnostic capability
- **Manufacturer Specific**: EBS-specific diagnostic functions
- **CAN Bus Support**: High-speed CAN bus communication
- **Data Logging**: Capability to log and analyze data
- **Software Updates**: Ability to perform ECU software updates

**Recommended Scan Tools:**
- Professional automotive scan tool with EBS support
- Manufacturer-specific diagnostic tool
- Oscilloscope capability for signal analysis
- Multimeter with automotive functions

#### 4.1.2 Pressure Testing Equipment
- **Brake Pressure Gauge**: 0-300 bar range, ±1% accuracy
- **Pressure Bleeder**: Pneumatic brake bleeder with pressure regulation
- **Vacuum Pump**: Hand-operated vacuum pump for brake bleeding
- **Pressure Transducers**: For dynamic pressure measurement

#### 4.1.3 Electrical Testing Equipment
- **Digital Multimeter**: True RMS, automotive functions
- **Oscilloscope**: 2-channel minimum, 100 MHz bandwidth
- **Signal Generator**: For sensor simulation and testing
- **Breakout Box**: For ECU connector testing
- **Wire Piercing Probes**: For non-invasive signal measurement

### 4.2 Mechanical Tools

#### 4.2.1 General Tools
- **Socket Set**: Metric sockets, 8mm to 19mm
- **Wrench Set**: Combination wrenches, 8mm to 19mm
- **Screwdriver Set**: Phillips and flathead, various sizes
- **Pliers Set**: Needle nose, standard, and electrical pliers
- **Torque Wrench**: 10-150 Nm range, ±3% accuracy

#### 4.2.2 Specialized Tools
- **Brake Line Wrenches**: Flare nut wrenches for brake lines
- **Connector Removal Tools**: For electrical connector removal
- **Seal Installation Tools**: For hydraulic seal installation
- **Spring Compressors**: For brake spring removal/installation
- **Bearing Pullers**: For wheel bearing service

#### 4.2.3 Lifting Equipment
- **Vehicle Lift**: Two-post or four-post lift, appropriate capacity
- **Floor Jack**: Hydraulic floor jack, minimum 2-ton capacity
- **Jack Stands**: Rated for vehicle weight, multiple pairs
- **Wheel Chocks**: Heavy-duty wheel chocks for safety

### 4.3 Calibration Equipment

#### 4.3.1 Wheel Alignment Equipment
- **Alignment System**: Computer-controlled wheel alignment system
- **Alignment Targets**: Wheel-mounted alignment targets
- **Steering Wheel Holder**: To maintain steering position during alignment
- **Turntables**: Front wheel turntables for alignment adjustments

#### 4.3.2 Sensor Calibration Tools
- **Yaw Rate Sensor Calibration**: Level surface and calibration procedure
- **Steering Angle Calibration**: Steering wheel centering tools
- **Accelerometer Calibration**: Level reference and calibration software
- **Wheel Speed Sensor Gap**: Feeler gauges for air gap measurement

---

## 5. Diagnostic Procedures

### 5.1 Initial System Check

#### 5.1.1 Visual Inspection Checklist
- [ ] Check all warning lamps during key-on bulb test
- [ ] Inspect brake fluid level and condition
- [ ] Check for obvious damage to components
- [ ] Verify all electrical connections are secure
- [ ] Inspect brake lines for leaks or damage
- [ ] Check wheel speed sensor mounting and air gaps
- [ ] Verify proper tire pressures and condition

#### 5.1.2 Basic System Test
1. **Key On, Engine Off Test**
   - Turn ignition to ON position
   - Verify all warning lamps illuminate for bulb test
   - All lamps should extinguish after 3-5 seconds
   - Note any lamps that remain illuminated

2. **Engine Running Test**
   - Start engine and let idle
   - Verify all warning lamps are off
   - Listen for unusual noises from HMU
   - Check for any diagnostic trouble codes

3. **Road Test Preparation**
   - Ensure safe test route is available
   - Verify brake pedal feel and travel
   - Check parking brake operation
   - Confirm all safety equipment is in place

### 5.2 Diagnostic Trouble Code (DTC) Analysis

#### 5.2.1 DTC Categories
| Code Range | System | Description |
|------------|--------|-------------|
| **C0xxx** | Chassis | ABS/ESC/TCS related codes |
| **B0xxx** | Body | Warning lamp and switch codes |
| **U0xxx** | Network | CAN communication codes |
| **P0xxx** | Powertrain | Engine-related brake codes |

#### 5.2.2 Common DTCs and Meanings
| DTC | Description | Possible Causes |
|-----|-------------|-----------------|
| **C0035** | Left Front Wheel Speed Sensor | Sensor failure, wiring, air gap |
| **C0040** | Right Front Wheel Speed Sensor | Sensor failure, wiring, air gap |
| **C0045** | Left Rear Wheel Speed Sensor | Sensor failure, wiring, air gap |
| **C0050** | Right Rear Wheel Speed Sensor | Sensor failure, wiring, air gap |
| **C0121** | Valve Relay Circuit | Relay failure, wiring, ECU |
| **C0141** | System Voltage Low | Battery, alternator, wiring |
| **C0161** | ABS/TCS/ESC Disabled | Multiple system faults |
| **C0196** | System Voltage High | Alternator overcharge, wiring |

#### 5.2.3 DTC Diagnostic Procedure
1. **Retrieve DTCs**
   - Connect scan tool to OBD-II port
   - Navigate to ABS/ESC system
   - Retrieve all current and pending DTCs
   - Record all codes and freeze frame data

2. **Analyze DTC Information**
   - Determine if codes are current or history
   - Check for multiple related codes
   - Review freeze frame data for conditions
   - Prioritize codes by safety criticality

3. **Follow Diagnostic Tree**
   - Use manufacturer diagnostic procedures
   - Follow logical diagnostic sequence
   - Perform specified tests and measurements
   - Verify repair before clearing codes

### 5.3 Component Testing Procedures

#### 5.3.1 Wheel Speed Sensor Testing
**Visual Inspection:**
- Check sensor mounting and security
- Inspect sensor cable for damage
- Verify proper air gap (0.5-3.0mm)
- Check tone ring for damage or debris

**Electrical Testing:**
1. **Resistance Test**
   - Disconnect sensor connector
   - Measure resistance across sensor terminals
   - Specification: 1000-2000 ohms
   - Replace sensor if out of specification

2. **Signal Test**
   - Connect oscilloscope to sensor output
   - Rotate wheel slowly by hand
   - Verify clean AC waveform generation
   - Amplitude should increase with speed

3. **Insulation Test**
   - Measure resistance from each terminal to ground
   - Specification: >10 megohms
   - Replace sensor if insulation is compromised

#### 5.3.2 Yaw Rate Sensor Testing
**Calibration Check:**
1. **Zero Point Calibration**
   - Ensure vehicle is on level surface
   - Engine running, wheels straight ahead
   - Use scan tool to check yaw rate reading
   - Should read 0 ±2 degrees/second

2. **Dynamic Test**
   - Perform controlled steering inputs
   - Monitor yaw rate sensor response
   - Verify sensor tracks steering inputs
   - Check for proper return to zero

**Electrical Testing:**
- Check sensor power supply (5V ±0.25V)
- Verify ground circuit continuity
- Test CAN communication signals
- Check for proper sensor initialization

#### 5.3.3 Hydraulic Modulator Unit Testing
**Pressure Testing:**
1. **Static Pressure Test**
   - Connect pressure gauge to test port
   - Apply brake pedal with specific force
   - Verify pressure reading matches specification
   - Check for pressure leakage over time

2. **Dynamic Pressure Test**
   - Use scan tool to activate individual valves
   - Monitor pressure changes during activation
   - Verify proper valve operation and sealing
   - Check pump operation and pressure buildup

**Electrical Testing:**
- Test solenoid valve resistance (8-15 ohms)
- Check pump motor current draw
- Verify ECU control signals to valves
- Test valve response time and operation

---

## 6. Maintenance Procedures

### 6.1 Scheduled Maintenance

#### 6.1.1 Maintenance Intervals
| Service | Interval | Description |
|---------|----------|-------------|
| **System Check** | 12 months/12,000 miles | Visual inspection and basic function test |
| **Brake Fluid Service** | 24 months/24,000 miles | Brake fluid replacement and system flush |
| **Comprehensive Test** | 36 months/36,000 miles | Complete system test and calibration |
| **Component Inspection** | 48 months/48,000 miles | Detailed component inspection and testing |

#### 6.1.2 Annual System Check Procedure
1. **Visual Inspection**
   - Inspect all visible components for damage
   - Check brake fluid level and condition
   - Verify warning lamp operation
   - Check for any obvious leaks or damage

2. **Basic Function Test**
   - Retrieve and analyze any DTCs
   - Perform basic system self-test
   - Verify proper warning lamp operation
   - Test basic ABS function (if safe to do so)

3. **Documentation**
   - Record all findings and test results
   - Update maintenance records
   - Provide customer with service report
   - Schedule any required follow-up service

### 6.2 Brake Fluid Service

#### 6.2.1 Brake Fluid Specifications
- **Fluid Type**: DOT 4 brake fluid only
- **Boiling Point**: Dry >260°C, Wet >155°C
- **Viscosity**: -40°C <1800 cSt
- **Compatibility**: Compatible with existing system seals
- **Contamination**: Must be free from water and contaminants

#### 6.2.2 Fluid Replacement Procedure
1. **Preparation**
   - Ensure vehicle is on level surface
   - Remove brake fluid reservoir cap
   - Check fluid condition and contamination
   - Prepare brake bleeding equipment

2. **System Bleeding**
   - Connect pressure bleeder to reservoir
   - Bleed brakes in specified sequence: RR, LR, RF, LF
   - Maintain reservoir level during bleeding
   - Continue until clean fluid flows from each bleeder

3. **ABS System Bleeding**
   - Use scan tool to activate ABS bleeding procedure
   - Follow manufacturer-specific bleeding sequence
   - Ensure all air is removed from HMU
   - Verify proper brake pedal feel after bleeding

4. **Final Checks**
   - Check brake pedal travel and feel
   - Verify proper brake fluid level
   - Test brake warning lamp operation
   - Clear any DTCs related to bleeding procedure

### 6.3 Component Replacement

#### 6.3.1 Wheel Speed Sensor Replacement
1. **Removal Procedure**
   - Raise and support vehicle safely
   - Remove wheel and tire assembly
   - Disconnect sensor electrical connector
   - Remove sensor mounting bolt
   - Carefully extract sensor from hub

2. **Installation Procedure**
   - Clean sensor mounting hole thoroughly
   - Apply thin coat of anti-seize to sensor body
   - Install new sensor with proper torque (8 Nm)
   - Connect electrical connector securely
   - Verify proper air gap (0.5-3.0mm)

3. **Post-Installation Testing**
   - Clear any related DTCs
   - Test sensor operation with scan tool
   - Perform road test to verify operation
   - Document replacement in service records

#### 6.3.2 ECU Replacement
⚠️ **WARNING**: ECU replacement requires special procedures and may require dealer programming.

1. **Pre-Replacement Procedures**
   - Record ECU part number and software version
   - Save ECU configuration data if possible
   - Verify replacement ECU compatibility
   - Ensure proper ESD protection procedures

2. **Removal Procedure**
   - Disconnect battery negative terminal
   - Remove ECU mounting bracket
   - Carefully disconnect both ECU connectors
   - Remove ECU from mounting bracket

3. **Installation Procedure**
   - Install new ECU in mounting bracket
   - Connect both electrical connectors securely
   - Install mounting bracket with proper torque
   - Reconnect battery negative terminal

4. **Post-Installation Programming**
   - Connect scan tool and establish communication
   - Program ECU with correct software version
   - Perform all required calibrations
   - Clear all DTCs and perform system test

---

## 7. Repair Procedures

### 7.1 Wiring Repairs

#### 7.1.1 Wire Repair Standards
- **Wire Gauge**: Use same gauge as original wire
- **Insulation**: Use automotive-grade wire insulation
- **Connections**: Solder and heat shrink all connections
- **Routing**: Route repaired wires away from heat and moving parts
- **Protection**: Use appropriate wire loom and protection

#### 7.1.2 Connector Repair
1. **Connector Inspection**
   - Check for corrosion, damage, or contamination
   - Verify proper terminal retention
   - Check for proper connector mating
   - Inspect sealing and weather protection

2. **Terminal Repair**
   - Remove damaged terminals using proper tools
   - Install new terminals with proper crimping tool
   - Verify proper terminal retention in connector
   - Apply dielectric grease to prevent corrosion

3. **Connector Sealing**
   - Replace damaged seals and gaskets
   - Ensure proper connector alignment
   - Verify weather seal integrity
   - Test connector for proper retention

### 7.2 Hydraulic System Repairs

#### 7.2.1 Brake Line Repair
⚠️ **CRITICAL**: Use only approved brake line materials and fittings.

1. **Line Inspection**
   - Check for leaks, corrosion, or damage
   - Verify proper line routing and support
   - Check fitting torque and condition
   - Inspect for proper clearance from moving parts

2. **Line Replacement**
   - Use only DOT-approved brake line
   - Form lines to match original routing
   - Use proper flaring tools for fittings
   - Support lines properly to prevent vibration

3. **Pressure Testing**
   - Pressure test repaired lines to 200 bar
   - Check for leaks at all connections
   - Verify proper line support and routing
   - Bleed air from repaired sections

#### 7.2.2 HMU Service
⚠️ **WARNING**: HMU is not field serviceable. Replace as complete unit.

1. **HMU Removal**
   - Relieve brake system pressure
   - Disconnect electrical connector
   - Remove brake lines (mark for identification)
   - Remove HMU mounting bolts

2. **HMU Installation**
   - Install new HMU with proper torque
   - Connect brake lines with proper torque
   - Connect electrical connector securely
   - Fill and bleed brake system completely

3. **System Initialization**
   - Use scan tool to initialize new HMU
   - Perform all required calibrations
   - Test all ABS/ESC functions
   - Clear all DTCs and verify operation

---

## 8. Calibration Procedures

### 8.1 Steering Angle Sensor Calibration

#### 8.1.1 Calibration Requirements
- Vehicle on level surface
- Wheels straight ahead
- Steering wheel centered
- Engine running
- No DTCs present

#### 8.1.2 Calibration Procedure
1. **Pre-Calibration Checks**
   - Verify wheel alignment is within specification
   - Check tire pressures and condition
   - Ensure steering wheel is properly centered
   - Clear any existing DTCs

2. **Calibration Steps**
   - Connect scan tool to vehicle
   - Navigate to steering angle sensor calibration
   - Follow scan tool prompts for calibration
   - Maintain steering wheel position during procedure
   - Verify calibration completion

3. **Post-Calibration Verification**
   - Check steering angle reading at center (0° ±2°)
   - Perform lock-to-lock steering test
   - Verify proper ESC operation
   - Road test to confirm proper operation

### 8.2 Yaw Rate Sensor Calibration

#### 8.2.1 Calibration Requirements
- Vehicle on level surface (±0.5°)
- Engine running at idle
- Transmission in park/neutral
- All doors closed
- No passenger or cargo load

#### 8.2.2 Zero Point Calibration
1. **Setup Procedure**
   - Position vehicle on known level surface
   - Ensure wheels are straight ahead
   - Allow vehicle to sit stationary for 2 minutes
   - Engine running, all systems stabilized

2. **Calibration Execution**
   - Connect scan tool and navigate to yaw rate calibration
   - Initiate zero point calibration procedure
   - Maintain vehicle stationary during calibration
   - Wait for calibration completion confirmation

3. **Verification Test**
   - Check yaw rate reading (should be 0° ±2°/sec)
   - Perform controlled steering inputs
   - Verify sensor responds correctly to inputs
   - Clear any calibration-related DTCs

### 8.3 System Calibration After Major Repairs

#### 8.3.1 Complete System Recalibration
Required after:
- ECU replacement
- Multiple sensor replacement
- Major suspension work
- Wheel alignment changes
- Accident damage repair

#### 8.3.2 Recalibration Procedure
1. **Pre-Calibration Requirements**
   - All repairs completed and verified
   - No DTCs present in any system
   - Vehicle on level surface
   - Proper tire pressures and wheel alignment

2. **Calibration Sequence**
   - Steering angle sensor calibration
   - Yaw rate sensor zero point calibration
   - Lateral acceleration sensor calibration
   - System initialization and self-test
   - Final verification and road test

3. **Documentation**
   - Record all calibration values
   - Document calibration date and technician
   - Update vehicle service records
   - Provide customer with calibration certificate

---

## 9. Software Updates

### 9.1 Software Update Requirements

#### 9.1.1 Update Conditions
- Battery voltage >12.5V during update
- Engine running or battery charger connected
- Stable communication with ECU
- No pending DTCs that would prevent update
- Proper scan tool software version

#### 9.1.2 Pre-Update Procedures
1. **System Backup**
   - Save current ECU configuration
   - Record current software version
   - Document any custom calibrations
   - Create backup of vehicle data

2. **Update Preparation**
   - Verify correct update file for vehicle
   - Check scan tool battery and connections
   - Ensure stable power supply to vehicle
   - Prepare for potential update failure recovery

### 9.2 Update Procedure

#### 9.2.1 Software Download
1. **Connection Setup**
   - Connect scan tool to OBD-II port
   - Establish communication with ECU
   - Verify ECU identification and compatibility
   - Check current software version

2. **Update Execution**
   - Load correct update file into scan tool
   - Initiate software update procedure
   - Monitor update progress continuously
   - Do not interrupt power during update

3. **Update Verification**
   - Verify successful update completion
   - Check new software version number
   - Perform ECU initialization procedure
   - Clear any update-related DTCs

#### 9.2.2 Post-Update Procedures
1. **System Initialization**
   - Perform complete system self-test
   - Initialize all sensors and actuators
   - Verify proper system operation
   - Check for any new DTCs

2. **Calibration Requirements**
   - Perform steering angle sensor calibration
   - Execute yaw rate sensor calibration
   - Complete any other required calibrations
   - Verify all calibrations are successful

3. **Final Verification**
   - Road test vehicle for proper operation
   - Verify all EBS functions work correctly
   - Check warning lamp operation
   - Document update in service records

### 9.3 Update Troubleshooting

#### 9.3.1 Common Update Issues
| Issue | Possible Cause | Solution |
|-------|----------------|----------|
| **Communication Lost** | Poor connection, low voltage | Check connections, charge battery |
| **Update Failed** | Wrong file, corrupted data | Verify file, retry update |
| **ECU Not Responding** | Update corruption | Attempt recovery procedure |
| **Calibration Errors** | Incomplete update | Repeat calibration procedures |

#### 9.3.2 Recovery Procedures
1. **Soft Recovery**
   - Cycle ignition off/on
   - Retry communication with ECU
   - Attempt update procedure again
   - Check for partial update completion

2. **Hard Recovery**
   - Disconnect battery for 10 minutes
   - Reconnect and attempt communication
   - Use emergency programming mode if available
   - Contact technical support if needed

---

## 10. Troubleshooting Guide

### 10.1 Symptom-Based Troubleshooting

#### 10.1.1 ABS Warning Lamp On
**Possible Causes:**
- Wheel speed sensor failure
- Wiring or connector problems
- ECU internal fault
- Low system voltage
- Hydraulic system fault

**Diagnostic Steps:**
1. Retrieve DTCs and analyze
2. Check wheel speed sensor signals
3. Verify system voltage and grounds
4. Test hydraulic system pressure
5. Check ECU communication

#### 10.1.2 ESC Warning Lamp On
**Possible Causes:**
- Yaw rate sensor fault
- Steering angle sensor fault
- Lateral acceleration sensor fault
- System calibration required
- Multiple sensor faults

**Diagnostic Steps:**
1. Check all sensor calibrations
2. Verify sensor power supplies
3. Test CAN communication
4. Perform sensor functionality tests
5. Check for multiple system faults

#### 10.1.3 Poor Brake Pedal Feel
**Possible Causes:**
- Air in brake system
- Brake fluid contamination
- HMU internal fault
- Master cylinder problems
- Brake line restrictions

**Diagnostic Steps:**
1. Check brake fluid level and condition
2. Bleed brake system completely
3. Test brake system pressure
4. Check for internal HMU leakage
5. Verify proper brake pedal travel

### 10.2 Performance Issues

#### 10.2.1 ABS Activates Too Early
**Possible Causes:**
- Incorrect wheel speed sensor air gap
- Contaminated tone ring
- Tire pressure differences
- Wheel alignment problems
- Road surface conditions

**Diagnostic Steps:**
1. Check wheel speed sensor air gaps
2. Clean tone rings and sensors
3. Verify tire pressures and sizes
4. Check wheel alignment
5. Test on different road surfaces

#### 10.2.2 ESC Intervention Too Aggressive
**Possible Causes:**
- Incorrect sensor calibration
- Tire pressure differences
- Suspension modifications
- Wheel alignment issues
- System sensitivity settings

**Diagnostic Steps:**
1. Recalibrate all sensors
2. Check tire pressures and sizes
3. Verify suspension components
4. Check wheel alignment
5. Review system parameters

#### 10.2.3 System Not Responding
**Possible Causes:**
- ECU power supply problems
- CAN communication failure
- Multiple sensor failures
- Software corruption
- Wiring harness damage

**Diagnostic Steps:**
1. Check ECU power and ground
2. Test CAN bus communication
3. Verify sensor power supplies
4. Check wiring harness integrity
5. Consider ECU replacement

### 10.3 Intermittent Problems

#### 10.3.1 Intermittent Warning Lamps
**Diagnostic Approach:**
- Use data logging to capture events
- Check for loose connections
- Monitor system during temperature changes
- Test during vibration conditions
- Check for water intrusion

#### 10.3.2 Intermittent System Operation
**Diagnostic Approach:**
- Monitor live data during problem occurrence
- Check for thermal-related issues
- Test connections under load
- Verify proper connector sealing
- Check for electromagnetic interference

---

## 11. Parts and Components

### 11.1 Replacement Parts Catalog

#### 11.1.1 Electronic Control Unit
| Part Number | Description | Application | Notes |
|-------------|-------------|-------------|-------|
| EBS-ECU-001 | Primary ECU Assembly | All vehicles | Requires programming |
| EBS-ECU-002 | Secondary ECU Assembly | Dual ECU systems | Backup unit |

#### 11.1.2 Sensors
| Part Number | Description | Location | Specifications |
|-------------|-------------|----------|----------------|
| EBS-WSS-FL | Front Left Wheel Speed Sensor | Left front hub | Hall effect, 5V |
| EBS-WSS-FR | Front Right Wheel Speed Sensor | Right front hub | Hall effect, 5V |
| EBS-WSS-RL | Rear Left Wheel Speed Sensor | Left rear hub | Hall effect, 5V |
| EBS-WSS-RR | Rear Right Wheel Speed Sensor | Right rear hub | Hall effect, 5V |
| EBS-YRS-01 | Yaw Rate Sensor | Center console | ±120°/s range |
| EBS-LAS-01 | Lateral Acceleration Sensor | Center console | ±2g range |
| EBS-SAS-01 | Steering Angle Sensor | Steering column