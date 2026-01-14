#include "safety_manager.hpp"
#include <iostream>
#include <stdexcept>

// Constructor for SafetyManager
SafetyManager::SafetyManager() : is_system_safe(true), max_current(100.0), max_temperature(75.0) {}

// Method to check if system is safe
bool SafetyManager::check_system_safety(const MotorState &motor_state) {
    // Ensure we have valid input state
    if (!is_valid_motor_state(motor_state)) {
        std::cerr << "ERROR: Invalid motor state provided!" << std::endl;
        return false;
    }
    
    // Example of safety checks
    if (motor_state.current > max_current) {
        std::cerr << "WARNING: Overcurrent detected!" << std::endl;
        trigger_safety_protocol();
        return false;
    }
    if (motor_state.temperature > max_temperature) {
        std::cerr << "WARNING: Overheating detected!" << std::endl;
        trigger_safety_protocol();
        return false;
    }
    // Check for negative values, which are likely erroneous
    if (motor_state.current < 0 || motor_state.temperature < 0) {
        std::cerr << "WARNING: Detected negative sensor readings! Check sensor calibration." << std::endl;
        trigger_safety_protocol();
        return false;
    }
    // Additional safety checks can be added here
    return true;
}

// Method to trigger safety protocols
void SafetyManager::trigger_safety_protocol() {
    if (!is_system_safe) {
        std::cerr << "INFO: Safety protocol already active, redundant trigger ignored." << std::endl;
        return;
    }
    is_system_safe = false;
    std::cerr << "Safety protocol triggered! Stopping motor.\n";
    // Code to stop the motor safely
    stop_motor();
}

// Mock method to stop the motor
void SafetyManager::stop_motor() {
    // Implementation to stop motor safely
    std::cout << "Motor stopped for safety.\n";
}

// Method to reset safety protocols
void SafetyManager::reset_safety() {
    if (is_system_safe) {
        std::cerr << "INFO: System already safe, reset unnecessary." << std::endl;
        return;
    }
    is_system_safe = true;
    std::cout << "Safety protocols reset. System operational again.\n";
}

// Method to check if the system is safe
bool SafetyManager::is_safe() const {
    return is_system_safe;
}

// Helper method to validate motor state
bool SafetyManager::is_valid_motor_state(const MotorState &motor_state) const {
    return motor_state.current >= 0 && motor_state.temperature >= 0;
}

// End of File: SafetyManager.cpp
