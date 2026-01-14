#include "safety_manager.hpp"
#include <iostream>
#include <stdexcept>

// Constants for threshold limits
const float CURRENT_THRESHOLD = 30.0; // Amps
const float TEMPERATURE_THRESHOLD = 75.0; // Celsius

SafetyManager::SafetyManager() : current(0), temperature(0), is_safe(true) {}

void SafetyManager::updateSensors(float current_reading, float temperature_reading) {
    this->current = current_reading;
    this->temperature = temperature_reading;
    checkSafety(); 
}

void SafetyManager::checkSafety() {
    if (!is_safe) return; // If already in a hazardous state, skip checks.

    // Check for overcurrent
    if (current > CURRENT_THRESHOLD) {
        is_safe = false;
        handleHazard("Overcurrent detected!");
    }

    // Check for overheating, only if not already in a hazardous state
    if (is_safe && temperature > TEMPERATURE_THRESHOLD) {
        is_safe = false;
        handleHazard("Overheating detected!");
    }
}

void SafetyManager::handleHazard(const std::string &message) {
    // Log the hazard
    std::cerr << "Safety Alert: " << message << std::endl;
    // Implement appropriate safety measures, e.g., shutdown motor
    shutdownMotor();
}

void SafetyManager::shutdownMotor() {
    std::cout << "Motor has been safely shut down due to safety alert." << std::endl;
    // Additional logic for shutting down the motor can be added here
}

bool SafetyManager::isSafe() const {
    return is_safe;
}

void SafetyManager::reset() {
    is_safe = true;
    current = 0;
    temperature = 0;
    std::cout << "Safety Manager has been reset." << std::endl;
}
