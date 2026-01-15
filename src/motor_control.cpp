#include "motor_control.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>

class MotorControl {
private:
    float current_speed;
    const float max_speed;
    std::unique_ptr<SafetyManager> safety_manager;
    
public:
    MotorControl(float max) : current_speed(0), max_speed(max), safety_manager(new SafetyManager()) {
        // Handle invalid max speed
        if (max_speed <= 0) {
            throw std::invalid_argument("Max speed must be positive.");
        }
    }

    void setSpeed(float speed) {
        try {
            // First, ensure safety before proceeding
            if (safety_manager->isSafeToOperate()) {
                // Check if the requested speed is within bounds
                if (speed < 0 || speed > max_speed) {
                    throw std::out_of_range("Requested speed out of bounds.");
                }
                // Additional condition to reset speed to a minimum threshold for safety
                if (speed < 0.5) {
                    speed = 0; // Consider as stopped if below the safe operating minimum
                }
                current_speed = speed;
                std::cout << "Motor speed set to: " << current_speed << " units." << std::endl;
            } else {
                std::cerr << "Error: Unsafe to set speed due to safety checks." << std::endl;
            }
        }
        catch (const std::exception& ex) {
            std::cerr << "Exception caught in setSpeed: " << ex.what() << std::endl;
        }
    }

    float getSpeed() const {
        return current_speed;
    }

    void stop() {
        // Ensure safety check before stopping
        if (safety_manager->isSafeToOperate()) {
            current_speed = 0;
            std::cout << "Motor stopped." << std::endl;
        } else {
            std::cerr << "Error: Unsafe to stop motor due to safety checks." << std::endl;
        }
    }

    // Additional methods can be added here for more complex control logic.
};
