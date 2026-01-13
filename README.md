# Safe Motor Control System

## Tagline

## Project Overview

## Key Features
- **Real-time motor speed control** with built-in safety checks.
- **User-friendly Command Line Interface (CLI)** for operational commands and monitoring.
- **Extensive test suite** for ensuring motor functionality and safety.
- **Logging of motor operations and errors**, enabling comprehensive post-operation analysis.
- **Dataset generator** for simulating motor responses under various operational conditions.
- **Sanity checks on motor inputs and outputs** to ensure reliability during operation.

## Installation
To build and run the Safe Motor Control System, follow these instructions:
1. Clone the repository:
 ```bash
 git clone https://your-repo-url.git
 cd SafeMotorControlSystem
 ```
2. Create a build directory and navigate to it:
 ```bash
 mkdir build
 cd build
 ```
3. Run CMake to configure the build system:
 ```bash
 cmake ..
 ```
4. Build the project using make:
 ```bash
 make
 ```

## Running the System
After building the project, you can run the system using the Command Line Interface (CLI):
- To start the motor with safety checks:
 ```bash
 ./safe_motor_control run --start
 ```
- To check the current status of the motor system:
 ```bash
 ./safe_motor_control status
 ```

## Example Output
When running the `status` command, you might receive output like this:
```plaintext
Motor Status: ON
Current Speed: 300 RPM
Voltage: 12.5 V
Current: 3.2 A
Temperature: 55 °C
Safety Check: PASS
```

## Running Tests
To ensure the reliability of the system, run the included tests with the following command:
```bash
make test
```
This will execute all defined tests, evaluating the functionality of the motor control, safety manager, and CLI components.

## Project Layout
The project follows a modular architecture depicted below:
```
.
├── CMakeLists.txt # Build system configuration
├── README.md # Project documentation
├── include/ # Header files
│ ├── cli_interface.hpp # CLI interface definitions
│ ├── motor_control.hpp # Motor control class definitions
│ └── safety_manager.hpp # Safety management class definitions
├── src/ # Source files
│ ├── cli_interface.cpp # Implementation of CLI functionalities
│ ├── motor_control.cpp # Implementation of motor control logic
│ └── safety_manager.cpp # Implementation of safety mechanisms
└── tests/ # Unit tests
 ├── test_cli_interface.cpp # CLI unit tests
 ├── test_motor_control.cpp # Motor control tests
 └── test_safety_manager.cpp # Safety manager tests
```

## Notes
The project underscores modular design principles and rigorous testing to ensure high performance and reliability, addressing key requirements of safety and real-time monitoring in motor operations.
