# Electronic Braking System (EBS) - Component Design Specifications

## Document Information
- **Document Title**: EBS Component Design Specifications
- **Version**: 1.0
- **Date**: 2025-07-29
- **Classification**: Technical Design Document
- **Related Documents**: EBS_Requirements_Specification.md, EBS_System_Architecture_Specification.md

## Table of Contents
1. [Introduction](#introduction)
2. [Electronic Control Unit (ECU) Specifications](#electronic-control-unit-ecu-specifications)
3. [Sensor Component Specifications](#sensor-component-specifications)
4. [Actuator Component Specifications](#actuator-component-specifications)
5. [Communication Interface Specifications](#communication-interface-specifications)
6. [Power Management Specifications](#power-management-specifications)
7. [Mechanical Design Specifications](#mechanical-design-specifications)
8. [Environmental Protection Specifications](#environmental-protection-specifications)

---

## 1. Introduction

### 1.1 Purpose
This document provides detailed component-level design specifications for all hardware components of the Electronic Braking System (EBS), including electrical, mechanical, and environmental requirements.

### 1.2 Scope
The specifications cover:
- Electronic Control Units (Primary and Secondary)
- All sensor components and their interfaces
- Actuator components and control mechanisms
- Communication interfaces and protocols
- Power management and distribution
- Mechanical packaging and mounting
- Environmental protection requirements

### 1.3 Design Standards
- **Automotive Standards**: ISO 26262, ISO 16750, ISO 11452
- **Electronic Standards**: IEC 61508, IPC standards
- **Environmental Standards**: IP67, MIL-STD-810
- **EMC Standards**: CISPR 25, ISO 11452

---

## 2. Electronic Control Unit (ECU) Specifications

### 2.1 Primary ECU (EBS-ECU-P)

#### 2.1.1 Microcontroller Specifications
- **Part Number**: Infineon AURIX TC397 (or equivalent)
- **Architecture**: 32-bit TriCore with dual ARM Cortex-R5F cores
- **Clock Frequency**: 300 MHz main core, 200 MHz safety core
- **Safety Certification**: ISO 26262 ASIL-D qualified
- **Package**: LFBGA-516 (23mm x 23mm)
- **Operating Temperature**: -40°C to +150°C junction temperature

#### 2.1.2 Memory Specifications
| Memory Type | Capacity | Technology | Purpose |
|-------------|----------|------------|---------|
| Program Flash | 8 MB | Embedded Flash | Application code, calibration |
| Data Flash | 384 KB | EEPROM emulation | Non-volatile data storage |
| System RAM | 1 MB | SRAM | Runtime variables, stack |
| Safety RAM | 256 KB | ECC protected | Safety-critical data |
| Cache | 32 KB I-Cache, 16 KB D-Cache | On-chip | Performance optimization |

#### 2.1.3 Input/Output Specifications

**Analog Inputs (16 channels)**
- **Resolution**: 12-bit ADC
- **Sample Rate**: Up to 1 MSPS
- **Input Range**: 0-5V, 0-12V (configurable)
- **Accuracy**: ±0.5% FSR
- **Input Impedance**: >1 MΩ
- **Protection**: Overvoltage, reverse polarity

**Digital Inputs (24 channels)**
- **Voltage Levels**: 3.3V, 5V, 12V compatible
- **Input Current**: <1 mA per channel
- **Switching Threshold**: Schmitt trigger with hysteresis
- **Protection**: ESD protection to ±8kV
- **Debounce**: Hardware and software configurable

**PWM Outputs (12 channels)**
- **Frequency Range**: 100 Hz to 20 kHz
- **Resolution**: 16-bit
- **Output Current**: 2A per channel (with external driver)
- **Protection**: Short circuit, overtemperature
- **Diagnostics**: Load current monitoring

**CAN Interfaces (3 channels)**
- **Standard**: CAN 2.0B, CAN-FD capable
- **Baud Rate**: Up to 1 Mbps (CAN 2.0B), 8 Mbps (CAN-FD)
- **Transceiver**: Integrated high-speed CAN transceivers
- **Protection**: Bus fault protection, wake-up capability
- **Diagnostics**: Bus-off recovery, error frame detection

#### 2.1.4 Power Supply Specifications
- **Input Voltage**: 9V to 16V nominal (6V to 32V survival)
- **Power Consumption**: 15W typical, 25W maximum
- **Standby Current**: <5 mA in sleep mode
- **Inrush Current**: <50A for 1ms
- **Reverse Polarity Protection**: Integrated MOSFET protection
- **Load Dump Protection**: ISO 7637-2 compliant

#### 2.1.5 Physical Specifications
- **Dimensions**: 150mm x 100mm x 35mm (L x W x H)
- **Weight**: 800g maximum
- **Connector**: 2x 64-pin automotive connectors (TE Connectivity AMP)
- **Mounting**: 4-point mounting with vibration isolation
- **Material**: Aluminum housing with thermal interface

### 2.2 Secondary ECU (EBS-ECU-S)

#### 2.2.1 Microcontroller Specifications
- **Part Number**: Infineon AURIX TC375 (or equivalent)
- **Architecture**: 32-bit TriCore with ARM Cortex-R4F core
- **Clock Frequency**: 200 MHz main core
- **Safety Certification**: ISO 26262 ASIL-D qualified
- **Package**: LFBGA-292 (17mm x 17mm)
- **Operating Temperature**: -40°C to +150°C junction temperature

#### 2.2.2 Memory Specifications
| Memory Type | Capacity | Technology | Purpose |
|-------------|----------|------------|---------|
| Program Flash | 4 MB | Embedded Flash | Backup application code |
| Data Flash | 128 KB | EEPROM emulation | Configuration data |
| System RAM | 512 KB | SRAM | Runtime variables |
| Safety RAM | 128 KB | ECC protected | Safety monitoring data |

#### 2.2.3 Input/Output Specifications
- **Analog Inputs**: 8 channels, 12-bit ADC
- **Digital Inputs**: 16 channels, 3.3V/5V compatible
- **PWM Outputs**: 6 channels, 16-bit resolution
- **CAN Interfaces**: 2 channels, CAN 2.0B/CAN-FD
- **SPI Interfaces**: 2 channels for sensor communication

#### 2.2.4 Physical Specifications
- **Dimensions**: 100mm x 80mm x 25mm (L x W x H)
- **Weight**: 400g maximum
- **Connector**: 1x 48-pin automotive connector
- **Mounting**: 3-point mounting with vibration isolation

---

## 3. Sensor Component Specifications

### 3.1 Wheel Speed Sensors (WSS)

#### 3.1.1 Sensor Technology
- **Type**: Active Hall Effect sensor with integrated signal conditioning
- **Part Number**: Continental VDO A2C59513636 (or equivalent)
- **Sensing Element**: Hall IC with temperature compensation
- **Target**: Magnetic encoder ring (48 teeth)
- **Air Gap**: 0.5mm to 3.0mm operating range

#### 3.1.2 Electrical Specifications
- **Supply Voltage**: 5V ±5% (4.75V to 5.25V)
- **Supply Current**: 15 mA typical, 25 mA maximum
- **Output Type**: Digital square wave (push-pull)
- **Output Voltage**: 0.4V low, 4.6V high (into 1kΩ load)
- **Frequency Range**: 0 Hz to 10 kHz
- **Rise/Fall Time**: <10 μs

#### 3.1.3 Performance Specifications
- **Speed Range**: 0 to 300 km/h vehicle speed
- **Resolution**: 48 pulses per wheel revolution
- **Accuracy**: ±0.1% of reading ±0.1 km/h
- **Response Time**: <100 μs
- **Temperature Drift**: <0.01%/°C
- **Jitter**: <1% of pulse width

#### 3.1.4 Environmental Specifications
- **Operating Temperature**: -40°C to +150°C
- **Storage Temperature**: -55°C to +170°C
- **Vibration**: 30g RMS, 10-2000 Hz
- **Shock**: 100g, 11ms duration
- **IP Rating**: IP67 (dust tight, waterproof)
- **Salt Spray**: 240 hours per ASTM B117

#### 3.1.5 Mechanical Specifications
- **Housing Material**: PBT plastic with glass fiber reinforcement
- **Connector**: 3-pin sealed connector (Delphi Metri-Pack)
- **Cable**: 1.5m length, twisted pair with shield
- **Mounting**: M12 threaded housing with lock nut
- **Dimensions**: Ø12mm x 45mm (sensor head)

### 3.2 Inertial Measurement Unit (IMU)

#### 3.2.1 Sensor Technology
- **Part Number**: Bosch SMI230 (or equivalent)
- **Gyroscope**: 3-axis MEMS gyroscope
- **Accelerometer**: 3-axis MEMS accelerometer
- **Package**: LGA-14 (3mm x 4.5mm x 0.8mm)
- **Interface**: SPI (up to 10 MHz)

#### 3.2.2 Gyroscope Specifications
- **Measurement Range**: ±125°/s, ±250°/s, ±500°/s, ±1000°/s, ±2000°/s
- **Sensitivity**: 16.384 LSB/°/s (±2000°/s range)
- **Resolution**: 16-bit ADC
- **Noise Density**: 0.014°/s/√Hz
- **Bias Stability**: ±1°/s over temperature
- **Cross-Axis Sensitivity**: ±2%

#### 3.2.3 Accelerometer Specifications
- **Measurement Range**: ±2g, ±4g, ±8g, ±16g
- **Sensitivity**: 2048 LSB/g (±16g range)
- **Resolution**: 16-bit ADC
- **Noise Density**: 150 μg/√Hz
- **Bias Stability**: ±40 mg over temperature
- **Cross-Axis Sensitivity**: ±2%

#### 3.2.4 Performance Specifications
- **Sample Rate**: Up to 1600 Hz (gyroscope), 1600 Hz (accelerometer)
- **Output Data Rate**: Configurable from 25 Hz to 1600 Hz
- **Start-up Time**: 30 ms typical
- **Current Consumption**: 5 mA typical (normal mode)
- **Power-down Current**: 3 μA typical

#### 3.2.5 Environmental Specifications
- **Operating Temperature**: -40°C to +85°C
- **Storage Temperature**: -55°C to +125°C
- **Shock**: 10,000g for 0.2ms
- **Vibration**: Per IEC 60068-2-6
- **Humidity**: 85% RH at 85°C

### 3.3 Brake Pressure Sensors

#### 3.3.1 Sensor Technology
- **Type**: Piezoresistive silicon pressure sensor
- **Part Number**: Sensata 84DA-15-4-A250 (or equivalent)
- **Sensing Element**: Silicon diaphragm with strain gauges
- **Pressure Port**: 1/8-27 NPT threaded port
- **Media Compatibility**: DOT 3, DOT 4, DOT 5.1 brake fluid

#### 3.3.2 Performance Specifications
- **Pressure Range**: 0 to 250 bar (0 to 3625 psi)
- **Accuracy**: ±0.25% FSO (including linearity, hysteresis, repeatability)
- **Resolution**: 0.1 bar (limited by 12-bit ADC)
- **Response Time**: <1 ms (10% to 90%)
- **Proof Pressure**: 375 bar (1.5x full scale)
- **Burst Pressure**: 625 bar (2.5x full scale)

#### 3.3.3 Electrical Specifications
- **Supply Voltage**: 5V ±0.25V
- **Supply Current**: 10 mA typical
- **Output**: 0.5V to 4.5V ratiometric
- **Output Impedance**: 5kΩ typical
- **Load Resistance**: >10kΩ minimum
- **Insulation Resistance**: >100 MΩ at 50V DC

#### 3.3.4 Environmental Specifications
- **Operating Temperature**: -40°C to +125°C
- **Compensated Temperature**: -40°C to +125°C
- **Temperature Error**: ±1% FSO over compensated range
- **Vibration**: 20g RMS, 10-2000 Hz
- **Shock**: 100g, 11ms duration
- **IP Rating**: IP67

#### 3.3.5 Mechanical Specifications
- **Housing Material**: 17-4 PH stainless steel
- **Diaphragm Material**: 17-4 PH stainless steel
- **O-ring Material**: FKM (Viton)
- **Connector**: 3-pin Deutsch DT series
- **Weight**: 85g typical
- **Dimensions**: 25mm diameter x 35mm length

### 3.4 Steering Angle Sensor

#### 3.4.1 Sensor Technology
- **Type**: Contactless magnetic rotary encoder
- **Part Number**: Hella 6PX 012 684-041 (or equivalent)
- **Sensing Principle**: Dual Hall sensor with magnetic disc
- **Absolute Position**: Multi-turn absolute encoder
- **Resolution**: 0.1° mechanical resolution

#### 3.4.2 Performance Specifications
- **Measurement Range**: ±720° (4 full turns)
- **Accuracy**: ±0.5° over full range
- **Resolution**: 0.1° (12-bit equivalent)
- **Repeatability**: ±0.1°
- **Linearity**: ±0.2% of full scale
- **Update Rate**: 100 Hz minimum

#### 3.4.3 Electrical Specifications
- **Supply Voltage**: 5V ±5%
- **Supply Current**: 50 mA typical, 80 mA maximum
- **Interface**: CAN 2.0B (500 kbps)
- **Message Rate**: 10 ms cycle time
- **Wake-up**: CAN wake-up capable
- **Sleep Current**: <1 mA

#### 3.4.4 Environmental Specifications
- **Operating Temperature**: -40°C to +85°C
- **Storage Temperature**: -55°C to +125°C
- **Vibration**: 15g RMS, 10-1000 Hz
- **Shock**: 50g, 11ms duration
- **IP Rating**: IP54 (dust protected, splash proof)
- **EMC**: ISO 11452 compliant

#### 3.4.5 Mechanical Specifications
- **Housing Material**: PA66 with glass fiber
- **Shaft Material**: Stainless steel
- **Bearing**: Maintenance-free ball bearing
- **Connector**: 8-pin circular connector
- **Mounting**: Clamp-on steering column mount
- **Dimensions**: Ø65mm x 45mm height

---

## 4. Actuator Component Specifications

### 4.1 Hydraulic Modulator Unit (HMU)

#### 4.1.1 System Overview
- **Function**: Brake pressure modulation for ABS/ESC operation
- **Configuration**: 4-channel independent wheel control
- **Pressure Range**: 0 to 250 bar operating pressure
- **Flow Rate**: 15 L/min at 200 bar
- **Response Time**: <10 ms valve switching

#### 4.1.2 Solenoid Valve Specifications

**Inlet Valves (4x)**
- **Type**: Normally open, 2/2-way solenoid valve
- **Orifice Diameter**: 2.5 mm
- **Operating Pressure**: 0-250 bar
- **Flow Coefficient**: Cv = 0.8
- **Response Time**: <5 ms opening, <3 ms closing
- **Power Consumption**: 15W holding, 45W peak (100ms)

**Outlet Valves (4x)**
- **Type**: Normally closed, 2/2-way solenoid valve
- **Orifice Diameter**: 2.0 mm
- **Operating Pressure**: 0-250 bar
- **Flow Coefficient**: Cv = 0.6
- **Response Time**: <5 ms opening, <3 ms closing
- **Power Consumption**: 12W holding, 36W peak (100ms)

#### 4.1.3 Pump Specifications
- **Type**: Radial piston pump with eccentric drive
- **Drive Motor**: 12V DC motor, 300W peak power
- **Flow Rate**: 15 L/min at 200 bar
- **Maximum Pressure**: 300 bar
- **Efficiency**: >70% at rated conditions
- **Noise Level**: <75 dB(A) at 1m distance

#### 4.1.4 Accumulator Specifications
- **Type**: Diaphragm accumulator with nitrogen precharge
- **Volume**: 0.5 L fluid capacity
- **Precharge Pressure**: 50 bar nitrogen
- **Maximum Pressure**: 300 bar
- **Material**: Steel pressure vessel with rubber diaphragm
- **Certification**: PED 2014/68/EU compliant

#### 4.1.5 Control Electronics
- **Valve Drivers**: 8x high-side MOSFET drivers
- **Current Control**: PWM current regulation (1-5 kHz)
- **Diagnostics**: Valve current monitoring, coil resistance measurement
- **Protection**: Overcurrent, overtemperature, short circuit
- **Interface**: CAN communication with main ECU

#### 4.1.6 Physical Specifications
- **Dimensions**: 250mm x 200mm x 150mm (L x W x H)
- **Weight**: 8.5 kg including brake fluid
- **Mounting**: 6-point mounting with vibration isolation
- **Connections**: 8x brake line connections (M10x1.0 threads)
- **Material**: Aluminum housing with corrosion protection

### 4.2 Electric Brake Actuators (Future Enhancement)

#### 4.2.1 Actuator Technology
- **Type**: Electromechanical brake caliper with integrated motor
- **Motor**: Brushless DC motor with planetary gearbox
- **Force Range**: 0 to 50 kN clamping force
- **Position Range**: 0 to 20 mm pad travel
- **Efficiency**: >85% mechanical efficiency

#### 4.2.2 Motor Specifications
- **Type**: 3-phase BLDC motor
- **Power**: 2 kW peak, 500W continuous
- **Speed**: 3000 RPM maximum
- **Torque**: 15 Nm peak, 4 Nm continuous
- **Control**: Sinusoidal commutation with encoder feedback
- **Protection**: IP67 sealed housing

#### 4.2.3 Gearbox Specifications
- **Type**: 3-stage planetary gearbox
- **Ratio**: 100:1 reduction
- **Efficiency**: >90% per stage
- **Backlash**: <0.5° at output
- **Lubrication**: Lifetime sealed lubrication
- **Material**: Hardened steel gears

#### 4.2.4 Position Feedback
- **Sensor Type**: Absolute magnetic encoder
- **Resolution**: 0.01 mm position accuracy
- **Interface**: SSI (Synchronous Serial Interface)
- **Update Rate**: 1 kHz position feedback
- **Redundancy**: Dual encoder channels

#### 4.2.5 Force Feedback
- **Sensor Type**: Strain gauge load cell
- **Range**: 0-60 kN (120% of maximum force)
- **Accuracy**: ±1% of full scale
- **Resolution**: 10 N force resolution
- **Interface**: Analog voltage output
- **Temperature Compensation**: Integrated

---

## 5. Communication Interface Specifications

### 5.1 CAN Bus Interface

#### 5.1.1 Physical Layer
- **Standard**: ISO 11898-2 (CAN 2.0B)
- **Bit Rate**: 500 kbps (high-speed CAN)
- **Cable**: Twisted pair, 120Ω characteristic impedance
- **Termination**: 120Ω resistors at both ends
- **Maximum Length**: 40m at 500 kbps
- **Connector**: 9-pin D-sub or automotive-specific

#### 5.1.2 Data Link Layer
- **Frame Format**: CAN 2.0B extended frame (29-bit identifier)
- **Data Length**: 0-8 bytes per frame
- **Error Detection**: CRC-15, frame check, bit monitoring
- **Error Handling**: Automatic retransmission, bus-off recovery
- **Arbitration**: CSMA/CD with bitwise arbitration

#### 5.1.3 Application Layer
- **Protocol**: CANopen or proprietary protocol
- **Message Types**: Process data, service data, emergency
- **Addressing**: Node ID based addressing
- **Services**: SDO (Service Data Objects), PDO (Process Data Objects)
- **Network Management**: Heartbeat, node guarding

### 5.2 SPI Interface

#### 5.2.1 Physical Layer
- **Standard**: SPI (Serial Peripheral Interface)
- **Clock Speed**: Up to 10 MHz
- **Voltage Levels**: 3.3V CMOS
- **Signals**: SCLK, MOSI, MISO, CS (chip select)
- **Cable**: 4-wire interface with ground

#### 5.2.2 Protocol Specifications
- **Mode**: SPI Mode 0 (CPOL=0, CPHA=0)
- **Bit Order**: MSB first
- **Frame Size**: 8-bit or 16-bit configurable
- **CS Timing**: Minimum 100ns setup/hold time
- **Data Rate**: Up to 1 Mbps effective data rate

### 5.3 PWM Interface

#### 5.3.1 Signal Specifications
- **Frequency Range**: 100 Hz to 20 kHz
- **Resolution**: 16-bit (65536 steps)
- **Duty Cycle Range**: 0% to 100%
- **Voltage Levels**: 0V to 12V (with external driver)
- **Rise/Fall Time**: <1 μs (10% to 90%)

#### 5.3.2 Control Specifications
- **Update Rate**: 1 kHz minimum command update
- **Accuracy**: ±0.1% of commanded duty cycle
- **Jitter**: <0.01% of period
- **Synchronization**: Phase-locked to system clock
- **Protection**: Overcurrent detection and shutdown

---

## 6. Power Management Specifications

### 6.1 Power Distribution Architecture

#### 6.1.1 Primary Power Supply
- **Input Voltage**: 12V automotive battery (9V-16V nominal)
- **Input Current**: 25A maximum (including all actuators)
- **Inrush Current**: <50A for 1ms at startup
- **Reverse Polarity Protection**: MOSFET-based protection
- **Overvoltage Protection**: Crowbar circuit at 32V

#### 6.1.2 Voltage Regulation
- **5V Rail**: 10A capacity for sensors and logic
  - Regulator: Switching regulator, >90% efficiency
  - Ripple: <50mV peak-to-peak
  - Load Regulation: ±2% from no load to full load
  - Line Regulation: ±1% over input voltage range

- **3.3V Rail**: 5A capacity for microcontroller and digital circuits
  - Regulator: Low-dropout linear regulator
  - Ripple: <10mV peak-to-peak
  - Load Regulation: ±1% from no load to full load
  - Dropout Voltage: <300mV at full load

#### 6.1.3 Power Monitoring
- **Voltage Monitoring**: All supply rails monitored
- **Current Monitoring**: Load current measurement per rail
- **Temperature Monitoring**: Power component temperature sensing
- **Fault Detection**: Overvoltage, undervoltage, overcurrent detection
- **Protection**: Automatic shutdown and recovery

### 6.2 Power Modes

#### 6.2.1 Normal Operation Mode
- **Total Power**: 150W maximum (all systems active)
- **ECU Power**: 25W (primary) + 15W (secondary)
- **Sensor Power**: 10W total
- **Actuator Power**: 100W maximum (pump + valves)
- **Efficiency**: >85% overall system efficiency

#### 6.2.2 Standby Mode
- **Total Power**: 5W maximum
- **ECU Power**: 2W (reduced clock speed)
- **Sensor Power**: 2W (essential sensors only)
- **Actuator Power**: 0W (all actuators off)
- **Wake-up**: CAN message or ignition signal

#### 6.2.3 Sleep Mode
- **Total Power**: 50mW maximum
- **ECU Power**: 30mW (RTC and wake-up circuits only)
- **Sensor Power**: 0W (all sensors powered down)
- **Actuator Power**: 0W (all actuators off)
- **Wake-up Time**: <100ms to normal operation

---

## 7. Mechanical Design Specifications

### 7.1 Housing Design

#### 7.1.1 ECU Housing
- **Material**: Die-cast aluminum alloy (A380)
- **Surface Treatment**: Anodized finish, 25μm thickness
- **Wall Thickness**: 3mm minimum for structural integrity
- **Sealing**: O-ring sealed, IP67 rating
- **Thermal Interface**: Integrated heat sink with thermal pads

#### 7.1.2 Connector Design
- **Type**: Automotive-grade sealed connectors
- **Material**: PBT plastic housing with gold-plated contacts
- **Sealing**: IP67 when mated
- **Retention Force**: >100N connector pull-out force
- **Contact Resistance**: <5mΩ per contact
- **Insertion Cycles**: >1000 mate/unmate cycles

#### 7.1.3 Mounting System
- **Mounting Points**: 4-point mounting with M8 bolts
- **Vibration Isolation**: Rubber isolators, 40 Shore A hardness
- **Torque Specification**: 25 Nm ±5 Nm mounting torque
- **Clearance**: 10mm minimum clearance on all sides
- **Orientation**: Any orientation acceptable

### 7.2 Thermal Management

#### 7.2.1 Heat Dissipation
- **Maximum Heat Generation**: 25W (primary ECU)
- **Thermal Resistance**: <2°C/W junction to case
- **Heat Sink**: Integrated aluminum heat sink
- **Thermal Interface**: Thermal pad, 3W/mK conductivity
- **Convection**: Natural convection cooling

#### 7.2.2 Temperature Monitoring
- **Sensor Type**: NTC thermistor, 10kΩ at 25°C
- **Accuracy**: ±2°C over operating range
- **Response Time**: <10s thermal time constant
- **Protection**: Thermal shutdown at 125°C
- **Hysteresis**: 10°C hysteresis for thermal protection

### 7.3 Vibration and Shock Resistance

#### 7.3.1 Vibration Specifications
- **Standard**: ISO 16750-3, Table 1
- **Frequency Range**: 10 Hz to 2000 Hz
- **Acceleration**: 30g RMS
- **Duration**: 8 hours per axis (X, Y, Z)
- **Mounting**: Vibration isolated mounting

#### 7.3.2 Shock Specifications
- **Standard**: ISO 16750-3, Table 2
- **Acceleration**: 100g peak
- **Duration**: 11ms half-sine pulse
- **Direction**: All six directions (±X, ±Y, ±Z)
- **Quantity**: 3 shocks per direction

---

## 8. Environmental Protection Specifications

### 8.1 Ingress Protection

#### 8.1.1 IP Rating Requirements
- **ECU Housing**: IP67 (dust tight, waterproof to 1m depth)
- **Sensor Housing**: IP67 minimum, IP69K for wheel speed sensors
- **Connector Interfaces**: IP67 when mated
- **Cable Entries**: IP67 with appropriate cable glands
- **Vent Requirements**: Gore-Tex membrane for pressure equalization

#### 8.1.2 Sealing System
- **Primary Seals**: FKM (Viton) O-rings
- **Secondary Seals**: Silicone gaskets where required
- **Cable Seals**: Molded cable boots with strain relief
- **Connector Seals**: Integrated connector sealing system
- **Test Method**: IPX7 water immersion test

### 8.2 Chemical Resistance

#### 8.2.1 Automotive Fluids
- **Engine Oil**: No degradation after 1000 hours exposure
- **Brake Fluid**: DOT 3, DOT 4, DOT 5.1 compatibility
- **Coolant**: Ethylene glycol based coolant resistance
- **Fuel**: Gasoline and diesel fuel resistance
- **Cleaning Agents**: Automotive cleaning chemical resistance

#### 8.2.2 Environmental Chemicals
- **Salt Spray**: 240 hours per ASTM B117
- **Acid Rain**: pH 3.0 solution resistance
- **Road Salt**: 5% NaCl solution resistance
- **De-icing Fluids**: Calcium chloride solution resistance
- **UV Exposure**: 1000 hours UV-B exposure per ASTM G154

### 8.3 Temperature Cycling

#### 8.3.1 Operating Temperature Range
- **Minimum**: -40°C (cold start capability)
- **Maximum**: +85°C (under-hood environment)
- **Gradient**: 2°C/minute maximum rate of change
- **Cycles**: 1000 cycles over product lifetime
- **Humidity**: 5% to 95% RH non-condensing

#### 8.3.2 Storage Temperature Range
- **Minimum**: -55°C (shipping and storage)
- **Maximum**: +125°C (shipping and storage)
- **Duration**: Up to 6 months storage
- **Packaging**: Moisture barrier bag with desiccant
- **Recovery**: Full functionality after storage

### 8.4 Electromagnetic Compatibility (EMC)

#### 8.4.1 Emission Requirements
- **Standard**: CISPR 25, Class 5 limits
- **Frequency Range**: 150 kHz to 1 GHz
- **Measurement**: Peak and average detection
- **Antenna**: Biconical and log-periodic antennas
- **Test Setup**: Vehicle simulation with LISN

#### 8.4.2 Immunity Requirements
- **Standard**: ISO 11452 series
- **BCI (Bulk Current Injection)**: 60 mA, 1-400 MHz
- **Radiated Immunity**: 200 V/m, 80-1000 MHz
- **ESD**: ±8 kV contact, ±15 kV air discharge
- **Transients**: ISO 7637-2 pulses 1, 2a, 3a, 3b, 4

---

## Document Control

### Revision History
| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | 2025-07-29 | Component Engineer | Initial component specifications |

### Approval
- **Component Engineer**: [Signature Required]
- **Hardware Manager**: [Signature Required]