#include "cli_interface.hpp"
#include <iostream>
#include <string>
#include "motor_control.hpp"
#include "safety_manager.hpp"

// CLI Interface Implementation

void startMotor() {
    try {
        if (SafetyManager::checkSafety()) {
            MotorControl::start();
            std::cout << "Motor started successfully." << std::endl;
        } else {
            std::cout << "Cannot start motor: safety checks failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error starting motor: " << e.what() << std::endl;
    }
}

void displayStatus() {
    try {
        auto status = MotorControl::getStatus();
        std::cout << "Current Status: " << status << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error displaying status: " << e.what() << std::endl;
    }
}

void testAll() {
    try {
        if (SafetyManager::runTests()) {
            std::cout << "All safety tests passed successfully." << std::endl;
        } else {
            std::cout << "One or more safety tests failed." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error running tests: " << e.what() << std::endl;
    }
}

void handleCommand(const std::string& command) {
    if (command == "run --start") {
        startMotor();
    } else if (command == "status") {
        displayStatus();
    } else if (command == "test --all") {
        testAll();
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command(argv[1]);
        std::transform(command.begin(), command.end(), command.begin(), ::tolower); // Ensure case insensitivity
        handleCommand(command);
    } else {
        std::cout << "No command provided. Use 'run --start', 'status', or 'test --all'." << std::endl;
    }
    return 0;
}
