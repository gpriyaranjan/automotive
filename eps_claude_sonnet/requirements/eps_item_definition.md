# Electronic Power Steering (EPS) Item Definition

## 1. Item Overview

### 1.1 Item Name
Electronic Power Steering System (EPS)

### 1.2 Item Description
The Electronic Power Steering (EPS) system is a safety-critical automotive item that provides steering assistance to the driver through an electric motor-based system. The EPS system reduces steering effort while maintaining vehicle controllability and road feel, ensuring safe and comfortable steering operation across all driving conditions.

### 1.3 Item Classification
- **Item Type**: Safety-critical automotive system
- **Vehicle Function**: Primary steering assistance
- **ISO 26262 Scope**: Yes (safety-related system)
- **Customer Visibility**: Yes (directly affects driver experience)

## 2. Item Boundaries and Interfaces

### 2.1 Physical Boundaries

#### 2.1.1 Included Components
The EPS item includes the following physical components:
- Electronic Control Unit (ECU) with embedded software
- Electric assist motor (BLDC/PMSM)
- Torque sensor assembly
- Steering angle sensor
- Motor position sensor
- Power electronics (motor drive inverter)
- Wiring harness and connectors
- Mechanical mounting hardware
- Software and calibration data

#### 2.1.2 Excluded Components
The following components are NOT part of the EPS item:
- Steering wheel
- Steering column (mechanical parts only)
- Steering rack and pinion (mechanical parts)
- Tie rods and steering linkages
- Vehicle power supply (12V battery, alternator)
- Vehicle communication networks (CAN bus infrastructure)
- Other vehicle ECUs

### 2.2 Functional Boundaries

#### 2.2.1 Primary Functions (Within Item Scope)
1. **Steering Assistance**: Provide electric motor assistance based on driver torque input
2. **Torque Sensing**: Measure and interpret driver steering intentions
3. **Motor Control**: Precisely control electric motor torque output
4. **System Monitoring**: Monitor system health and detect faults
5. **Communication**: Interface with vehicle systems via CAN/LIN networks
6. **Fail-Safe Operation**: Maintain safe operation during fault conditions
7. **Diagnostic Functions**: Perform self-diagnostics and fault reporting

#### 2.2.2 Secondary Functions (Within Item Scope)
1. **Speed-Sensitive Assistance**: Adjust assistance based on vehicle speed
2. **Return-to-Center**: Assist steering wheel return to center position
3. **Damping Control**: Provide appropriate steering damping
4. **Active Return**: Active centering assistance at low speeds
5. **Driver Monitoring**: Detect driver hands-off conditions
6. **Calibration Management**: Store and manage system calibration parameters

#### 2.2.3 Functions Outside Item Scope
1. **Mechanical Steering**: Basic mechanical steering capability (manual fallback)
2. **Vehicle Dynamics Control**: ESP, ABS, traction control systems
3. **Advanced Driver Assistance**: Lane keeping, parking assist (coordination only)
4. **Power Generation**: Battery charging, alternator control
5. **Network Management**: CAN bus arbitration and network control

### 2.3 System Interfaces

#### 2.3.1 Electrical Interfaces

**Power Supply Interfaces:**
- **12V Battery Supply**: Primary power input (10.5V - 16V operating range)
- **Ground Connections**: Multiple ground paths for safety and EMC
- **Wake-up Signal**: System activation from ignition or CAN

**Communication Interfaces:**
- **CAN High-Speed**: Primary vehicle communication (500 kbps)
- **CAN Low-Speed**: Secondary communication if required (125 kbps)
- **LIN Bus**: Steering wheel controls communication (19.2 kbps)
- **Diagnostic Interface**: K-Line or CAN-based diagnostics

**Sensor Interfaces:**
- **Torque Sensor**: Analog differential signals (±5V)
- **Steering Angle Sensor**: Digital/analog position feedback
- **Motor Position Sensor**: Hall effect or encoder signals
- **Temperature Sensors**: Analog temperature monitoring

#### 2.3.2 Mechanical Interfaces

**Mounting Interfaces:**
- **ECU Mounting**: Secure attachment to vehicle structure
- **Motor Mounting**: Rigid connection to steering system
- **Sensor Integration**: Precise alignment with steering components

**Steering System Integration:**
- **Torque Transmission**: Mechanical connection for assist torque
- **Position Sensing**: Mechanical coupling for position measurement
- **Manual Override**: Mechanical backup for manual steering

#### 2.3.3 Software Interfaces

**Vehicle Network Communication:**
- **CAN Messages**: Standardized message formats for vehicle communication
- **Diagnostic Protocols**: UDS (ISO 14229) or KWP2000 protocols
- **Calibration Interface**: ASAM standards for parameter management

**Internal Software Interfaces:**
- **AUTOSAR Architecture**: Standardized software architecture
- **Safety Mechanisms**: Software-based safety monitoring functions
- **Bootloader**: Secure software update capability

## 3. Operational Environment

### 3.1 Vehicle Integration Context

#### 3.1.1 Vehicle Types
- **Passenger Cars**: Compact, mid-size, luxury vehicles
- **Light Commercial Vehicles**: Vans, pickup trucks
- **Vehicle Classes**: A-segment through F-segment vehicles

#### 3.1.2 Market Requirements
- **Global Markets**: Europe, North America, Asia-Pacific
- **Regulatory Compliance**: FMVSS, ECE, GB standards
- **Homologation**: Type approval requirements per market

### 3.2 Operating Conditions

#### 3.2.1 Environmental Conditions
- **Temperature Range**: -40°C to +85°C (ECU), -40°C to +150°C (motor)
- **Humidity**: 5% to 95% relative humidity (non-condensing)
- **Altitude**: Sea level to 3000m above sea level
- **Vibration**: Per ISO 16750-3 automotive vibration standards
- **EMC Environment**: Per CISPR 25 automotive EMC requirements

#### 3.2.2 Operational Scenarios
- **Urban Driving**: Low-speed maneuvering, parking, traffic
- **Highway Driving**: High-speed stability, lane changes
- **Rural Driving**: Variable road conditions, curves
- **Extreme Conditions**: Emergency maneuvers, adverse weather

### 3.3 Lifecycle Requirements

#### 3.3.1 Durability
- **Service Life**: 15 years minimum
- **Mileage**: 300,000 km minimum
- **Duty Cycle**: Continuous operation capability
- **Maintenance**: Maintenance-free operation

#### 3.3.2 Reliability Targets
- **MTBF**: >100,000 hours
- **Failure Rate**: <10 FIT (Failures in Time)
- **Availability**: >99.9% operational availability

## 4. Performance Requirements Overview

### 4.1 Functional Performance
- **Assist Torque Range**: 0 to 8 Nm (vehicle-dependent)
- **Torque Accuracy**: ±5% of commanded value
- **Response Time**: <50ms from input to output
- **System Latency**: <20ms total system delay

### 4.2 Quality Attributes
- **Safety**: ASIL C/D compliance per ISO 26262
- **Reliability**: Automotive-grade component reliability
- **Availability**: High availability with graceful degradation
- **Maintainability**: Diagnostic capability for service support

## 5. Assumptions and Dependencies

### 5.1 Vehicle System Assumptions
- **Power Supply**: Stable 12V electrical system with proper grounding
- **CAN Network**: Functional vehicle CAN bus with proper termination
- **Mechanical System**: Properly maintained steering mechanical components
- **Installation**: Correct installation and calibration procedures followed

### 5.2 External Dependencies
- **Vehicle Speed Signal**: Accurate vehicle speed information from ABS/ESP
- **Engine Status**: Engine running/stopped status for power management
- **Diagnostic Tools**: Compatible diagnostic equipment for service
- **Calibration Data**: Vehicle-specific calibration parameters

### 5.3 Regulatory Assumptions
- **Standards Compliance**: Compliance with applicable automotive standards
- **Type Approval**: Successful completion of homologation processes
- **Market Requirements**: Adherence to regional regulatory requirements

## 6. Constraints and Limitations

### 6.1 Technical Constraints
- **Power Consumption**: Maximum 150W continuous, 300W peak
- **Package Size**: Fit within available vehicle space envelope
- **Weight**: Minimize weight impact on vehicle
- **Cost**: Meet target cost objectives for volume production

### 6.2 Regulatory Constraints
- **EMC Compliance**: Meet automotive EMC requirements
- **Safety Standards**: Comply with ISO 26262 functional safety
- **Environmental**: Meet automotive environmental standards
- **Cybersecurity**: Address automotive cybersecurity requirements

### 6.3 Manufacturing Constraints
- **Production Volume**: Scalable for high-volume production
- **Quality Systems**: ISO/TS 16949 automotive quality standards
- **Supply Chain**: Automotive-qualified supplier network
- **Testing**: Comprehensive validation and verification testing

## 7. Success Criteria

### 7.1 Technical Success Criteria
- **Performance**: Meet all specified performance requirements
- **Safety**: Achieve target ASIL rating with safety case approval
- **Quality**: Pass all validation and verification tests
- **Integration**: Successful integration with target vehicles

### 7.2 Business Success Criteria
- **Cost**: Achieve target manufacturing cost
- **Schedule**: Meet development timeline milestones
- **Quality**: Achieve target quality metrics (PPM, warranty)
- **Compliance**: Pass all regulatory and certification requirements

## 8. Document Control

### 8.1 Document Information
- **Document ID**: EPS-ITEM-DEF-001
- **Version**: 1.0
- **Status**: Draft
- **Classification**: Internal Use

### 8.2 Approval Requirements
- **Technical Review**: Systems engineering team approval
- **Safety Review**: Functional safety team approval
- **Management Review**: Program management approval
- **Customer Review**: OEM customer approval (if applicable)

### 8.3 Change Control
- **Change Process**: Formal change control process required
- **Impact Assessment**: Safety impact assessment for all changes
- **Traceability**: Maintain traceability to requirements and tests
- **Version Control**: Controlled document versioning system